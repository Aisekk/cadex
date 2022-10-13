# CMakeLists.txt for program

cmake_minimum_required(VERSION 3.16.0)

set(HEADERS Summator.h CurvesManager.h)
set(SOURCES main.cpp Summator.cpp CurvesManager.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

find_package(TBB REQUIRED tbb)

include_directories(../${LIBRARY_NAME})

target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME} ${TBB_IMPORTED_TARGETS})

# End file
