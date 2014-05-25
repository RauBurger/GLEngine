#message(STATUS ${GLENGINE_SOURCE_DIR})

include_directories(include)
include_directories(${OPENGL_INCLUDE_DIR})

if (UNIX)
    set (PLATFORM_HEADERS
	 include/GLX/GLXRenderWindow.h
	)
    set (PLATFORM_SOURCE
	 src/GLX/GLXRenderWindow.cpp
	)
    include_directories(include/GLX)
    include_directories(${X11_INCLUDE_DIR})
endif ()

set 	(HEADER_FILES
	 include/Camera.h
    	 include/Core.h
	 include/EventListener.h
	 include/Frustrum.h
	 include/InputHandler.h
	 include/Matrix3.h
	 include/Matrix4.h
	 include/Node.h
	 include/Object.h
	 include/RenderWindow.h
	 include/SceneTree.h
	 include/Vector3.h
	 )

set	(SOURCE_FILES
	 src/Camera.cpp
	 src/Core.cpp
	 src/Frustrum.cpp
	 src/InputHandler.cpp
	 src/Matrix3.cpp
	 src/Matrix4.cpp
	 src/Node.cpp
	 src/Object.cpp
	 src/RenderWindow.cpp
	 src/SceneTree.cpp
	 src/Vector3.cpp
	 )

add_library(GLEngine ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADERS} ${PLATFORM_SOURCE})

if (UNIX)
    target_link_libraries(GLEngine ${OPENGL_LIBRARIES} ${X11_LIBRARIES})
else ()
    target_link_libraries(GLEngine ${OPENGL_LIBRARIES})
endif ()
