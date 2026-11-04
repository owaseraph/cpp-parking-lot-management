#ifndef CAR_CPP
#define CAR_CPP
#include "Car.h"
#include <iostream>
namespace Vehicles{
    /// @brief Creates the Car Object
    /// @param plate the license plate of the vehicle
    Car::Car(const std::string& plate):Vehicle(plate){}
    void Car::displayInfo() const {
        std::cout<<"Car license plate: "<<getLicensePlate()<<"\n";
    }
}
#endif /*CAR_CPP*/