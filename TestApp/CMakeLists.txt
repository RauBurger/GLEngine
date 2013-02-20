include_directories(${GLENGINE_SOURCE_DIR}/TestApp/include)

set (HEADER_FILES ${HEADER_FILES}
    include/app.h
    include/myinputhandler.h
    )

set (SOURCE_FILES
    src/app.cpp
    src/myinputhandler.cpp
    src/main.cpp
    )

add_executable (TestApp ${SOURCE_FILES} ${HEADER_FILES} ${ENGINE_HEADERS})

target_link_libraries(TestApp GLEngine)
