cmake_minimum_required(VERSION 3.16)

project(RLMathLib VERSION 1.0 DESCRIPTION "Math lib" LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED)

set(EXPORT_FILE ${PROJECT_NAME}_export.h)
string(TOLOWER ${EXPORT_FILE} EXPORT_FILE)

set(EXPORT_MACROS ${PROJECT_NAME}_EXPORT)
string(TOUPPER ${EXPORT_MACROS} EXPORT_MACROS)

set(PRIVATE_HEADER_DIRECTORY internal)
set(PUBLIC_HEADER_DIRECTORY include)
set(ROOT_SRC src)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
         EXPORT_MACRO_NAME ${EXPORT_MACROS}
         EXPORT_FILE_NAME ${EXPORT_FILE})
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${EXPORT_FILE} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_HEADER_DIRECTORY})

set(SOURCES ${ROOT_SRC}/Matrix.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADER_DIRECTORY})
target_include_directories(${PROJECT_NAME} PRIVATE  ${PRIVATE_HEADER_DIRECTORY})
target_include_directories(${PROJECT_NAME} PRIVATE $<TARGET_PROPERTY:MathTypes,INTERFACE_INCLUDE_DIRECTORIES>)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_EXPORTS _ITERATOR_DEBUG_LEVEL=0)

#Hack to place this dll to the same folder as exe
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.dll" "${CMAKE_BINARY_DIR}/RenderLenderApp")
