set(MAVLINK_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(ardupilotmega)
add_subdirectory(slugs)
add_subdirectory(ASLUAV)         
add_subdirectory(common)              
add_subdirectory(standard)
add_subdirectory(autoquad)       
add_subdirectory(icarous)              
add_subdirectory(minimal)              
add_subdirectory(test)
add_subdirectory(matrixpilot)                      
add_subdirectory(uAvionix)



set(MAV_LINK_HEADERS 
mavlink_conversions.h
mavlink_get_info.h
mavlink_helpers.h
mavlink_sha256.h
mavlink_types.h
protocol.h

)



add_library(LibMavLink ${MAV_LINK_HEADER})
set_target_properties(LibMavLink PROPERTIES LINKER_LANGUAGE C)

# Use the Widgets module from Qt 5.
#target_link_libraries(LibThread Qt5::Widgets LibFlightDynamic)






