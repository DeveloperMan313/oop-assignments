cmake_minimum_required(VERSION 3.23)

set(project "lab2")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(libraries "planet")

add_subdirectory(${libraries})

add_executable(${project} main.cpp)

target_link_libraries(${project} ${libraries})

if(NOT WIN32)
  target_link_libraries(${project} m)
endif()
