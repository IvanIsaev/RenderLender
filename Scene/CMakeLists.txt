cmake_minimum_required(VERSION 3.16)

project(Scene VERSION 1.0 DESCRIPTION "This is a scene" LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)

cmake_policy(SET CMP0167 OLD)
find_package(Boost REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE Boost::headers)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)
