
set(MIRCO_CONTROLLER_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(HEADERS 
	Controller.h     
	DataStructure.h  
	Macros.h                     
	UserDefinedFunctions.h

)

set(SOURCES 
	
	HYGP_C_Controller.ino  
	UserDefinedFunctions.cpp
	Controller.cpp  
)




add_library(LibMicroController ${HEADERS} ${SOURCES})
TARGET_LINK_LIBRARIES(LibMicroController LINK_PUBLIC ${Boost_LIBRARIES})





