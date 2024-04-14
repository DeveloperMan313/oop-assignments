cmake_minimum_required(VERSION 3.23)

set(project "lab8")
project(${project})

set(CMAKE_CXX_STANDARD 17)

add_executable(${project} main.cpp)

if(NOT WIN32)
  target_link_libraries(${project} m)
endif()
