set(INPUT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS 
	Joystick.hpp
)

set(SOURCES 	
	Joystick.cpp
)




add_library(LibInput ${HEADERS} ${SOURCES})

# Use the Widgets module from Qt 5.
target_link_libraries(LibInput  ${PLIB_LIBRARIES})






