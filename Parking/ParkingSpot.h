#pragma once

#ifndef PARKINGSPOT_H
#define PARKINGSPOT_H

#include "Vehicles/Vehicle.h"
namespace Parking{
    class ParkingSpot{
        private:
            int spotID;
            Vehicles::Vehicle* vehicle;
        public:
            ParkingSpot(int id);
            void parkVehicle(Vehicles::Vehicle& newVehicle);
            void removeVehicle();
            bool isOccupied() const;
            Vehicles::Vehicle* getVehicle() const;

            //getter
            int getSpotID() const;
    };
}

#endif /*PARKINGSPOT_H*/