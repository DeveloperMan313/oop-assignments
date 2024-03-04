cmake_minimum_required(VERSION 3.23)

set(project "lab3")
project(${project})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(fraction)

add_executable(${project} main.cpp)

target_link_libraries(${project} fraction)

if(NOT WIN32)
  target_link_libraries(${project} m)
endif()
