cmake_minimum_required(VERSION 3.16)
project(attackAlg)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
