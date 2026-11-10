#include <iostream>
#include <chrono>
#include <stdexcept>
#include <string>

#include "Payments/Payments.h"

void check(bool condition, const std::string& message){
    if(!condition){
        throw std::runtime_error(message);
    }
}

template<typename Function>
void checkThrows(Function function, const std::string& message) {
    try {
        function();
    }
    catch (const std::invalid_argument&) {
        return;
    }

    throw std::runtime_error(message);
}

int main(){
    try{
        const Parking::TimePoint entryTime{};

        //Test 1: 30 mins
        Parking::TimePoint exitTime = entryTime + std::chrono::minutes(30);
        check(Payments::Payment::calculateFee(entryTime,exitTime) == 2.0, "Payment should be 2 euros after 30 mins");

        //Test 2: 60 mins
        exitTime = entryTime + std::chrono::hours(1);
        check(Payments::Payment::calculateFee(entryTime,exitTime) == 2.0, "Payment should be 2 euros after 60 mins");

        //Test 3: 61 mins
        exitTime = entryTime + std::chrono::minutes(61);
        check(Payments::Payment::calculateFee(entryTime,exitTime) == 3.0, "Payment should be 3 euros after 61 mins");

        //Test 4: 2h 15mins
        exitTime = entryTime + std::chrono::hours(2) + std::chrono::minutes(15);
        check(Payments::Payment::calculateFee(entryTime,exitTime) == 4.0, "Payment should be 4 euros after 2h 15mins");

        //Test 4: 2h 15mins
        exitTime = entryTime + std::chrono::hours(4) + std::chrono::minutes(1);
        check(Payments::Payment::calculateFee(entryTime,exitTime) == 6.0, "Payment should be 6 euros after 4h 1min");

        // Test 6: Exit time earlier than entry time
        exitTime = entryTime - std::chrono::minutes(10);

        checkThrows(
            [&]() {
                Payments::Payment::calculateFee(entryTime, exitTime);
            },
            "Earlier exit time should throw an exception"
        );

        // Test 7: Identical timestamps
        exitTime = entryTime;

        checkThrows(
            [&]() {
                Payments::Payment::calculateFee(entryTime, exitTime);
            },
            "Identical timestamps should throw an exception"
        );

        std::cout<<"All payment test passed!\n";
        return 0;
    }
    catch(const std::exception& e){
        std::cerr<<"Payment test failed: "<<e.what()<<"\n";
        return 1;
    }
}