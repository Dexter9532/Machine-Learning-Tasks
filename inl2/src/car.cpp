#include "car.h"


namespace vehicle {

Car::Car(const std::string& brand,
    const std::string& model,
    const std::string& color,
    unsigned yearOfLaunch,
    TransmissionType transmission)
    : myBrand(brand),
      myModel(model),
      myColor(color),
      myYearOfLaunch(yearOfLaunch),
      myTransmissionType(transmission)
{
}
const std::string& Car::getBrand() const 
{
    return myBrand;
}

const std::string& Car::getModel() const
{
    return myModel;
}

const std::string& Car::getColor() const
{
    return myColor;
}

unsigned Car::getYearOfLaunch() const
{
    return myYearOfLaunch;
}

TransmissionType Car::getTransmissionType() const
{
    return myTransmissionType;
}

void Car::setColor(const std::string& color)
{
    myColor = color;
}

void Car::setTransmissionType(TransmissionType Transmission)
{
    myTransmissionType = Transmission;
}

void Car::print(std::ostream& out) const
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