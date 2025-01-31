cmake_minimum_required(VERSION 3.10)
project(nrf24l01_pico_serial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS system thread)

# Define source directories
set(HOST_DIR "${CMAKE_SOURCE_DIR}/host")

add_executable(read_pico ${HOST_DIR}/receive.cpp)
add_executable(write_pico ${HOST_DIR}/send.cpp)

target_include_directories(read_pico PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(read_pico PRIVATE ${Boost_LIBRARIES} pthread)
target_include_directories(write_pico PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(write_pico PRIVATE ${Boost_LIBRARIES} pthread)