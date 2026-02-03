cmake_minimum_required(VERSION 3.23)
project(big_int_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(big_int_lib
        application.qrc
        BigInt.cpp
        BigInt.h
        BigInt_const_size.cpp
        BigInt_const_size.h
        )


set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
#find_package(Qt5Widgets REQUIRED)

target_link_libraries(big_int_lib)