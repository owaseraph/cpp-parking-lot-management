#pragma once
#ifndef _PAYMENTS_H
#define _PAYMENTS_H
#include "Parking/ParkingTicket.h"
namespace Payments{
    class Payment{
        public:
            static double calculateFee(
                Parking::TimePoint entryTime,
                Parking::TimePoint exitTime
            );
    };
}

#endif /*_PAYMENTS_H*/