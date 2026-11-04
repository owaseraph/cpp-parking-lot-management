#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
namespace Vehicles{
    class Vehicle{
        private:
            std::string licensePlate;
        public:
            Vehicle(const std::string& plate);
            virtual void displayInfo() const=0;
            virtual ~Vehicle();

            //getter
            std::string getLicensePlate() const;
    };
}


#endif /*VEHICLE_H*/