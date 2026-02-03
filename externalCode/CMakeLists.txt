cmake_minimum_required(VERSION 3.23)
project(externalCode3)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE main.cpp dialog.cpp help.cpp)

include_directories(BigInt)
add_subdirectory(BigInt)

include_directories(PN)
add_subdirectory(PN)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} big_int_lib pn_lib)

add_subdirectory(GTESTS)
