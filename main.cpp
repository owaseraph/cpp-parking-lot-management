#include "include.hpp"
int main() {

    try {
        Parking::ParkingLot lot(2);

        Vehicles::Car car1("CJ-10-ABC");
        Vehicles::Motorcycle bike1("CJ-20-XYZ");
        Vehicles::Car car2("CJ-30-DEF");

        lot.parkVehicle(car1);
        lot.parkVehicle(bike1);

        lot.displayParkingStatus();

        // Should throw: duplicate vehicle
        lot.parkVehicle(car1);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}