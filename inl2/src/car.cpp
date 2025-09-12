#include "car.h"


namespace vehicle {

//--------------------------------------------------------------------------------//
Car::Car(const std::string& brand,
    const std::string& model,
    const std::string& color,
    unsigned yearOfLaunch,
    TransmissionType transmission) noexcept
    : myBrand{brand},
      myModel{model},
      myColor{color},
      myYearOfLaunch{yearOfLaunch},
      myTransmissionType{transmission}
{
}

//--------------------------------------------------------------------------------//
const std::string& Car::getBrand() const noexcept
{
    return myBrand;
}

//--------------------------------------------------------------------------------//
const std::string& Car::getModel() const noexcept
{
    return myModel;
}

//--------------------------------------------------------------------------------//
const std::string& Car::getColor() const noexcept
{
    return myColor;
}

//--------------------------------------------------------------------------------//
unsigned Car::getYearOfLaunch() const noexcept
{
    return myYearOfLaunch;
}

//--------------------------------------------------------------------------------//
TransmissionType Car::getTransmissionType() const noexcept
{
    return myTransmissionType;
}

//--------------------------------------------------------------------------------//
void Car::setColor(const std::string& color) noexcept
{
    myColor = color;
}

//--------------------------------------------------------------------------------//
void Car::setTransmissionType(TransmissionType Transmission) noexcept
{
    myTransmissionType = Transmission;
}

//--------------------------------------------------------------------------------//
void Car::print(std::ostream& out) const noexcept
{
    out << "--------------------------------------------------------------------------------\n";
    out << "Brand: "                << myBrand              << "\n";
    out << "Model: "                << myModel              << "\n";
    out << "Color: "                << myColor              << "\n";
    out << "Year of launch: "       << myYearOfLaunch       << "\n";
    // For enumclass
    if (myTransmissionType == TransmissionType::Manual){
        out << "Transmission type: Manual\n";
    }
    else {
        out << "Transmission type: Automatic\n";
    }
    out << "--------------------------------------------------------------------------------\n";
}

} // Namespace vehicle