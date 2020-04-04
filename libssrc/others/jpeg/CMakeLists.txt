cmake_minimum_required(VERSION 2.8)

#LIBRARY PROJECT
#----------------------------------
PROJECT(egeJPEG)

SET(${PROJECT_NAME}_headers jpgd.h jpge.h)
SET(${PROJECT_NAME}_sources jpgd.cpp jpge.cpp)

SET(EGE_MAIN_PATH ${CMAKE_SOURCE_DIR}/../../..)
SET(EGE_BIN_PATH  ${EGE_MAIN_PATH}/bin)
SET(EGE_LIBS_PATH ${EGE_MAIN_PATH}/lib)

message ("${PROJECT_NAME}:> Linker using ${EGE_DESTINATION_PLATFORM_STR} setting for project : <<${PROJECT_NAME}>> ***")
# create the library
#----------------------------------
if(EGE_SYS_EMSCRIPTEN)
	SET(PROJECT_NAME_EXT ${PROJECT_NAME}.bc)
	message("${PROJECT_NAME}:> Libreria STATICA .bc (da linkare al programma) per EMSCRIPTEN***")
	
	ADD_EXECUTABLE(${PROJECT_NAME_EXT} ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})
	message("${PROJECT_NAME}:> ESEGUIBILE in : <<${CMAKE_RUNTIME_OUTPUT_DIRECTORY}>> ***")
endif()

if(EGE_SYS_LINUX OR EGE_SYS_WIN64)
    message (">>>>> OPTION->EGE_SYS_LINUX OR OPTION->EGE_SYS_WIN64")
	SET(PROJECT_NAME_EXT ${PROJECT_NAME})
	message ("\n${PROJECT_NAME}:> Libreria STATICA .a (da linkare al programma) per WIN64 o LINUX ***\n")
	
	if(EGE_SYS_LINUX)
		cmake_policy(PUSH)
		cmake_policy(SET CMP0002 OLD)
	endif()
    	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fvisibility=hidden -g" )
        ADD_LIBRARY(${PROJECT_NAME_EXT} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})
		SET_TARGET_PROPERTIES(${PROJECT_NAME_EXT} PROPERTIES COMPILE_FLAGS "${EGE_EMSCRIPTEN_STATIC_LIBS_COMPILE_FLAGS}" ) 
    if(EGE_SYS_LINUX)
		cmake_policy(POP)
	endif()	
	message("\n${PROJECT_NAME}:> LIBRERIA in : <<${CMAKE_LIBRARY_OUTPUT_DIRECTORY}>>")
endif()


# linker
#----------------------------------
#TARGET_LINK_LIBRARIES(${PROJECT_NAME}) 
message("${PROJECT_NAME}:> Project folder: ${CMAKE_SOURCE_DIR}")
INSTALL( 	
	TARGETS ${PROJECT_NAME_EXT}
	RUNTIME DESTINATION ${EGE_BIN_PATH}
	LIBRARY DESTINATION ${EGE_LIBS_PATH}
	ARCHIVE DESTINATION ${EGE_LIBS_PATH}
)

