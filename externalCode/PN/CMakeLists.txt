cmake_minimum_required(VERSION 3.23)
project(pn_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(pn_lib
        PN.cpp
        PN.h
        )

target_link_libraries(pn_lib)