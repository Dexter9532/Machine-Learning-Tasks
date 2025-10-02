/**
 * @brief Cpp-file for neural network functions
 */
#pragma once 
#include "ml/dense_layer/interface.h"
#include "ml/dense_layer/single_layer.h"

namespace ml::neural_network {

//--------------------------------------------------------------------------------//  
SingleLayer::SingleLayer(ml::dense_layer::Interface& hiddenLayer,
                        ml::dense_layer::Interface& outputLayer,
                        std::vector<std::vector<double>>& trainInput,
                        std::vector<std::vector<double>>& trainOutput)
                :   myHiddenLayer{hiddenLayer},
                    myOutputLayer{outputLater},
                    myTrainInput{trainInput},
                    myTrainOutput{trainOutput},
                    myTrainSetCount(static_cast<unsigned>(
                    std::min(trainInput.size(), trainOutput.size()))),
                    

//--------------------------------------------------------------------------------//  
~SingleLayer() noexcept override = default;
//--------------------------------------------------------------------------------//
const std::vector<double>& predict(const std::vector<double>& input) const noexcept override;
//--------------------------------------------------------------------------------//
bool train(double learningrate = 0) noexcept;
} // namespace ml::neural_network