set(FLIGHT_DYNAMIC_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(HEADERS 
	FlightDynamic.hpp
	FlightMode.hpp
)

set(SOURCES 
	FlightDynamic.cpp
)




add_library(LibFlightDynamic ${HEADERS} ${SOURCES})
TARGET_LINK_LIBRARIES( LibFlightDynamic LINK_PUBLIC ${Boost_LIBRARIES} LibFlightVehicle LibEnviroment)





