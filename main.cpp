#include "include.hpp"

int main() {
    try {
        // Create a parking lot with 2 spots
        Parking::ParkingLot lot(2);
        auto ticket1 = lot.parkVehicle(
            std::make_unique<Vehicles::Car>("CJ-10-ABC"));

        auto ticket2 = lot.parkVehicle(
            std::make_unique<Vehicles::Motorcycle>("CJ-69-SEX")
        );

        std::cout << "Ticket ID: " << ticket1.getTicketID() << '\n';
        std::cout << "License plate: " << ticket1.getLicensePlate() << '\n';
        std::cout << "Spot ID: " << ticket1.getSpotID() << '\n';

        std::cout << "Ticket ID: " << ticket2.getTicketID() << '\n';
        std::cout << "License plate: " << ticket2.getLicensePlate() << '\n';
        std::cout << "Spot ID: " << ticket2.getSpotID() << '\n';
    }
    catch(std::exception& e){
        std::cerr<<"Error: "<<e.what()<<"\n";
    }
    return 0;
}