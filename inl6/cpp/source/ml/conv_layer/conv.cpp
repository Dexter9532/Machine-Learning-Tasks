/**
 * @brief Convolutional layer implementation details.
 */
#include <stdexcept>

#include "ml/conv_layer/conv.h"
#include "ml/factory/factory.h"
#include "ml/utils.h"

namespace ml::conv_layer {
// -----------------------------------------------------------------------------
Conv::Conv(const std::size_t inputSize, const std::size_t kernelSize,
           const act_func::Type actFunc)
    : myInput{}, myInputGradients{}, myKernel{}, myOutput{}, myError{},
      myKernelGradients{}, myActFunc{nullptr} {
  checkParameters(inputSize, kernelSize);
  initialize(inputSize, kernelSize, actFunc);
}

// -----------------------------------------------------------------------------
std::size_t Conv::inputSize() const noexcept { return myInput.size(); }

// -----------------------------------------------------------------------------
std::size_t Conv::outputSize() const noexcept { return myOutput.size(); }

// -----------------------------------------------------------------------------
const Matrix2d &Conv::output() const noexcept { return myOutput; }

// -----------------------------------------------------------------------------
const Matrix2d &Conv::inputGradients() const noexcept {
  return myInputGradients;
}

// -----------------------------------------------------------------------------
bool Conv::feedforward(const Matrix2d &input) noexcept {
  // Return false if the dimensions don't match.
  constexpr const char *opName{"feedforward in convolutional layer"};
  if (!matchDimensions(outputSize(), input.size(), opName) ||
      !isMatrixSquare(input, opName)) {
    return false;
  }

  myInput = input;
  initMatrix(myOutput);

  const std::size_t n{input.size()};
  const std::size_t k{myKernel.size()};
  const std::size_t pad{padBefore()};

  // Convolve the kernel over the input with zero-padding.
  for (std::size_t y{}; y < n; ++y) {
    for (std::size_t x{}; x < n; ++x) {
      double sum{};

      for (std::size_t ky{}; ky < k; ++ky) {
        for (std::size_t kx{}; kx < k; ++kx) {
          const int inY = static_cast<int>(y) + static_cast<int>(ky) -
                          static_cast<int>(pad);
          const int inX = static_cast<int>(x) + static_cast<int>(kx) -
                          static_cast<int>(pad);

          if ((inY >= 0) && (inY < static_cast<int>(n)) && (inX >= 0) &&
              (inX < static_cast<int>(n))) {
            sum += input[static_cast<std::size_t>(inY)]
                        [static_cast<std::size_t>(inX)] *
                   myKernel[ky][kx];
          }
        }
      }
      myOutput[y][x] = myActFunc->output(sum);
    }
  }
  // Return true to indicate success.
  return true;
}

// -----------------------------------------------------------------------------
bool Conv::backpropagate(const Matrix2d &outputGradients) noexcept {
  // Return false if the dimensions don't match.
  constexpr const char *opName{"backpropagation in convolutional layer"};
  if (!matchDimensions(outputSize(), outputGradients.size(), opName) ||
      !isMatrixSquare(outputGradients, opName)) {
    return false;
  }

  const std::size_t n{myOutput.size()};
  const std::size_t k{myKernel.size()};
  const std::size_t pad{padBefore()};

  // Compute error after applying activation function derivative.
  initMatrix(myError);

  for (std::size_t y{}; y < n; ++y) {
    for (std::size_t x{}; x < n; ++x) {
      myError[y][x] = outputGradients[y][x] * myActFunc->delta(myOutput[y][x]);
    }
  }

  // Compute kernel gradients.
  initMatrix(myKernelGradients);

  for (std::size_t ky{}; ky < k; ++ky) {
    for (std::size_t kx{}; kx < k; ++kx) {
      double sum{};

      for (std::size_t y{}; y < n; ++y) {
        for (std::size_t x{}; x < n; ++x) {
          const int inY = static_cast<int>(y) + static_cast<int>(ky) -
                          static_cast<int>(pad);
          const int inX = static_cast<int>(x) + static_cast<int>(kx) -
                          static_cast<int>(pad);

          if ((inY >= 0) && (inY < static_cast<int>(n)) && (inX >= 0) &&
              (inX < static_cast<int>(n))) {
            sum += myInput[static_cast<std::size_t>(inY)]
                          [static_cast<std::size_t>(inX)] *
                   myError[y][x];
          }
        }
      }
      myKernelGradients[ky][kx] = sum;
    }
  }

  // Compute input gradients.
  initMatrix(myInputGradients);

  for (std::size_t inY{}; inY < n; ++inY) {
    for (std::size_t inX{}; inX < n; ++inX) {
      double sum{};

      for (std::size_t y{}; y < n; ++y) {
        for (std::size_t x{}; x < n; ++x) {
          const int ky = static_cast<int>(inY) -
                         (static_cast<int>(y) - static_cast<int>(pad));
          const int kx = static_cast<int>(inX) -
                         (static_cast<int>(x) - static_cast<int>(pad));

          if ((ky >= 0) && (ky < static_cast<int>(k)) && (kx >= 0) &&
              (kx < static_cast<int>(k))) {
            sum += myError[y][x] * myKernel[static_cast<std::size_t>(ky)]
                                           [static_cast<std::size_t>(kx)];
          }
        }
      }
      myInputGradients[inY][inX] = sum;
    }
  }

  // Return true to indicate success.
  return true;
}

// -----------------------------------------------------------------------------
bool Conv::optimize(const double learningRate) noexcept {
  // Return false if the learning rate is invalid.
  constexpr const char *opName{"optimization in convolutional layer"};
  if (!checkLearningRate(learningRate, opName)) {
    return false;
  }

  // Adjust kernel parameters using the calculated gradients.
  const std::size_t k{myKernel.size()};

  for (std::size_t y{}; y < k; ++y) {
    for (std::size_t x{}; x < k; ++x) {
      myKernel[y][x] += myKernelGradients[y][x] * learningRate;
    }
  }
  // Return true to indicate success.
  return true;
}

// -----------------------------------------------------------------------------
void Conv::checkParameters(const std::size_t inputSize,
                           const std::size_t kernelSize) {
  if ((kMinKernelSize > kernelSize) || (kMaxKernelSize < kernelSize)) {
    throw std::invalid_argument("Invalid kernel size!");
  } else if (0U == inputSize) {
    throw std::invalid_argument("Input size cannot be 0!");
  } else if (inputSize < kernelSize) {
    throw std::invalid_argument(
        "Kernel size cannot be greater than input size!");
  }
}

// -----------------------------------------------------------------------------
void Conv::initialize(const std::size_t inputSize, const std::size_t kernelSize,
                      const act_func::Type actFunc) {
  // Initialize the matrices.
  initMatrix(myInput, inputSize);
  initMatrix(myInputGradients, inputSize);
  initMatrix(myKernel, kernelSize);
  initMatrix(myOutput, inputSize);
  initMatrix(myError, inputSize);
  initMatrix(myKernelGradients, kernelSize);

  // Fill the kernel with random values.
  for (std::size_t y{}; y < kernelSize; ++y) {
    for (std::size_t x{}; x < kernelSize; ++x) {
      myKernel[y][x] = randomStartVal();
    }
  }

  // initialize the activation function.
  factory::Factory factory{};
  myActFunc = factory.actFunc(actFunc);
}

// -----------------------------------------------------------------------------
std::size_t Conv::padBefore() const noexcept {
  return myKernel.empty() ? 0U : (myKernel.size() / 2U);
}
} // namespace ml::conv_layer
