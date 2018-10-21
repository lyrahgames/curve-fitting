cmake_minimum_required(VERSION 3.10)
project(curve_fitting VERSION 0.1.0 LANGUAGES CXX)

add_executable(fit gn-fit.cpp lm-fit.cpp sa-fit.cpp io-data.cpp main.cpp)
