// -----------------------------------------------------------------------------
/**
 * @brief Function to train the modell
 * 
 * @param [in] input The data that is going to be trained, (x value in kx + m = y).
 * @param [in] reference The data that the module should aim for, (y value in kx + m = y).
 * @param [in] learingrate The speed in % the module should train in.
 */
void LinReg::optimize(const double input, const double reference, const double learningRate) noexcept  
{ 
    // if x = 0, m = y, for faster learing.
    if (0.0 == input) { 
        myBias -= reference; 
    } 
    else 
    { 
        const auto error{reference - predict(input)};   // e value set = y - ypred. Set the error margin for the predicted value.
        myBias -= error * learningRate;                 // m value set = e * lr. Set the new bias value for next prediction. 
        myWeight -= error * learningRate + input;       // k value set = e * lr + x. Set the new weight value for next prediction.
    } 
} 

// The function will not work due to these rows:
// row-19. Should be instedad myWeight -= error * learningRate * input;
// row-12. The if-statement is not needed, bias should always update from error.
