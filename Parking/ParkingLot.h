#pragma once
#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <vector>
#include "ParkingSpot.h"

namespace Parking{
    class ParkingLot{
        private:
            std::vector<ParkingSpot> spots;
        public:
            ParkingLot(int numberOfLots);
            std::size_t getAvailableSpots() const;
            ParkingSpot* findAvailableSpot();
            void parkVehicle(Vehicles::Vehicle& newVehicle);
            void removeVehicle(const std::string& licensePlate);
            void displayParkingStatus() const;

    };
}
#endif /*PARKINGLOT_H*/