cmake_minimum_required(VERSION 3.25)
project(lab_1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp TVector.c TVector.h Tools.cpp Tools.h newton.cpp newton.h gradient_descent.cpp gradient_descent.h functions.cpp functions.h)
add_executable(lab_1 main.cpp)
set(gsl_INCLUDE_DIR /usr/local/include)

find_package(gsl REQUIRED)
include_directories(${gsl_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} GSL::gsl GSL::gslcblas)