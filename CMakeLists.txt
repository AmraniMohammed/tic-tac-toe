cmake_minimum_required(VERSION 3.16)

project(TicTacToe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()

qt_standard_project_setup(REQUIRES 6.6)