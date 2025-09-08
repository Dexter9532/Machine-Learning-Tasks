/**
 * @brief Interface for linear regression algorithms.
 */

namespace ml::lin_reg {

class Interface
{
public:
    /**
     * @brief Delete the constructor.
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Predict module
     * 
     * @param[in] input The given data is what the module should base it´s predict on.
     * 
     * @return The predict value of given data.
     */
    virtual double predict(const double input) const = 0;

};
} // Namespace ml::lin_reg