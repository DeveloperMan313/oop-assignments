cmake_minimum_required(VERSION 3.23)

set(project "lab2")
project(${project})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(planet)
add_subdirectory(star)
add_subdirectory(input)

add_executable(${project} main.cpp)

target_link_libraries(${project} planet star input)

if(NOT WIN32)
  target_link_libraries(${project} m)
endif()
