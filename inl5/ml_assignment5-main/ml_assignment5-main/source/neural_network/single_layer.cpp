/** @note Snyggt jobbat här med! */
/**
 * @brief Cpp-file for neural network functions
 */
#include <algorithm>
//! @note Lade till mellanrum här. Jag har samma kommentar om headersortering här med.
#include "ml/neural_network/single_layer.h"
#include "ml/dense_layer/interface.h"

namespace ml::neural_network {

//--------------------------------------------------------------------------------//  
SingleLayer::SingleLayer(ml::dense_layer::Interface& hiddenLayer,
                        ml::dense_layer::Interface& outputLayer,
                        const std::vector<std::vector<double>>& trainInput,
                        const std::vector<std::vector<double>>& trainOutput)
                //! @note Indraget är på tok för kraftigt, fyra blanka steg räcker.
                :   myHiddenLayer{hiddenLayer},
                    myOutputLayer{outputLayer},
                    myTrainInput{trainInput},
                    myTrainOutput{trainOutput},
                    myTrainSetCount(static_cast<unsigned>(
                    std::min(trainInput.size(), trainOutput.size())))
{

}
//--------------------------------------------------------------------------------//
const std::vector<double>& SingleLayer::predict(const std::vector<double>& input) noexcept
{    
    //! @note Lägg gärna inline-kommentarer ovanför funktionerna, som du gjorde i train nedan. :)
    myHiddenLayer.feedforward(input);                    // run feedforward on the hidden layer with the input values
    myOutputLayer.feedforward(myHiddenLayer.output());   // run feedforward on the output layer using the hidden layer's output as input
    return myOutputLayer.output(); 
}
//--------------------------------------------------------------------------------//
bool SingleLayer::train( std::size_t epochCount, double learningrate) noexcept
{
    //! Utmärkt med Yoda notation och parenteser.
    if ((0U == epochCount) || (0.0 >= learningrate)) { return false;}

    //! Använd hellre {} än = för initiering; std::size_t epoch{} eller std::size_t epoch{0U}.
    for (std::size_t epoch = 0; epoch < epochCount; ++epoch) 
    {
        //! @note Snyggt jobbat med koden här! :)
        for (std::size_t k{}; k < myTrainSetCount; k++)
        {
            // (a) forward: hidden then output
            if (!myHiddenLayer.feedforward(myTrainInput[k]))                   { return false; }
            if (!myOutputLayer.feedforward(myHiddenLayer.output()))            { return false; }

            // (b) backprop: output with target, then hidden with next layer
            if (!myOutputLayer.backpropagate(myTrainOutput[k]))                { return false; }
            if (!myHiddenLayer.backpropagate(myOutputLayer))                   { return false; }

            // (c) optimize: each layer with its own input source
            if (!myHiddenLayer.optimize(myTrainInput[k], learningrate))        { return false; }
            if (!myOutputLayer.optimize(myHiddenLayer.output(), learningrate)) { return false; }
        }
    }
    return true;
}
} // namespace ml::neural_network