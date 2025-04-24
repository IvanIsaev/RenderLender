cmake_minimum_required(VERSION 3.16)

project(GUILib VERSION 1.0 DESCRIPTION "GuiLib realization in qt" LANGUAGES CXX)

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

set(MOC_HEADERS ${PRIVATE_HEADER_DIRECTORY}/CApplication.h 
                ${PRIVATE_HEADER_DIRECTORY}/CMainWindow.h
                ${PRIVATE_HEADER_DIRECTORY}/CRenderArea.h
                ${PRIVATE_HEADER_DIRECTORY}/CRenderWindow.h)

set(SOURCES ${ROOT_SRC}/CApplication.cpp
            ${ROOT_SRC}/CApplicationFactory.cpp 
            ${ROOT_SRC}/CInterfaceFactory.cpp 
            ${ROOT_SRC}/CMainWindow.cpp
            ${ROOT_SRC}/CRenderArea.cpp
            ${ROOT_SRC}/CRenderWindow.cpp
            ${ROOT_SRC}/COperationCreatingRenderWindow.cpp
)

set(UIS ui/CMainWindow.ui)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets)

qt6_wrap_ui( UI_HEADERS ${UIS} )
qt6_wrap_cpp( MOC_SRCS ${MOC_HEADERS} )

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADER_DIRECTORY})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${PRIVATE_HEADER_DIRECTORY})

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${MOC_SRCS} ${UI_HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Gui Qt::Widgets)
target_link_libraries(${PROJECT_NAME} PUBLIC IGUIlib)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_EXPORTS)

#Hack to place this dll to the same folder as exe
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.dll" "${CMAKE_BINARY_DIR}/RenderLenderApp")
