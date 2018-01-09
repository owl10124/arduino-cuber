cmake_minimum_required(VERSION 3.8)
project(ckociemba)

set(raspicam_DIR "/usr/local/lib/cmake")
find_package(raspicam REQUIRED)
find_package(OpenCV)
find_library(wiringPi_LIB wiringPi)

set(SOURCE_FILES
        include/color.h
        include/coordcube.h
        include/corner.h
        include/cubiecube.h
        include/edge.h
        include/facecube.h
        include/facelet.h
        include/search.h
        coordcube.c
        cubiecube.c
        facecube.c
        search.c
        main.cpp)

include_directories(include/
		    ${OpenCV_INCLUDE_DIRS})

add_executable(ckociemba ${SOURCE_FILES})

set_property(TARGET ckociemba PROPERTY CXX_STANDARD 11)
set_property(TARGET ckociemba PROPERTY C_STANDARD 11)

target_link_libraries(ckociemba ${OpenCV_LIBS})
target_link_libraries (ckociemba ${raspicam_CV_LIBS})
target_link_libraries(ckociemba ${wiringPi_LIB})
