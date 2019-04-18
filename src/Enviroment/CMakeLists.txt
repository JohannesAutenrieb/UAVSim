set(ENVIROMENT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS 
	Atmosphere.hpp
	EnviromentConstants.hpp
)

set(SOURCES 
	Atmosphere.cpp
)




add_library(LibEnviroment ${HEADERS} ${SOURCES})






