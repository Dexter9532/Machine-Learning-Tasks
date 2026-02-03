/**
 * @brief Convolutional layer implementation.
 *
 *        This layer performs 2D convolution with zero-padding so that output
 *        spatial dimensions match the input. Stride is fixed to 1.
 */
#pragma once

#include "ml/act_func/type.h"
#include "ml/conv_layer/interface.h"
#include "ml/types.h"

namespace ml::conv_layer {
/**
 * @brief Convolutional layer implementation.
 *
 *        Performs convolution + activation, computes gradients for backprop,
 *        and updates kernel parameters during optimization.
 *
 *        This class is non-copyable and non-movable.
 */
class Conv final : public Interface {
public:
  /**
   * @brief Constructor.
   *
   * @param[in] inputSize Input size. Must be greater than 0.
   * @param[in] kernelSize Kernel size. Must be greater than 0 and smaller than
   * the input size.
   * @param[in] actFunc Activation function to use (default = none).
   */
  explicit Conv(std::size_t inputSize, std::size_t kernelSize,
                act_func::Type actFunc = act_func::Type::None);

  /**
   * @brief Destructor.
   */
  ~Conv() noexcept override = default;

  /**
   * @brief Get the input size of the layer.
   *
   * @return The input size of the layer.
   */
  std::size_t inputSize() const noexcept override;

  /**
   * @brief Get the output size of the layer.
   *
   * @return The output size of the layer.
   */
  std::size_t outputSize() const noexcept override;

  /**
   * @brief Get the output of the layer.
   *
   * @return Matrix holding the output of the layer.
   */
  const Matrix2d &output() const noexcept override;

  /**
   * @brief Get the input gradients of the layer.
   *
   * @return Matrix holding the input gradients of the layer.
   */
  const Matrix2d &inputGradients() const noexcept override;

  /**
   * @brief Perform feedforward operation.
   *
   * @param[in] input Matrix holding input data.
   *
   * @return True on success, false on failure.
   */
  bool feedforward(const Matrix2d &input) noexcept override;

  /**
   * @brief Perform backpropagation.
   *
   * @param[in] outputGradients Matrix holding gradients from the next layer.
   *
   * @return True on success, false on failure.
   */
  bool backpropagate(const Matrix2d &outputGradients) noexcept override;

  /**
   * @brief Perform optimization.
   *
   * @param[in] learningRate Learning rate to use.
   *
   * @return True on success, false on failure.
   */
  bool optimize(double learningRate) noexcept override;

  Conv() = delete;
  Conv(const Conv &) = delete;
  Conv(Conv &&) = delete;
  Conv &operator=(const Conv &) = delete;
  Conv &operator=(Conv &&) = delete;

private:
  void checkParameters(std::size_t inputSize, std::size_t kernelSize);
  void initialize(std::size_t inputSize, std::size_t kernelSize,
                  act_func::Type actFunc);
  std::size_t padBefore() const noexcept;

  static constexpr std::size_t kMinKernelSize{1U};
  static constexpr std::size_t kMaxKernelSize{11U};

  Matrix2d myInput;          // Last input (needed for backpropagation).
  Matrix2d myInputGradients; // Input gradients computed during backpropagation.
  Matrix2d myKernel;         // Trainable kernel weights.
  Matrix2d myOutput;         // Output after activation.
  Matrix2d myError;          // Error after applying activation derivative.
  Matrix2d myKernelGradients; // Accumulated kernel gradients.

  ActFuncPtr myActFunc; // Activation function used by this layer.
};
} // namespace ml::conv_layer
