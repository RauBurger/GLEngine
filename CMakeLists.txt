cmake_minimum_required(VERSION 2.8)

#if (UNIX)
#   set(CMAKE_CXX_COMPILER gcc)
#endif ()

project(GLENGINE)

if (UNIX)
   message(STATUS "Unix/Linux build environment")
   find_package(X11)
   find_package(glx)
endif ()

find_package(OpenGL)

add_subdirectory(QtGLEngine)
add_subdirectory(TestApp)
