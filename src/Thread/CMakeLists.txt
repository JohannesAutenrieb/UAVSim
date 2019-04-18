set(TREAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS 
	Worker.hpp
)

set(SOURCES 
	Worker.cpp

)

find_package(Qt5Core)

find_package(Qt5Widgets REQUIRED)


get_target_property(QtCore_location Qt5::Core LOCATION)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../FlightDynamic)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Communication)

add_library(LibThread ${HEADERS} ${SOURCES})

# Use the Widgets module from Qt 5.
target_link_libraries(LibThread Qt5::Widgets LibFlightDynamic LibCommunication)






