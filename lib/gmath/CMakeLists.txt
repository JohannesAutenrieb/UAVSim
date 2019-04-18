
set(HEADERS 
	Matrix3x3.hpp  
	Quaternion.hpp 
	Vector2.hpp  
	Vector3.hpp
)

add_library(gmath STATIC ${HEADERS})
set_target_properties(gmath PROPERTIES LINKER_LANGUAGE CXX)
