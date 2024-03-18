cmake_minimum_required(VERSION 3.23)

set(project "MySet")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES MySet.cpp)

set(${project}_HEADERS MySet.hpp)

set(${project}_SOURCE_LIST ${${project}_SOURCES} ${${project}_HEADERS})

add_library(${project} STATIC ${${project}_SOURCE_LIST})
