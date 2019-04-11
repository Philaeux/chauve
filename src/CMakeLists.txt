cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
set(CMAKE_CONFIGURATION_TYPES Debug;Release)

project(Chauve VERSION 0.0.3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# This will find the Qt5 files. You will need a Qt5_DIR env variable
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
if (WIN32)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		foreach(QTDLL Core Gui Widgets)
			file(COPY ${Qt5_DIR}/../../../bin/Qt5${QTDLL}.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
		endforeach(QTDLL)
		file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobuf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
		file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../snappy-1.1.7/win_x64/snappy.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	else(CMAKE_BUILD_TYPE STREQUAL "Debug")	
		foreach(QTDLL Core Gui Widgets)
			file(COPY ${Qt5_DIR}/../../../bin/Qt5${QTDLL}d.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
		endforeach(QTDLL)
		file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobufd.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
		file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../snappy-1.1.7/win_x64/snappyd.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	endif()
endif()

# Repository files and generation
set(SOURCES 
	protobuf/demo.pb.cc 
	protobuf/dota_commonmessages.pb.cc 
	protobuf/dota_shared_enums.pb.cc 
	protobuf/dota_usermessages.pb.cc 
	protobuf/netmessages.pb.cc 
	protobuf/network_connection.pb.cc 
	protobuf/networkbasetypes.pb.cc 
	protobuf/usermessages.pb.cc
	hero.cpp 
	main.cpp 
	mainwindow.cpp 
	replay.cpp 
	replaymanager.cpp 
	replaywidget.cpp 
	settingsdialog.cpp 
	settingsmanager.cpp 
) 
set(HEADERS 
	protobuf/demo.pb.h 
	protobuf/dota_commonmessages.pb.h 
	protobuf/dota_shared_enums.pb.h 
	protobuf/dota_usermessages.pb.h 
	protobuf/netmessages.pb.h 
	protobuf/network_connection.pb.h 
	protobuf/networkbasetypes.pb.h 
	protobuf/usermessages.pb.h
	hero.h
	mainwindow.h
	replay.h
	replaymanager.h
	replaywidget.h
	settingsdialog.h
	settingsmanager.h 
)
set(UIS 
	replaywidget.ui 
	settingsdialog.ui
)
set(RESOURCES 
	application.qrc
)
qt5_add_resources(${RESOURCES})

add_executable(chauve ${RESOURCES} ${SOURCES} ${HEADERS} ${UIS})
if (WIN32)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		set_property(TARGET chauve PROPERTY WIN32_EXECUTABLE true)
	endif()
endif()

# Link libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../snappy-1.1.7/include/)
target_link_libraries(chauve Qt5::Core Qt5::Gui Qt5::Widgets)
if (WIN32)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		target_link_libraries(chauve ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobuf.lib)
		target_link_libraries(chauve ${CMAKE_CURRENT_SOURCE_DIR}/../snappy-1.1.7/win_x64/snappy.lib)	
	else(CMAKE_BUILD_TYPE STREQUAL "Debug")	
		target_link_libraries(chauve ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf-3.7.1/win_x64/libprotobufd.lib)
		target_link_libraries(chauve ${CMAKE_CURRENT_SOURCE_DIR}/../snappy-1.1.7/win_x64/snappyd.lib)	
	endif()
else()
	find_package(Protobuf REQUIRED)
	target_link_libraries(chauve ${Protobuf_LIBRARIES})
	find_package(Snappy REQUIRED)
	target_link_libraries(chauve Snappy)
endif()
 