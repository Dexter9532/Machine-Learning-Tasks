#include "ml/lin_reg/lin_reg.h"
#include <vector>
#include <cmath>

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

    while (!isPredictDone())
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
            
            myPredVector[i] = predict(myTrainInput[i]);
        }
        // Save epochs used.
        myEpochsUsed++;
    }
    return true;    
}
//--------------------------------------------------------------------------------//
bool LinReg::train(const std::size_t epochCount, double learningRate) noexcept
{
    if ((0U == epochCount) || (0.0 >= learningRate)) { return false;}
    
    myEpochCount = epochCount;   

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
bool LinReg::isPredictDone() const noexcept
{
    constexpr double tol = 1e-6;
    for (std::size_t i{}; i < myTrainSetCount; ++i)
    {
        if (std::abs(myPredVector[i] - myTrainOutput[i]) > tol)
        {
            return false;
        }
    }
    return true;
}
//--------------------------------------------------------------------------------//
int LinReg::getEpochsUsed() const noexcept 
{
    if (myEpochsUsed == 0)
    { 
        return myEpochCount;
    } 
    return myEpochsUsed;
}
//--------------------------------------------------------------------------------//
} //namespace ml::lin_reg

