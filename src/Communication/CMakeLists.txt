set(COMMUNICATION_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS 
	TcpServer.hpp
	TcpClient.hpp
	UdpClient.hpp
	UdpServer.hpp
	SerialPortReader.hpp
	Udp_Server_Client_Error.hpp

)

set(SOURCES 	
	TcpServer.cpp
	TcpClient.cpp
	UdpClient.cpp
	UdpServer.cpp
	SerialPortReader.cpp
)




add_library(LibCommunication ${HEADERS} ${SOURCES})







