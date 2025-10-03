/**
 * @brief Interface for neural network functions
 */
#pragma once
#include <vector>

namespace ml::neural_network {

class Interface
{
public:
    /**
     * @brief Delete the constructor
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Prediction method to predict the network
     * 
     * @param [in] input Reference to a double vector containing 
     * the data the prediction should be based on.
     * 
     * @return The predictet value.
     */
    virtual const std::vector<double>& predict(const std::vector<double>& input) = 0;
};
} // namespace ml::neural_network