cmake_minimum_required(VERSION 3.16)

project(IGUIlib VERSION 1.0 DESCRIPTION "Interface of the GUILib" LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include/)

target_include_directories(${PROJECT_NAME} INTERFACE $<TARGET_PROPERTY:MathTypes,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${PROJECT_NAME} INTERFACE $<TARGET_PROPERTY:MiscellaneousH,INTERFACE_INCLUDE_DIRECTORIES>)

cmake_policy(SET CMP0167 OLD)
find_package(Boost REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE Boost::headers)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)
