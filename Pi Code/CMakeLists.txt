cmake_minimum_required(VERSION 3.8)
project(ckociemba)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/color.h
        include/coordcube.h
        include/corner.h
        include/cubiecube.h
        include/edge.h
        include/facecube.h
        include/facelet.h
        include/search.h
        include/stdafx.h
        coordcube.c
        cubiecube.c
        facecube.c
        search.c
        main.cpp)

include_directories(include/)

add_executable(ckociemba ${SOURCE_FILES})