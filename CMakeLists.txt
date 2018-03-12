cmake_minimum_required(VERSION 3.8)
project(tilapia)

find_package(OpenCV)

set(SOURCE_FILES
        tilapia.cpp)

include_directories(include/)

add_executable(tilapia ${SOURCE_FILES})

set_property(TARGET tilapia PROPERTY CXX_STANDARD 11)
set_property(TARGET tilapia PROPERTY C_STANDARD 11)

target_link_libraries(tilapia ${OpenCV_LIBS})