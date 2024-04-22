cmake_minimum_required(VERSION 3.5)

project(TestQT2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia) # Add Multimedia here
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia) # Add Multimedia here

set(PROJECT_SOURCES
    main.cpp
    # Add your other source files here
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TestQT2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        gameform.cpp gameform.h gameform.ui signupform.h signupform.cpp mainwindow.ui mainwindow.h mainwindow.cpp main.cpp ui.h ui.cpp signupform.ui
        bucket.cpp bucket.h clouds.cpp clouds.h gameScene.cpp gameScene.h waterdrop.cpp waterdrop.h
        QtResource.qrc
        scoredb.h scoredb.cpp
    )
else()
    if(ANDROID)
        add_library(TestQT2 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(TestQT2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TestQT2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia) # Link Multimedia here

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TestQT2)
endif()
set_target_properties(TestQT2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TestQT2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TestQT2)
endif()
