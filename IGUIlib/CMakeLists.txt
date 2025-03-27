cmake_minimum_required(VERSION 3.16)

project(IGUIlib VERSION 1.0 DESCRIPTION "Interface of the GUILib" LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)

target_link_libraries(${PROJECT_NAME} INTERFACE Common)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)
