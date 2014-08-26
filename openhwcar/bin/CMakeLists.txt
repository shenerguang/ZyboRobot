set(PRODIR /root/openhwcar)
set(BIN ${PRODIR}/bin/openhwcar)
set(SRC_PATH ${PRODIR}/src)
set(SRC ${SRC_PATH}/main.c 
	${SRC_PATH}/eye.c 
	${SRC_PATH}/motor.c 
	${SRC_PATH}/roadctl.c 
	${SRC_PATH}/sign.c )
cmake_minimum_required(VERSION 2.8)
project(openhwcar)
include_directories(${SRC_PATH})
find_package( OpenCV REQUIRED )
add_executable(openhwcar ${SRC})
target_link_libraries( openhwcar ${OpenCV_LIBS} )

