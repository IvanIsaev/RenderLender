cmake_minimum_required(VERSION 3.16)

project(RenderLender VERSION 1.0 DESCRIPTION "Library for rendering" LANGUAGES CXX)

add_subdirectory(Scene)

add_subdirectory(ISceneImporter)
add_subdirectory(CSceneImporter)

add_subdirectory(MathTypes)

add_subdirectory(IGUIlib)
add_subdirectory(GUILibQt)

add_subdirectory(IRendererLib)
add_subdirectory(RendererLibFilament)

add_subdirectory(RenderLenderApp)