#include <iostream>
#include <memory>
#include <stdexcept>

#include "Vehicles/Car.h"
#include "Vehicles/Motorcycle.h"
#include "Parking/ParkingLot.h"

void check(bool condition, const std::string& message){
    if(!condition){
        throw std::runtime_error(message);
    }
}

template<typename Function>
void checkThrows(Function function, const std::string& message){
    try{
        function();
    }
    catch(const std::logic_error&){
        return;
    }
    throw std::runtime_error(message);
}

int main(){
    try{
        Parking::ParkingLot lot(2);
        
        //Test 1: Initial available spots
        check(lot.getAvailableSpots()==2, "Initial available spots should be 2");

        //Test 2: Park a vehicle
        lot.parkVehicle(std::make_unique<Vehicles::Car>("CJ-10-ABC"));
        check(lot.getAvailableSpots()==1, "Available spots should be 1 after parking");

        //Test 3: Full parking lot
        lot.parkVehicle(std::make_unique<Vehicles::Motorcycle>("SV-94-RAI"));
        check(lot.getAvailableSpots()==0, "Available spots should be 0 after parking is full");

        // Test: Duplicate vehicle
        checkThrows(
            [&]() {
                lot.parkVehicle(
                    std::make_unique<Vehicles::Car>("CJ-10-ABC")
                );
            },
            "Parking a duplicate vehicle should throw"
        );

        // Test: Parking lot full
        checkThrows(
            [&]() {
                lot.parkVehicle(
                    std::make_unique<Vehicles::Car>("SV-94-RAI")
                );
            },
            "Parking when the lot is full should throw"
        );

        check(lot.getAvailableSpots() == 0,
            "Available spots should remain 0");

        //Test 4: Remove the vehicle
        lot.removeVehicle("CJ-10-ABC");
        check(lot.getAvailableSpots()==1, "Available spots should be 1 after removal");

        //Test 5: Removing non-existent vehicle
        checkThrows(
            [&](){
                lot.removeVehicle("AB-30-DEF");
            },
            "Removing a nonexistent vehicle should throw"
        );

        //Test 6: Reusing available spots
        lot.parkVehicle(std::make_unique<Vehicles::Car>("CJ-10-ABC"));
        check(lot.getAvailableSpots()==0, "Available spots should be 0 after parking is full");

        std::cout<<"All test passed!";
        return 0;
    }
    catch(const std::exception& e){
        std::cerr<<"Test failed: "<<e.what()<<"\n";
        return 1;
    }
}

