#pragma once
#ifndef _PARKINGTICKET_H
#define _PARKINGTICKET_H
#include <chrono>
#include <string>
#include <stdexcept>

namespace Parking{
    using TimePoint = std::chrono::system_clock::time_point;
    class ParkingTicket{
        private:
            int ticketID;
            std::string licensePlate;
            int spotID;
            TimePoint entryTime;
        public:
            ParkingTicket(
                int ticketID, 
                const std::string& licensePlate,
                int spotID, 
                TimePoint entryTime);

            //getters
            int getTicketID() const;
            const std::string& getLicensePlate() const;
            int getSpotID() const;
            TimePoint getEntryTime() const;
    };
}
#endif /*_PARKINGTICKET_H*/