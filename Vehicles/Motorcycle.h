#pragma once

#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "Vehicle.h"

namespace Vehicles{
    class Motorcycle : public Vehicle{
        public:
            Motorcycle(const std::string& plate);
            void displayInfo() const override;
    };
} // namespace Vehicles


#endif /*MOTORCYCLE_H*/