cmake_minimum_required(VERSION 3.16)

project(ParkingSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
# Core parking system library
add_library(ParkingCore
    Vehicles/Vehicle.cpp
    Vehicles/Car.cpp
    Vehicles/Motorcycle.cpp
    Parking/ParkingSpot.cpp
    Parking/ParkingLot.cpp
    Parking/ParkingTicket.cpp
    Payments/Payments.cpp
)

target_include_directories(ParkingCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Main application
add_executable(ParkingSystem main.cpp)

target_link_libraries(ParkingSystem PRIVATE ParkingCore)

# Compiler warnings
if(MSVC)
    target_compile_options(ParkingCore PRIVATE /W4)
    target_compile_options(ParkingSystem PRIVATE /W4)
else()
    target_compile_options(ParkingCore PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ParkingSystem PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
    add_executable(ParkingLotTests
        tests/ParkingLotTests.cpp
    )

    target_link_libraries(ParkingLotTests PRIVATE ParkingCore)

    add_test(
        NAME ParkingLotTests
        COMMAND ParkingLotTests
    )

    add_executable(PaymentTests
        tests/PaymentTests.cpp
    )

    target_link_libraries(PaymentTests PRIVATE ParkingCore)

    add_test(
        NAME PaymentTests
        COMMAND PaymentTests
    )
endif()