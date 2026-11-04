#ifndef PARKINGLOT_CPP
#define PARKINGLOT_CPP
#include "ParkingLot.h"
#include <stdexcept>
#include <iostream>

namespace Parking{
    ParkingLot::ParkingLot(int numberOfLots){
        if(numberOfLots<=0){
            throw std::invalid_argument("Invalid number of lots");
        }
        for(int i=1;i<=numberOfLots;i++){
            this->spots.emplace_back(i);
        }
    }

    std::size_t ParkingLot::getAvailableSpots() const{
        size_t count=0;
        for(const auto& spot:spots){
            if(!spot.isOccupied()){
                count++;
            }
        }
        return count;
    }

    ParkingSpot* ParkingLot::findAvailableSpot(){
        for(auto& spot: spots){
            if(!spot.isOccupied()){
                return &spot;
            }
        }
        return nullptr;
    }

    void ParkingLot::parkVehicle(Vehicles::Vehicle& newVehicle){
        for(const auto& spot: spots){
            if(spot.isOccupied()){
                if(spot.getVehicle()->getLicensePlate()==newVehicle.getLicensePlate()){
                    throw std::logic_error("This vehicle is already parked in this lot");
                }
            }
        }
        ParkingSpot* parkSpot = findAvailableSpot();
        if(parkSpot==nullptr){
            throw std::logic_error("Parking lot is full");
        }
        parkSpot->parkVehicle(newVehicle);
    }

    void ParkingLot::removeVehicle(const std::string& licensePlate){
        for(auto& spot: spots){
            if(spot.isOccupied()){
                if(spot.getVehicle()->getLicensePlate()==licensePlate){
                    spot.removeVehicle();
                    return;
                }
            }
        }
        throw std::logic_error("This vehicle is not parked in this lot");
    }

    void ParkingLot::displayParkingStatus() const{
        std::cout<<"========== PARKING STATUS =========="<<"\n";
        for(auto& spot: spots){  
            std::cout<<"Spot "<<spot.getSpotID()<<": "<<(spot.isOccupied() ? "Occupied":"Available")<<"\n";
        }
        std::cout<<"\nAvailable spots: "<<ParkingLot::getAvailableSpots()<<"\n";
        std::cout<<"===================================="<<"\n";
    }
}
#endif /*PARKINGLOT_CPP*/