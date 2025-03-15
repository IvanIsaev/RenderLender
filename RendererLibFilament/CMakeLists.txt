cmake_minimum_required(VERSION 3.16)

project(RendererLib VERSION 1.0 DESCRIPTION "RendererLib using Filament" LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED)

set(EXPORT_FILE ${PROJECT_NAME}_export.h)
string(TOLOWER ${EXPORT_FILE} EXPORT_FILE)

set(EXPORT_MACROS ${PROJECT_NAME}_EXPORT)
string(TOUPPER ${EXPORT_MACROS} EXPORT_MACROS)

set(PRIVATE_HEADER_DIRECTORY internal)
set(PUBLIC_HEADER_DIRECTORY include)

set(FILAMENT_INCLUDE_PATH $ENV{FILAMENT_INCLUDE_PATH})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FILAMENT_LIBS_PATH $ENV{FILAMENT_DEBUG_LIBS_PATH})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FILAMENT_LIBS_PATH $ENV{FILAMENT_RELEASE_LIBS_PATH})
endif()

if((FILAMENT_INCLUDE_PATH STREQUAL "") OR (FILAMENT_LIBS_PATH STREQUAL ""))
    message( FATAL_ERROR "Ooops, set path to filament libs, please" )
endif()

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
         EXPORT_MACRO_NAME ${EXPORT_MACROS}
         EXPORT_FILE_NAME ${EXPORT_FILE})
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${EXPORT_FILE} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_HEADER_DIRECTORY})

set(SOURCES src/CFilamentRenderer.cpp src/CFilamentRendererFactory.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADER_DIRECTORY})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} 
${PRIVATE_HEADER_DIRECTORY} 
${FILAMENT_INCLUDE_PATH})

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC IRandererLib)

set(FILAMENT_LIBRARIES_LIST abseil.lib backend.lib basis_transcoder.lib bluevk.lib camutils.lib civetweb.lib dracodec.lib
                            filabridge.lib filaflat.lib filamat.lib filament.lib filament-iblprefilter.lib filameshio.lib
                            geometry.lib gltfio.lib gltfio_core.lib ibl.lib ibl-lite.lib image.lib ktxreader.lib matdbg.lib
                            meshoptimizer.lib mikktspace.lib shaders.lib smol-v.lib stb.lib uberarchive.lib uberzlib.lib
                            utils.lib viewer.lib vkshaders.lib zstd.lib)

foreach(LIB IN LISTS FILAMENT_LIBRARIES_LIST)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${FILAMENT_LIBS_PATH}/${LIB})
endforeach()

include(FindVulkan)
find_package(Vulkan REQUIRED COMPONENTS shaderc_combined)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_EXPORTS _ITERATOR_DEBUG_LEVEL=0)
