cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
set(CMAKE_CONFIGURATION_TYPES Debug;Release)

project(Chauve VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC_OPTIONS ON)

# This will find the Qt5 files. You will need a Qt5_DIR env variable
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED) 

# Repository files and generation
set(SOURCES main.cpp application.qrc mainwindow.cpp replay.cpp replaymanager.cpp replaywidget.cpp settingsdialog.cpp settingsmanager.cpp) 
set(HEADERS mainwindow.h replay.h replaymanager.h replaywidget.h settingsdialog.h settingsmanager.h)
set(UI replaywidget.ui settingsdialog.ui)
add_executable(chauve ${SOURCES} ${HEADERS} ${UI})

# Link libraries
target_link_libraries(chauve Qt5::Core Qt5::Gui Qt5::Widgets)

