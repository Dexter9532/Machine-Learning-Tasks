#include "car.h"

int main()
{
    vehicle::Car car1("Volkswagen", "Gold", "Gray", 2002, vehicle::TransmissionType::Manual);
    car1.print();
    car1.setColor("Blue");
    car1.setTransmissionType(vehicle::TransmissionType::Automatic);
    car1.print();

}


