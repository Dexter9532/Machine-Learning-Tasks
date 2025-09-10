#include "ml/lin_reg/lin_reg.h"
#include <vector>

namespace ml::lin_reg
{
//--------------------------------------------------------------------------------//
LinReg::LinReg(const std::vector<double>& trainInput,
               const std::vector<double>& trainOutput) noexcept
                :   myTrainInput{trainInput},
                    myTrainOutput{trainOutput},  
                    myTrainSetCount(static_cast<unsigned>(
                    std::min(trainInput.size(), trainOutput.size()))),
                    myBias{0.5},
                    myWeight{0.5},
                    myPredVector(myTrainSetCount)
{
}   
//--------------------------------------------------------------------------------//
double LinReg::predict(const double input) const noexcept
{
    return (myWeight * input + myBias);
}
//--------------------------------------------------------------------------------//
bool LinReg::trainWithNoEpoch(double learningRate) noexcept
{
    if ((0.0 >= learningRate)) { return false;}

    while (isPredictDone(myPredVector, myTrainOutput) == false)
    {
        for (std::size_t i{}; i < myTrainSetCount; i++)
        {
            // ypred = kx + m.
            const auto yPred = predict(myTrainInput[i]);

            // e = yref - ypred.
            const auto e = (myTrainOutput[i] - yPred);

            // m = m + e * LR.
            myBias = myBias + (e * learningRate);

            // k = k + e * LR * x.
            myWeight = myWeight + (e * learningRate * myTrainInput[i]); 

            // Save epochs used.
            myEpochsUsed++;
        }
    }
    return true;    
}
//--------------------------------------------------------------------------------//
bool LinReg::train(const std::size_t epochCount, double learningRate) noexcept
{
    if ((0U == epochCount) || (0.0 >= learningRate)) { return false;}
    
    // Detta ska ska varje epok. Hur ser vi till att köra epochCount varv.
    for (std::size_t epoch{}; epoch < epochCount; epoch++)
    {
        for (std::size_t i{}; i < myTrainSetCount; i++)
        {
            // ypred = kx + m.
            const auto yPred = predict(myTrainInput[i]);

            // e = yref - ypred.
            const auto e = (myTrainOutput[i] - yPred);

            // m = m + e * LR.
            myBias = myBias + (e * learningRate);

            // k = k + e * LR * x.
            myWeight = myWeight + (e * learningRate * myTrainInput[i]); 
        }
    }
    return true;
}
//--------------------------------------------------------------------------------//
bool LinReg::isPredictDone(const std::vector<double>& yPredVector, const std::vector<double>& yPref ) const noexcept
{
    for (std::size_t i{}; i < yPredVector.size(); i++)
    {
        auto yWantedZero = (yPredVector[i] - yPref[i]);
        if (0.0 != yWantedZero )
        {
            return false;
        }
    }
return true;
}
//--------------------------------------------------------------------------------//
} //namespace ml::lin_reg

