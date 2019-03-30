cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
set(CMAKE_CONFIGURATION_TYPES Debug;Release)

project(Chauve VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# This will find the Qt5 files. You will need a Qt5_DIR env variable
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
if (WIN32)
	foreach(QTDLL Core Gui Widgets)
		file(COPY ${Qt5_DIR}/../../../bin/Qt5${QTDLL}.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	endforeach(QTDLL)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobuf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

# Repository files and generation
set(SOURCES main.cpp 
	mainwindow.cpp replay.cpp replaymanager.cpp replaywidget.cpp settingsdialog.cpp settingsmanager.cpp
	protobuf/demo.pb.cc) 
set(HEADERS 
	mainwindow.h replay.h replaymanager.h replaywidget.h settingsdialog.h settingsmanager.h
	protobuf/demo.pb.h)
set(UIS replaywidget.ui settingsdialog.ui)
set(RESOURCES application.qrc)

qt5_add_resources(${RESOURCES})
add_executable(chauve ${RESOURCES} ${SOURCES} ${HEADERS} ${UIS})

# Link libraries
set(PROTOBUF_USE_DLLS TRUE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/include/)
target_link_libraries(chauve Qt5::Core Qt5::Gui Qt5::Widgets ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobuf.lib)


