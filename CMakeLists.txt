cmake_minimum_required(VERSION 3.20)
project(CPPPatterns)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executables here
add_executable(builder patterns/creational/builder/builder.cpp)
add_executable(factory patterns/creational/factory/factory.cpp)
