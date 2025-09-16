#include "ml/lin_reg/lin_reg.h"
#include <vector>
#include <cmath>
#include <algorithm> // for std::shuffle
#include <random>

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
    myIndex.reserve(myTrainSetCount); // Tell vector how many elements it will contain to not allocate vector. 

    // Loop to add the indexes in the trainingdata to the vector myIndex.
    for (std::size_t i{0}; i < myTrainSetCount; i++)
    {
        myIndex.push_back(i);
    }
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
        shuffleIndex();
        for (std::size_t k{}; k < myTrainSetCount; k++)
        {
            const std::size_t i = myIndex[k];
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
        shuffleIndex();
        for (std::size_t k{}; k < myTrainSetCount; k++)
        {
            // Use random index.
            const std::size_t i = myIndex[k];

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
    //! @note  Kör gärna yoda här, precis som ovan (if 0U == myEpochsUsed).
    if (myEpochsUsed == 0)
    { 
        return myEpochCount;
    } 
    return myEpochsUsed;

    //! @note Vill bara påpeka att du även kan skriva följande om du vill hålla det mer kompakt:
    //! return 0U == myEpochsUser ? myEpochCount : myEpochsUsed;
    //! Detta är dock inte bättre än vad du gjorde på något sätt.
}
//--------------------------------------------------------------------------------//
void LinReg::shuffleIndex() noexcept
{
    static std::mt19937 gen{std::random_device{}()};
    std::shuffle(myIndex.begin(), myIndex.end(), gen);

}
} //namespace ml::lin_reg
