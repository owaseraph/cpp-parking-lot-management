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

int main() {
    try {
        Parking::ParkingLot lot(2);

        // Test 1: Initial available spots
        check(lot.getAvailableSpots() == 2,
              "Initial available spots should be 2");

        // Test 2: Park a car and verify its ticket
        auto carTicket = lot.parkVehicle(
            std::make_unique<Vehicles::Car>("CJ-10-ABC")
        );

        check(lot.getAvailableSpots() == 1,
              "Available spots should be 1 after parking");

        check(carTicket.getTicketID() == 1,
              "First ticket ID should be 1");

        check(carTicket.getLicensePlate() == "CJ-10-ABC",
              "Ticket should contain the correct license plate");

        check(carTicket.getSpotID() == 1,
              "First ticket should reference spot 1");

        // Test 3: Park a motorcycle and verify its ticket
        auto motorcycleTicket = lot.parkVehicle(
            std::make_unique<Vehicles::Motorcycle>("SV-94-RAI")
        );

        check(lot.getAvailableSpots() == 0,
              "Available spots should be 0");

        check(motorcycleTicket.getTicketID() == 2,
              "Second ticket ID should be 2");

        check(motorcycleTicket.getLicensePlate() == "SV-94-RAI",
              "Ticket should contain the correct license plate");

        check(motorcycleTicket.getSpotID() == 2,
              "Second ticket should reference spot 2");

        // Test 4: Duplicate vehicle
        checkThrows(
            [&]() {
                lot.parkVehicle(
                    std::make_unique<Vehicles::Car>("CJ-10-ABC")
                );
            },
            "Parking a duplicate vehicle should throw"
        );

        // Test 5: Parking lot full
        checkThrows(
            [&]() {
                lot.parkVehicle(
                    std::make_unique<Vehicles::Car>("CJ-30-DEF")
                );
            },
            "Parking when the lot is full should throw"
        );

        check(lot.getAvailableSpots() == 0,
              "Available spots should remain 0 after failed parking");

        // Test 6: Remove an existing vehicle
        lot.removeVehicle("CJ-10-ABC");

        check(lot.getAvailableSpots() == 1,
              "Available spots should be 1 after removal");

        // Test 7: Remove nonexistent vehicle
        checkThrows(
            [&]() {
                lot.removeVehicle("AB-30-DEF");
            },
            "Removing a nonexistent vehicle should throw"
        );

        // Test 8: Remove the same vehicle twice
        checkThrows(
            [&]() {
                lot.removeVehicle("CJ-10-ABC");
            },
            "Removing the same vehicle twice should throw"
        );

        // Test 9: Reuse an available spot
        auto replacementTicket = lot.parkVehicle(
            std::make_unique<Vehicles::Car>("CJ-30-DEF")
        );

        check(lot.getAvailableSpots() == 0,
              "Available spots should be 0 after reusing the spot");

        check(replacementTicket.getTicketID() == 3,
              "Third ticket ID should be 3");

        check(replacementTicket.getLicensePlate() == "CJ-30-DEF",
              "Ticket should contain the correct license plate");

        check(replacementTicket.getSpotID() == 1,
              "The reused spot should have ID 1");

        std::cout << "All tests passed!\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << '\n'; 
        return 1;
    }
}

