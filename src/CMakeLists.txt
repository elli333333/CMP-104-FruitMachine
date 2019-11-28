cmake_minimum_required(VERSION 3.10)

project(CMP-104_Fruit_Machine)

if(WIN)
else()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
endif()


add_executable(FruitMachine main.cpp)
target_link_libraries(FruitMachine ${CURSES_LIBRARIES})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)