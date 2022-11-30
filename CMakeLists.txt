cmake_minimum_required(VERSION 3.5)

project(log2nmea VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if (WIN32)
    set(APP_ICONS "${CMAKE_CURRENT_SOURCE_DIR}/resources/log2nmea.rc")
elseif (APPLE)
    set(MACOSX_BUNDLE_ICON_FILE log2nmea.icns)
    set(APP_ICONS "${CMAKE_CURRENT_SOURCE_DIR}/resources/log2nmea.icns")
    set_source_files_properties(${APP_ICONS} PROPERTIES
           MACOSX_PACKAGE_LOCATION "Resources")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 12.0)
endif()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        log2nmea.cpp
        log2nmea.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(log2nmea
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${APP_ICONS}
    )
else()
    add_executable(log2nmea
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(log2nmea PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(log2nmea PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER log2nmea.hdgnss.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_COPYRIGHT "Copyright 2022, HDGNSS. All Rights Reserved."
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(log2nmea)
endif()
