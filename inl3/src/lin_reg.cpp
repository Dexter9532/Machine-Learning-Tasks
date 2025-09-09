#include "ml/lin_reg/lin_reg.h"

namespace ml::lin_reg
{
//--------------------------------------------------------------------------------//
LinReg::LinReg( const std::vector<double>& trainInput,
                const std::vector<double>& trainOutput) noexcept
                :   myTrainInput{trainInput},
                    myTrainOutput{trainOutput},  
                    myTrainSetCount(static_cast<unsigned>(
                    std::min(trainInput.size(), trainOutput.size()))),
                    myBias{0.5},
                    myWeight{0.5}
{
}   
//--------------------------------------------------------------------------------//
double LinReg::predict(const double input) const noexcept
{
    return (myWeight * input + myBias);
}
//--------------------------------------------------------------------------------//
bool LinReg::train(unsigned epochCount, double learningRate) noexcept
{
    if (epochCount == 0 || learningRate <= 0.0) {return false;}

    return true;
}
//--------------------------------------------------------------------------------//
} //namespace ml::lin_reg

