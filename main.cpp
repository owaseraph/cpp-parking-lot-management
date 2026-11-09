#include "include.hpp"

int main() {
    try {
        // Create a parking lot with 2 spots
        Parking::ParkingLot lot(2);

        std::cout << "\n--- INITIAL PARKING STATUS ---\n";
        lot.displayParkingStatus();

        // Create and park vehicles
        lot.parkVehicle(
            std::make_unique<Vehicles::Car>("CJ-10-ABC")
        );

        lot.parkVehicle(
            std::make_unique<Vehicles::Motorcycle>("CJ-20-XYZ")
        );

        std::cout << "\n--- AFTER PARKING TWO VEHICLES ---\n";
        lot.displayParkingStatus();

        // TEST 1: Try parking a duplicate vehicle
        std::cout << "\n--- TEST 1: DUPLICATE VEHICLE ---\n";
        try {
            lot.parkVehicle(
                std::make_unique<Vehicles::Car>("CJ-10-ABC")
            );
        }
        catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << '\n';
        }

        // TEST 2: Try parking when the lot is full
        std::cout << "\n--- TEST 2: PARKING LOT FULL ---\n";
        try {
            lot.parkVehicle(
                std::make_unique<Vehicles::Car>("CJ-30-DEF")
            );
        }
        catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << '\n';
        }

        // TEST 3: Remove an existing vehicle
        std::cout << "\n--- TEST 3: REMOVE VEHICLE ---\n";
        lot.removeVehicle("CJ-10-ABC");
        lot.displayParkingStatus();

        // TEST 4: Try removing a nonexistent vehicle
        std::cout << "\n--- TEST 4: REMOVE NONEXISTENT VEHICLE ---\n";
        try {
            lot.removeVehicle("CJ-99-XXX");
        }
        catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << '\n';
        }

        // TEST 5: Try removing the same vehicle again
        std::cout << "\n--- TEST 5: REMOVE VEHICLE TWICE ---\n";
        try {
            lot.removeVehicle("CJ-10-ABC");
        }
        catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << '\n';
        }

        // TEST 6: Verify that the freed spot can be reused
        std::cout << "\n--- TEST 6: REUSE AVAILABLE SPOT ---\n";
        lot.parkVehicle(
            std::make_unique<Vehicles::Car>("CJ-30-DEF")
        );
        lot.displayParkingStatus();
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}