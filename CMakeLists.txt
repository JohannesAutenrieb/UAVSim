# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.0)


#add_subdirectory(lib/pugixml)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/executable)

# Include Qt basic functions
include(QtCommon)

# Basic information about project

project(droneSim C CXX)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)

add_definitions(-fPIC) 

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
include_directories(${CMAKE_SOURCE_DIR}/lib/pugixml/)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

# Set additional project information
set(COMPANY "droneSim")
set(COPYRIGHT "Copyright (c) 2014 Vincent Lee. All rights reserved.")
set(IDENTIFIER "com.droneSim.droneSim")

set(SOURCE_FILES
    src/main.cc
    src/mainwindow.cc
    src/terminalwindow.cpp

)

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES droneSim.qrc)

find_package(Qt5Widgets REQUIRED)
#find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

find_package(Boost)

#find_library(QtCore protobuf HINTS /usr/include/x86_64-linux-gnu/qt5/QtCore/)



# source_group("UI Files" FILES ${UI_FILES})

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)


# The Qt5Widgets_INCLUDES also includes the include directories for
  # dependencies QtCore and QtGui
  include_directories(${Qt5Widgets_INCLUDES})

  # We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
  add_definitions(${Qt5Widgets_DEFINITIONS})
 # Executables fail to build with Qt 5 in the default configuration
  # without -fPIE. We add that here.
  set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


target_link_libraries(${PROJECT_NAME} pugixml gmath LibFlightVehicle LibFlightDynamic LibThread ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${PROTOBUF_LIBRARY})
#target_link_libraries( ${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} )


# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

qt5_use_modules(${PROJECT_NAME} Widgets)
