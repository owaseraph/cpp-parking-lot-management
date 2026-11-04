#ifndef VEHICLE_CPP
#define VEHICLE_CPP
#include "Vehicle.h"
#include <cctype>
#include <stdexcept>
#include <algorithm>
namespace Vehicles{
    /// @brief instantiates the vehicle object with validations
    /// @param plate license plate of the vehicle 
    Vehicle::Vehicle(const std::string& plate):licensePlate(plate){
        if (plate.empty() || std::all_of(plate.begin(), plate.end(),[](unsigned char c) {return std::isspace(c);})) {
            throw std::invalid_argument("Invalid license plate");
        };
    }

    Vehicle::~Vehicle() = default;

    //getter
    std::string Vehicle::getLicensePlate() const{
        return this->licensePlate;
    }
    
}
#endif /*VEHICLE_CPP*/