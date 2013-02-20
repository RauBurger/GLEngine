cmake_minimum_required(VERSION 2.8)

#if (UNIX)
#   set(CMAKE_CXX_COMPILER gcc)
#endif ()

project(GLENGINE)

if (UNIX)
   message(STATUS "Unix/Linux build environment")
   find_package(X11)
   if (X11_FOUND)
	message(STATUS "Found X11")
	message(STATUS ${X11_INCLUDE_DIR})
   else ()
	message(ERROR " X11 not found")
   endif ()

#   find_package(glx)
endif ()

find_package(OpenGL)

add_subdirectory(QtGLEngine)
add_subdirectory(TestApp)

#add_executable (TestApp ${SOURCE_FILES} ${HEADER_FILES} ${ENGINE_HEADERS})
