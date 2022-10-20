# CMakeLists.txt for project

cmake_minimum_required(VERSION 3.16.0)

set(PROJECT_NAME GeometricCurves)
set(LIBRARY_NAME CurvesLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

add_subdirectory(${LIBRARY_NAME})
add_subdirectory(${PROJECT_NAME})

# End file
