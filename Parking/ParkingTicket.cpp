#ifndef _PARKINGTICKET_CPP
#define _PARKINGTICKET_CPP

#include "ParkingTicket.h"

namespace Parking{
    ParkingTicket::ParkingTicket(int ticketID, const std::string& licensePlate, int spotID, TimePoint entryTime):
        ticketID(ticketID),
        licensePlate(licensePlate),
        spotID(spotID),
        entryTime(entryTime){
            if(ticketID<=0){
                throw std::invalid_argument("TicketID must be greater than 0");
            }
            if(spotID<=0){
                throw std::invalid_argument("SpotID must be greater than 0");
            }
            if(licensePlate.empty() || std::all_of(licensePlate.begin(), licensePlate.end(),[](unsigned char c) {return std::isspace(c);})){
                throw std::invalid_argument("License plate must not be empty");
            }

    }
    
    int ParkingTicket::getTicketID() const{
        return this->ticketID;
    }

    const std::string& ParkingTicket::getLicensePlate() const{
        return this->licensePlate;
    }

    int ParkingTicket::getSpotID() const{
        return this->spotID;
    }

    TimePoint ParkingTicket::getEntryTime() const{
        return this->entryTime;
    }
    
}

#endif /*_PARKINGTICKET_CPP*/