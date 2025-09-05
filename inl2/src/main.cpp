#include "car.h"
#include  <vector>
#include <fstream>


int main()
{
    // G-part
    vehicle::Car car1("Volkswagen", "Gold", "Gray", 2002, vehicle::TransmissionType::Manual);
    car1.print();
    car1.setColor("Blue");
    car1.setTransmissionType(vehicle::TransmissionType::Automatic);
    car1.print();

    // VG-part
    vehicle::Car car2("Volvo", "V70", "Black", 1995, vehicle::TransmissionType::Manual);
    vehicle::Car car3("BWM", "Z3", "Blue", 2001, vehicle::TransmissionType::Automatic);
    vehicle::Car car4("Skoda", "Octavia RS", "White", 2003, vehicle::TransmissionType::Manual);

    std::vector<vehicle::Car*> cars{&car2, &car3, &car4};

    std::cout << "VG-del!\n\n\n";

    for (auto& car : cars)
    {
        car->setColor("Red");
    }

    for (const auto& car : cars)
    {
        car->print();
    }
    // Write to file "Cars.txt"
    std::ofstream file("Cars.txt");
    for (const auto& car : cars)
    {
        car->print(file);
    }
}


