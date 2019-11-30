cmake_minimum_required(VERSION 3.15)

project(CMP-104_Fruit_Machine)

if(WIN)
    add_library(Curses src/libs/pdcurses.dll)
    add_executable(FruitMachine src/main.cpp)
    target_link_libraries(FruitMachine Curses)

else()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    add_executable(FruitMachine src/main.cpp)
    target_link_libraries(FruitMachine ${CURSES_LIBRARIES})
endif()


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)