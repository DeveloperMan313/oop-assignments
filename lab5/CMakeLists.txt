cmake_minimum_required(VERSION 3.23)

set(project "lab5")
project(${project})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(MyVector)
add_subdirectory(MySet)

add_executable(${project} main.cpp)

target_link_libraries(${project} MyVector MySet)

if(NOT WIN32)
  target_link_libraries(${project} m)
endif()
