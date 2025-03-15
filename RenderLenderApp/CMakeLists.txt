cmake_minimum_required(VERSION 3.16)

project(RenderLenderApp VERSION 1.0 DESCRIPTION "Graphical wrapper for RenderLender" LANGUAGES CXX)

add_executable(${PROJECT_NAME})

set(ROOT_SRC src)

target_sources(${PROJECT_NAME} PRIVATE ${ROOT_SRC}/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GUILib)
target_link_libraries(${PROJECT_NAME} PRIVATE RendererLib)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/GUILibQt/GUILib.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/RendererLibFilament/RendererLib.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)