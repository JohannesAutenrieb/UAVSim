
set(FLIGHT_VEHICLE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(HEADERS 
	Propeller.hpp
	Multicopter.hpp
	ESC.hpp
	Battery.hpp
	Motor.hpp
)

set(SOURCES 
	
	Propeller.cpp
	Multicopter.cpp
	Motor.cpp
	Battery.cpp
	ESC.cpp

)




add_library(LibFlightVehicle ${HEADERS} ${SOURCES})
TARGET_LINK_LIBRARIES( LibFlightVehicle LINK_PUBLIC ${Boost_LIBRARIES} pugixml)





