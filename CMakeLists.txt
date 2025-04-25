cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
cmake_policy(SET CMP0072 NEW) 

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

add_executable(main
    src/main.cpp
    src/Terrain.cpp
    src/Character.cpp
    src/Camera.cpp
    src/Cube.cpp
    src/InstancedRenderer.cpp
)

target_compile_features(main PRIVATE cxx_std_11)

target_include_directories(main PRIVATE
    include/
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${glm_INCLUDE_DIRS}
)

target_link_libraries(main
    GLEW::GLEW
    ${GLUT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    glm::glm
)