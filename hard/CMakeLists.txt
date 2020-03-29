cmake_minimum_required(VERSION 3.15)
project(LPOptimize)

set(CMAKE_CXX_STANDARD 20)

add_executable(LPOpt main.cpp
                LPproblem.cpp LPproblem.h
                LPresult.cpp LPresult.h)

target_link_libraries(LPOpt armadillo lapack blas)
