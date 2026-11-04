#pragma once

#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"
namespace Vehicles{
    class Car : public Vehicle{
        public:
            Car(const std::string& plate);
            void displayInfo() const override;
    };
    
}

#endif /*CAR_H*/