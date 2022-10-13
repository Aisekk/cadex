# CMakeLists.txt for library

cmake_minimum_required(VERSION 3.16.0)

set(HEADERS
    CurvesLibraryApi.h
    Helix.h
    Ellipse.h
    Circle.h
    Curve3D.h
    Forwards.h
    Vector3D.h
    Point3D.h
	)

set(SOURCES
    CurvesLibraryApi.cpp
    Helix.cpp
    Ellipse.cpp
    Circle.cpp
    Curve3D.cpp
    )

# Включение экспорта всех символов для создания динамической библиотеки
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${LIBRARY_NAME} SHARED ${HEADERS} ${SOURCES})

# End file
