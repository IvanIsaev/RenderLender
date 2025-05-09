cmake_minimum_required(VERSION 3.16)

project(RenderLenderApp VERSION 1.0 DESCRIPTION "Graphic wrapper for RenderLender" LANGUAGES CXX)

add_executable(${PROJECT_NAME})

set(ROOT_SRC src)

target_sources(${PROJECT_NAME} PRIVATE ${ROOT_SRC}/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GUILib)
target_link_libraries(${PROJECT_NAME} PRIVATE RendererFilamentLib)
target_link_libraries(${PROJECT_NAME} PRIVATE SceneImporterLib)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
