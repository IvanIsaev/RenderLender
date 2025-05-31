cmake_minimum_required(VERSION 3.16)

project(IRandererLib VERSION 1.0 DESCRIPTION "Interface of the RendererLib" LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)

target_include_directories(${PROJECT_NAME} INTERFACE $<TARGET_PROPERTY:MathTypes,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${PROJECT_NAME} INTERFACE $<TARGET_PROPERTY:MiscellaneousH,INTERFACE_INCLUDE_DIRECTORIES>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)
