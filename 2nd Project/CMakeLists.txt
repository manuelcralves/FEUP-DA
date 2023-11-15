cmake_minimum_required(VERSION 3.23)
project(DA2_G16_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/data_structures)

add_executable(DA2_G16_3
        src/data_structures/Graph.cpp
        src/data_structures/Graph.h
        src/data_structures/VertexEdge.cpp
        src/data_structures/VertexEdge.h
        src/main.cpp)
