include_directories(${GLENGINE_SOURCE_DIR}/TestApp/include)
include_directories(${GLENGINE_SOURCE_DIR}/QtGLEngine/include)

if (UNIX)
    include_directories(${GLENGINE_SOURCE_DIR}/QtGLEngine/include/GLX)
endif ()

set (HEADER_FILES ${HEADER_FILES}
    include/app.h
    include/myinputhandler.h
    )

set (SOURCE_FILES
    src/app.cpp
    src/myinputhandler.cpp
    src/main.cpp
    )

add_executable (TestApp ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(TestApp GLEngine)
