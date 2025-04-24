cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
    include/
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

add_executable(main
    src/main.cpp
    src/Terrain.cpp
    src/Character.cpp
    src/Camera.cpp
)

target_link_libraries(main
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)