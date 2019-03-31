cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
set(CMAKE_CONFIGURATION_TYPES Debug;Release)

project(Chauve VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# This will find the Qt5 files. You will need a Qt5_DIR env variable
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
if (WIN32)
	foreach(QTDLL Core Gui Widgets)
		if(CMAKE_BUILD_TYPE STREQUAL "Release")
			file(COPY ${Qt5_DIR}/../../../bin/Qt5${QTDLL}.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
		else(CMAKE_BUILD_TYPE STREQUAL "Debug")
			file(COPY ${Qt5_DIR}/../../../bin/Qt5${QTDLL}d.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
		endif()
	endforeach(QTDLL)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobuf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

# Repository files and generation
set(SOURCES main.cpp 
	mainwindow.cpp replay.cpp replaymanager.cpp replaywidget.cpp settingsdialog.cpp settingsmanager.cpp 
	protobuf/demo.pb.cc protobuf/dota_commonmessages.pb.cc protobuf/dota_shared_enums.pb.cc protobuf/dota_usermessages.pb.cc protobuf/netmessages.pb.cc protobuf/network_connection.pb.cc protobuf/networkbasetypes.pb.cc protobuf/usermessages.pb.cc) 
set(HEADERS 
	mainwindow.h replay.h replaymanager.h replaywidget.h settingsdialog.h settingsmanager.h 
	protobuf/demo.pb.h protobuf/dota_commonmessages.pb.h protobuf/dota_shared_enums.pb.h protobuf/dota_usermessages.pb.h protobuf/netmessages.pb.h protobuf/network_connection.pb.h protobuf/networkbasetypes.pb.h protobuf/usermessages.pb.h)
set(UIS replaywidget.ui settingsdialog.ui)
set(RESOURCES application.qrc)
qt5_add_resources(${RESOURCES})

add_executable(chauve ${RESOURCES} ${SOURCES} ${HEADERS} ${UIS})
if (WIN32)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		set_property(TARGET chauve PROPERTY WIN32_EXECUTABLE true)
	endif()
endif()

# Link libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/include/)
target_link_libraries(chauve Qt5::Core Qt5::Gui Qt5::Widgets)
if (WIN32)
	target_link_libraries(chauve ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobuf.lib)
endif()
