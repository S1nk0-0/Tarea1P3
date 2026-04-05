cmake_minimum_required(VERSION 4.0)
project(Tarea1P3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tarea1P3
        Tensor.cpp
        TensorTranform.cpp
        RELU.cpp
        Sigmoid.cpp
        main.cpp)
