cmake_minimum_required(VERSION 3.2)
project(cpp_design_patterns)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
add_subdirectory(SOLID)
add_subdirectory(Creational)
add_subdirectory(Structural)
add_subdirectory(Behavioral)
