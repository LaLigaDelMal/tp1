cmake_minimum_required(VERSION 3.16)
project(AyED_Programa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(includes/math)
include_directories(includes/general)

add_executable( AyED_Programa
        main.cpp
        LectorDeHtml.cpp
        LectorDeHtml.h
        Lista.cpp
        Lista.h
        Nodo.cpp
        Nodo.h
        Pila.cpp
        Pila.h )

