#pragma once
#include <string> //for std::string
#include <iostream> // for std::ostream

namespace vehicle {

/**
 * @brief Enumeration of transmission types.
 */
enum class TransmissionType{
    Manual, // Manual transmission.
    Automatic // Automatic transmission.
};
/**
 * @brief Carclass that holds basic info about a vehicle.
 */
class Car final
{
public:

//--------------------------------------------------------------------------------//

    explicit Car(const std::string& brand,                                      // Carbrand.
        const std::string& model,                                               // Carmodel.
        const std::string& color,                                               // Carcolor.
        unsigned yearOfLaunch,                                                  // Year the car was launched.
        TransmissionType transmission = TransmissionType::Manual) noexcept;     // Transmissiontype, Automatic or Manual.

//--------------------------------------------------------------------------------//

    ~Car() = default;                       // Destructor.
//--------------------------------------------------------------------------------//

    Car() = delete;                         // Delete a car without info.
    Car(const Car&) = delete;               // Delete copy constructor.
    Car& operator=(const Car&) = delete;    // Delete copy assignment.
    Car(Car&&) = delete;                    // Delete move constructor.
    Car& operator=(Car&&) = delete;         // Delete move assignment.

//--------------------------------------------------------------------------------//
    /**
     * @brief Get-method to see what the carbrand is.
     */
    const std::string& getBrand() const noexcept;

//--------------------------------------------------------------------------------//
    /**
     * @brief Get-method to see what the carmodel is.
     */
    const std::string& getModel() const noexcept;

//--------------------------------------------------------------------------------//
    /**
     * @brief Get-method to see what the carcolor is.
     */
    const std::string& getColor() const noexcept;

//--------------------------------------------------------------------------------//
    /**
     * @brief Get-method to see what the year the car was launched is.
     */
    unsigned getYearOfLaunch() const noexcept;

//--------------------------------------------------------------------------------//
    /**
     * @brief Get-method to see what the year the car was launched is.
     */
    TransmissionType getTransmissionType() const noexcept;

//--------------------------------------------------------------------------------//
    /**
     * @brief Set-method to see what the carcolor is.
     */
    void setColor(const std::string& color) noexcept;

//--------------------------------------------------------------------------------//
    /**
     * @brief Set-method to see what the cars transmissiontype is.
     */
    void setTransmissionType(TransmissionType color) noexcept;

//--------------------------------------------------------------------------------//
    /**
     * @brief Print function to print all the info about the car.
     */
    void print(std::ostream& out = std::cout) const noexcept;


private:

    std::string myBrand; // Save given carbrand.
    std::string myModel; // Save given model.
    std::string myColor; // Save given color.
    unsigned myYearOfLaunch = 0; // Save given year of the launch, defalut is 0.
    TransmissionType myTransmissionType; // Save transmissiontype, default is Manual.

};
} // Namespace vehicle