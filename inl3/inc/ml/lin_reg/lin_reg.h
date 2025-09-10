/**
 * @brief File to define the subclass named LinReg
 */
#pragma once
#include "ml/lin_reg/interface.h"
#include <vector>
#include <algorithm> // for std::min


namespace ml::lin_reg
{
/**
 * @brief Class LinReg that inherits from the Class Interface
 * 
 * @note The class is final.
 */
class LinReg final: public Interface
{
public:
    /**
     * @brief Constructor LinReg.
     * 
     * @param [in] trainInput Reference to a readble vector, (data that is going to be traded).
     * @param [in] tainOutput Reference to a readble vector, (data that is going to be traded).
     */
    explicit LinReg(const std::vector<double>& trainInput,
                    const std::vector<double>& trainOutput) noexcept;

    /**
     * @brief Delete the constructor as default.
     */
    ~LinReg() noexcept override = default;

    /**
     * @brief Predict module
     * 
     * @param[in] input The given data is what the module should base it´s predict on.
     * 
     * @return The predict value of given data.
     */
    double predict(const double input) const noexcept override;

    /**
     * @brief Method to train the module.
     * 
     * @param [in] epochCount Indicates how many epochs that will be used.
     * @param [in] learingRate Learingrate speed, default is 0.01 or 1%.
     */
    bool train(const std::size_t epochCount = 1U, double learningRate = 0.01) noexcept;

    LinReg() = delete;                            // Delete a car without info.
    LinReg(const LinReg&) = delete;               // Delete copy constructor.
    LinReg& operator=(const LinReg&) = delete;    // Delete copy assignment.
    LinReg(LinReg&&) = delete;                    // Delete move constructor.
    LinReg& operator=(LinReg&&) = delete;         // Delete move assignment.

private:
        const std::vector<double>& myTrainInput;            // Reference to the training data (input data).
        const std::vector<double>& myTrainOutput;           // Reference to the training data (output data).
        const unsigned myTrainSetCount;                     // Indicates the total of full trainingset that are avalible.
        double myBias;                                      // Bias value for the module, (m) in the ecvation kx + m = y.
        double myWeight;                                    // Weight value for the module, (k) in the ecvation kc + m = y.

};
} // Namespace ml::lin_reg