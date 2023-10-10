cmake_minimum_required(VERSION 3.25)
project(neuro-eye VERSION 0.1.0 LANGUAGES CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(neuro-eye src/main.cpp)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
