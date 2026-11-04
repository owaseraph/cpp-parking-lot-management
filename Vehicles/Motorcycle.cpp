#ifndef MOTORCYCLE_CPP
#define MOTORCYCLE_CPP
#include "Motorcycle.h"
#include <iostream>

namespace Vehicles{
    /// @brief Creates the Motorcycle Object
    /// @param plate the license plate of the vehicle
    Motorcycle::Motorcycle(const std::string& plate):Vehicle(plate){};
    void Motorcycle::displayInfo() const {
        std::cout<<"Motorcycle license plate: "<<getLicensePlate()<<"\n";
    }
} // namespace Vehicles


#endif /*MOTORCYCLE_CPP*/