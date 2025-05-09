cmake_minimum_required(VERSION 3.16)

project(RenderLender VERSION 1.0 DESCRIPTION "Library for rendering" LANGUAGES CXX)

add_subdirectory(Scene)

add_subdirectory(ISceneImporterLib)
add_subdirectory(SceneImporterLib)

add_subdirectory(MathTypes)

add_subdirectory(IGUIlib)
add_subdirectory(GUIQtLib)

add_subdirectory(IRendererLib)
add_subdirectory(RendererFilamentLib)

add_subdirectory(RenderLenderApp)