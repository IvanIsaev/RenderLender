cmake_minimum_required(VERSION 3.16)

project(MiscellaneousH VERSION 1.0 DESCRIPTION "Different stuff" LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)
