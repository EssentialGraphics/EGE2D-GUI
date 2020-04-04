CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( TUTORIAL03 )
# Define here the needed parameters
SET (EGE_VERSION_MAJOR 2)
SET (EGE_VERSION_MINOR 0)
SET (EGE_VERSION_PATCH 0) 
SET (EGE_VERSION ${EGE_VERSION_MAJOR}.${EGE_VERSION_MINOR}.${EGE_VERSION_PATCH})

SET(EGE_MAIN_PATH ${CMAKE_SOURCE_DIR}/../../..)
#SET(EGE_BIN_PATH  ${EGE_MAIN_PATH}/bin)
#SET(EGE_LIBS_PATH ${EGE_MAIN_PATH}/lib)
SET(EGE_LIBS_PATH ${EGE_OUTPUT_ABSOLUTE_PATH})

# Check if target system is selected (via CMake environment variable setup) 
if(EGE_SYS_LINUX OR EGE_SYS_OSX OR EGE_SYS_WIN64 OR EGE_SYS_EMSCRIPTEN)  # EGE SYS selected
MESSAGE(" *** ------------------------- EGE TUTORIAL 03 ver. " ${EGE_VERSION} " --------------------------- *** \n")
MESSAGE(" - CMAKE SOURCE DIR: <" ${CMAKE_SOURCE_DIR} ">")
MESSAGE(" - PROJECT SOURCE DIR: <" ${PROJECT_SOURCE_DIR} ">") 

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${EGE_MAIN_PATH}/libssrc/ege2d/src)
INCLUDE_DIRECTORIES(${EGE_MAIN_PATH}/libssrc/others/jpeg)
INCLUDE_DIRECTORIES(${EGE_MAIN_PATH}/libssrc/others/boost)
INCLUDE_DIRECTORIES(${EGE_MAIN_PATH}/libssrc/others/glfw/include)
INCLUDE_DIRECTORIES(${EGE_MAIN_PATH}/libssrc/others/glew/include)
INCLUDE_DIRECTORIES(${EGE_MAIN_PATH}/libssrc/others/glut)
INCLUDE_DIRECTORIES(${EGE_MAIN_PATH}/libssrc/others/freetype/include)

# Load project files to be compiled
FILE(GLOB EGE_headers ${CMAKE_SOURCE_DIR}/src/*.h )
MESSAGE("\nHEADER FILES (.h) : " ${EGE_headers})
FILE(GLOB EGE_sources ${CMAKE_SOURCE_DIR}/src/*.cpp )
MESSAGE("SOURCE FILES (.cpp) : " ${EGE_sources} "\n")

if(EGE_SYS_LINUX OR EGE_SYS_WIN64)
	if(EGE_SYS_LINUX)
		cmake_policy(PUSH)
		cmake_policy(SET CMP0002 OLD)
	endif()
	
		MESSAGE("CMake for EGE_SYS_LINUX OR EGE_SYS_WIN64")
	
		SET(PROJECT_NAME_EXT ${PROJECT_NAME})
		ADD_EXECUTABLE( ${PROJECT_NAME_EXT} ${EGE_sources} ${EGE_headers})
		TARGET_LINK_LIBRARIES(${PROJECT_NAME_EXT} -L"C:/EGE2D" ege2D egeJPEG freetype)
		TARGET_LINK_LIBRARIES(${PROJECT_NAME_EXT} -L"C:/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/lib" pthread gdi32 glew32 opengl32 glfw3)
				        
	if(EGE_SYS_LINUX)
		cmake_policy(POP)
	endif()
endif()

if(EGE_SYS_EMSCRIPTEN)
    SET(PROJECT_NAME_EXT ${PROJECT_NAME}.bc)	#Aggiunge suffisso estensione file
	ADD_EXECUTABLE(${PROJECT_NAME_EXT} ${EGE_headers} ${EGE_sources})

  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fvisibility=hidden" )
	SET_TARGET_PROPERTIES(${PROJECT_NAME_EXT} PROPERTIES COMPILE_FLAGS "${EGE_EMSCRIPTEN_STATIC_LIBS_COMPILE_FLAGS} " )
endif()

if(EGE_SYS_EMSCRIPTEN_SIM)
    SET(PROJECT_NAME_EXT ${PROJECT_NAME})		#Aggiunge suffisso estensione file
	
	cmake_policy(PUSH)
	cmake_policy(SET CMP0002 OLD)
		# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fvisibility=hidden -g" )
		ADD_LIBRARY(${PROJECT_NAME_EXT} STATIC ${EGE_headers} ${EGE_sources})
		SET_TARGET_PROPERTIES(${PROJECT_NAME_EXT} PROPERTIES COMPILE_FLAGS "${EGE_EMSCRIPTEN_STATIC_LIBS_COMPILE_FLAGS}" ) 
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} stdc++)

	cmake_policy(POP)
endif()

INSTALL( 	
	TARGETS ${PROJECT_NAME_EXT}
	RUNTIME DESTINATION ${EGE_BIN_PATH}
	LIBRARY DESTINATION ${EGE_LIBS_PATH}
	ARCHIVE DESTINATION ${EGE_LIBS_PATH}
)
# MESSAGE("${PROJECT_NAME} >>> LIBRARY DESTINATION FOLDER : <${EGE_LIBS_PATH}>")

else()	# EGE SYS selected

	MESSAGE("EGE ERROR: There is no CMake environment variable set for TARGET OS.")
	MESSAGE("SOLUTION: Set to TRUE one (and one only) value from following options list:")
	MESSAGE("\tEGE_SYS_LINUX")
	MESSAGE("\tEGE_SYS_OSX")
	MESSAGE("\tEGE_SYS_WIN64")
	MESSAGE("\tEGE_SYS_EMSCRIPTEN")

endif() # EGE SYS selected 