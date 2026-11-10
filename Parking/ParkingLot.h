#pragma once
#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <vector>
#include <cstddef>
#include <memory>
#include <string>
#include "Vehicles/Vehicle.h"
#include "ParkingSpot.h"
#include "ParkingTicket.h"

namespace Parking{
    class ParkingLot{
        private:
            std::vector<std::unique_ptr<Vehicles::Vehicle>> vehicles;
            std::vector<ParkingSpot> spots;
            int nextTicketID = 1;
            std::vector<ParkingTicket> activeTickets;
        public:
            ParkingLot(int numberOfSpots);
            std::size_t getAvailableSpots() const;
            ParkingSpot* findAvailableSpot();
            ParkingTicket parkVehicle(std::unique_ptr<Vehicles::Vehicle>&& newVehicle);
            void removeVehicle(const std::string& licensePlate);
            void displayParkingStatus() const;

    };
}
#endif /*PARKINGLOT_H*/