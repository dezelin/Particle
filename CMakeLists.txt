cmake_minimum_required(VERSION 3.5)
project(Particle)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(ui)
include_directories(ui)

set(SOURCE_FILES main.cpp)
add_executable(Particle ${SOURCE_FILES})

target_link_libraries(Particle ui)