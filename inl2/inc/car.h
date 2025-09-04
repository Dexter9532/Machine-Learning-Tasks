#pragma once
#include <string> //for std::string
#include <iostream> // for std::ostream

namespace vehicle {

enum class TransmissionType{
    Manual,
    Automatic
};
/**
 * @brief Carclass that holds basic info about a vehicle.
 */
class Car
{
public:

//--------------------------------------------------------------------------------//

explicit Car(const std::string& brand,                          // Carbrand.
    const std::string& model,                                   // Carmodel.
    const std::string& color,                                   // Carcolor.
    unsigned yearOfLaunch,                                      // Year the car was launched.
    TransmissionType transmission = TransmissionType::Manual);  // Transmissiontype, Automatic or Manual.

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
const std::string& getBrand() const;

//--------------------------------------------------------------------------------//
/**
 * @brief Get-method to see what the carmodel is.
 */
const std::string& getModel() const;

//--------------------------------------------------------------------------------//
/**
 * @brief Get-method to see what the carcolor is.
 */
const std::string& getColor() const;

//--------------------------------------------------------------------------------//
/**
 * @brief Get-method to see what the year the car was launched is.
 */
unsigned getYearOfLaunch() const;

 //--------------------------------------------------------------------------------//
 /**
 * @brief Get-method to see what the year the car was launched is.
 */
TransmissionType getTransmissionType() const;

//--------------------------------------------------------------------------------//
/**
 * @brief Set-method to see what the carcolor is.
 */
void setColor(const std::string& color);

//--------------------------------------------------------------------------------//
/**
 * @brief Set-method to see what the cars transmissiontype is.
 */
void setTransmissionType(TransmissionType color);

//--------------------------------------------------------------------------------//
/**
 * @brief Print function to print all the info about the car.
 */
void print(std::ostream& out = std::cout) const;


private:

std::string myBrand; // Save given carbrand.
std::string myModel; // Save given model.
std::string myColor; // Save given color.
unsigned myYearOfLaunch = 0; // Save given year of the launch, defalut is 0.
TransmissionType myTransmissionType; // Save transmissiontype, default is Manual.

};


} // Namespace vehicle