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
            throw std::invalid_argument("Invalid number of spots");
        }
        vehicles.reserve(numberOfSpots);
        activeTickets.reserve(numberOfSpots);
        spots.reserve(numberOfSpots);
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
        activeTickets.push_back(ticket);
        vehicles.push_back(std::move(newVehicle));
        parkSpot->parkVehicle(*vehiclePtr);
        ++nextTicketID;
        return ticket;
    }


    /// @brief removes a vehicle based on its license plate
    /// @param licensePlate license plate of the specified vehicle to be removed
    void ParkingLot::removeVehicle(const std::string& licensePlate) {
        // Find the vehicle
        const auto vehicleIt = std::find_if(
            vehicles.begin(),
            vehicles.end(),
            [&licensePlate](const auto& vehicle) {
                return vehicle->getLicensePlate() == licensePlate;
            }
        );

        if (vehicleIt == vehicles.end()) {
            throw std::logic_error("This vehicle is not parked in this lot");
        }

        // Find its active ticket
        const auto ticketIt = std::find_if(
            activeTickets.begin(),
            activeTickets.end(),
            [&licensePlate](const auto& ticket) {
                return ticket.getLicensePlate() == licensePlate;
            }
        );

        if (ticketIt == activeTickets.end()) {
            throw std::logic_error("There is no active ticket for this vehicle");
        }

        // Get the vehicle's raw pointer
        Vehicles::Vehicle* vehiclePtr = vehicleIt->get();

        // Find the corresponding parking spot
        const auto spotIt = std::find_if(
            spots.begin(),
            spots.end(),
            [vehiclePtr](const auto& spot) {
                return spot.getVehicle() == vehiclePtr;
            }
        );

        if (spotIt == spots.end()) {
            throw std::logic_error("Vehicle is not assigned to a parking spot");
        }

        // Clear the parking spot
        spotIt->removeVehicle();

        // Remove the active ticket
        activeTickets.erase(ticketIt);

        // Destroy the vehicle
        vehicles.erase(vehicleIt);
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