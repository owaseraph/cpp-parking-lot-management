#ifndef PARKINGSPOT_CPP
#define PARKINGSPOT_CPP
#include "ParkingSpot.h"
#include <stdexcept>
namespace Parking{
    ParkingSpot::ParkingSpot(int id):spotID(id),vehicle(nullptr){
        if(id <= 0){
            throw std::invalid_argument("ID cannot be less than 0");
        }
    };
    void ParkingSpot::parkVehicle(Vehicles::Vehicle& newVehicle){
        if(this->isOccupied()){
            throw std::logic_error("Occupied spot");
        }
        this->vehicle=&newVehicle;
    }
    void ParkingSpot::removeVehicle(){
        if(this->vehicle==nullptr){
            throw std::logic_error("No vehicle in this spot");
        }
        this->vehicle=nullptr;
    }
    bool ParkingSpot::isOccupied() const{
        return (this->vehicle!=nullptr);
    }

    Vehicles::Vehicle* ParkingSpot::getVehicle() const{
        return this->vehicle;
    }

    //getter
    int ParkingSpot::getSpotID() const{
        return this->spotID;
    }
}
#endif /*PARKINGSPOT_CPP*/