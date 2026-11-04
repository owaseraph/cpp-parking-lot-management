cmake_minimum_required(VERSION 3.16)

project(ParkingSystem VERSION 1.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create executable
add_executable(ParkingSystem
    main.cpp

    # Vehicles
    Vehicles/Vehicle.cpp
    Vehicles/Car.cpp
    Vehicles/Motorcycle.cpp

    # Parking
    Parking/ParkingSpot.cpp
    Parking/ParkingLot.cpp
)

# Allow includes from the project root
target_include_directories(ParkingSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compiler warnings
if(MSVC)
    target_compile_options(ParkingSystem PRIVATE /W4)
else()
    target_compile_options(ParkingSystem PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()