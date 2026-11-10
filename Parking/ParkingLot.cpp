#ifndef PARKINGLOT_CPP
#define PARKINGLOT_CPP
#include "ParkingLot.h"
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <iostream>
#include <chrono>

namespace Parking{
    ParkingLot::ParkingLot(int numberOfSpots){
        if(numberOfSpots<=0){
            throw std::invalid_argument("Invalid number of lots");
        }
        for(int i=1;i<=numberOfSpots;i++){
            this->spots.emplace_back(i);
        }
    }

    std::size_t ParkingLot::getAvailableSpots() const{
        std::size_t count=0;
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

    ParkingTicket ParkingLot::parkVehicle(std::unique_ptr<Vehicles::Vehicle>&& newVehicle){
        if(!newVehicle){
            throw std::invalid_argument("Invalid vehicle");
        }
        for(const auto& parkedVehicle: vehicles){
            if(parkedVehicle->getLicensePlate()==newVehicle->getLicensePlate()){
                throw std::logic_error("This vehicle is already parked in this lot");
            }
        }
        ParkingSpot* parkSpot = findAvailableSpot();
        if(parkSpot==nullptr){
            throw std::logic_error("Parking lot is full");
        }


        //create a ParkingTicket entity to park the car and get issued an ID
        ParkingTicket ticket(
            nextTicketID,
            newVehicle->getLicensePlate(),
            parkSpot->getSpotID(),
            std::chrono::system_clock::now());
        Vehicles::Vehicle* vehiclePtr = newVehicle.get();
        vehicles.push_back(std::move(newVehicle));
        parkSpot->parkVehicle(*vehiclePtr);
        ++nextTicketID;
        return ticket;
    }

    void ParkingLot::removeVehicle(const std::string& licensePlate){
        const auto it = std::find_if(
            vehicles.begin(), 
            vehicles.end(), 
            [&licensePlate](const auto& vehicle){
                return vehicle->getLicensePlate() == licensePlate;
            }
        );
        if(it==vehicles.end()){
            throw std::logic_error("This vehicle is not parked in this lot");
        }
        Vehicles::Vehicle* vehiclePtr = it->get(); 
        for(auto& spot : spots){
            if(spot.getVehicle() == vehiclePtr){
                spot.removeVehicle();
                break;
            }
        }
        vehicles.erase(it);

    }

    void ParkingLot::displayParkingStatus() const{
        std::cout<<"========== PARKING STATUS =========="<<"\n";
        for(const auto& spot: spots){  
            std::cout<<"Spot "<<spot.getSpotID()<<": "<<(spot.isOccupied() ? "Occupied":"Available")<<"\n";
        }
        std::cout<<"\nAvailable spots: "<<ParkingLot::getAvailableSpots()<<"\n";
        std::cout<<"===================================="<<"\n";
    }
}
#endif /*PARKINGLOT_CPP*/