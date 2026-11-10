#include "Payments.h"
#include <stdexcept>
#include <chrono>
#include "Parking/ParkingTicket.h"

namespace Payments{

    constexpr double INITIAL_FEE=2;
    constexpr double BILLABLE_FEE=1;
    double Payment::calculateFee(Parking::TimePoint entryTime, Parking::TimePoint exitTime){
        if(exitTime<=entryTime){
            throw std::invalid_argument("Invalid parking duration");
        }
        const auto parkingDuration = exitTime-entryTime;
        const auto billableHours = std::chrono::ceil<std::chrono::hours>(parkingDuration);
        double fee = INITIAL_FEE + (billableHours.count()-1)*BILLABLE_FEE;
        return fee;
    }
}