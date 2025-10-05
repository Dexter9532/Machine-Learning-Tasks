/** @note Din SingleLayer-klasser är också utmärkt! Jag har några små kommentarer dock, se nedan. */

/**
 * @brief Header-file for neural network functions
 */
#pragma once 

//! @note Du bör inkludera <vector> här istället för att förlita dig på att denna är inkluderad i 
//!       interfacet. Bästa praxis är att inkludera alla headers som används direkt för att
//!       dependencies (och undvika varningar från kodanalysverktyg och dylikt).

//! @note Sortera headerfiler alfabetiskt.
#include "ml/neural_network/interface.h"
#include "ml/dense_layer/interface.h"

namespace ml::neural_network {

class SingleLayer final: public ml::neural_network::Interface
{
public:
    /**
     * @brief Constructor SignleLayer
     * 
     * @param [in] hidden The hidden layer in the neural network.
     * @param [in] output The output layer in the neural network.
     * @param [in] trainInput The Input data that the model should train.
     * @param [in] trainOutput The output data that the model should be trained to predict. 
     */
    explicit SingleLayer(ml::dense_layer::Interface& hiddenLayer,
                        ml::dense_layer::Interface& outputLayer,
                        const std::vector<std::vector<double>>& trainInput,
                        const std::vector<std::vector<double>>& trainOutput);

    //! @note Destruktorn raderar inte konstruktorn; den raderar instansen som konstruktorn har skapat.
    //!       Men det är ingen biggie; det räcket att skriva @brief Destructor på destruktorer anser jag.
    /**
     * @brief Delete the constructor
     */
    ~SingleLayer() noexcept override = default;

    /**
     * @brief Prediction method to predict the network
     * 
     * @param [in] input Reference to a double vector containing 
     * the data the prediction should be based on.
     * 
     * @return The predictet value.
     */
    const std::vector<double>& predict(const std::vector<double>& input) noexcept override;

    /**
     * @brief Train the model.
     * 
     * @param [in] learningRate The speed the model should correct the errors in, 0.01 as default.
     * 
     * @return True if traingen is done, or False if not.
     */
    bool train(std::size_t epochCount, double learningrate = 0) noexcept;

    /**
     * @brief Delete not wanted constructors.
     */
    SingleLayer() = delete;                                 // Delete a car without info.
    SingleLayer(const SingleLayer&) = delete;               // Delete copy constructor.
    SingleLayer& operator=(const SingleLayer&) = delete;    // Delete copy assignment.
    SingleLayer(SingleLayer&&) = delete;                    // Delete move constructor.
    SingleLayer& operator=(SingleLayer&&) = delete;         // Delete move assignment.

private:

    ml::dense_layer::Interface& myHiddenLayer;              // Reference for the hiddenlayer from the interface.
    ml::dense_layer::Interface& myOutputLayer;              // Reference for the outputlayer from the interface.
    const std::vector<std::vector<double>>& myTrainInput;   // Reference to the traininginput.
    const std::vector<std::vector<double>>& myTrainOutput;  // Reference to the trainingoutput.
    const unsigned myTrainSetCount;                         // Indicates the amount of trainingsetups avalible.
};
} // namespace ml::neural_network