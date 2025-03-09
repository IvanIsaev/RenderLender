cmake_minimum_required(VERSION 3.16)

project(RenderLenderApp VERSION 1.0 DESCRIPTION "Graphical wrapper for RenderLender" LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GUILib)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/GUILibRealizationQt/GUILib.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)