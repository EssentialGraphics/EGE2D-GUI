# Windows 7 64Bit INSTALLATION
# 1) Install Net Framework 4
# 2) Install Windows SDK (in order to install GL/OpenGL32 libraries and headers)
# 3) Install CMake
# 4) Install Make 
# 5) Install ZLib
# 6) Install MinGW
# 7) Compile project libraries one by one with CMake

# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)
SET(EGE_SYS_WIN64 true)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER C:/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/bin/gcc.exe)
SET(CMAKE_CXX_COMPILER C:/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0/mingw64/bin/x86_64-w64-mingw32-g++.exe)

SET (CMAKE_C_FLAGS "-g -w")						#-std=c++17 -g -w -Wall -Wno-c++17-extensions -v
SET (CMAKE_CXX_FLAGS "-std=c++11 -g")			# -std=c++17 -g -w -Wall -Wno-c++17-extensions -v

SET (EGE_OUTPUT_ABSOLUTE_PATH "C:/EGE2D")  		# Where "make install" writes libraries
ADD_DEFINITIONS("-DEGE_WIN64")
ADD_DEFINITIONS("-DEGE_USE_GLFW3")
ADD_DEFINITIONS("-DEGE_MODE_VAO")				# Uses Vertex Array Objects for OpenGL (when GLFW3 >= ver. 3.2)


