cmake_minimum_required(VERSION 3.8)

project(capsule04)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(SRC
    src/main.cpp
    src/Shader.cpp
    src/Camera.cpp
    src/Shape.cpp
    src/Square.cpp
    src/Cube.cpp
)

set(ALL_LIBS
    GLEW::glew
    OpenGL::GL
    glfw
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})

file(COPY
    shaders/phong.frag.glsl
    shaders/phong.vert.glsl
    shaders/blinnPhong.frag.glsl
    shaders/blinnPhong.vert.glsl
    shaders/toon.frag.glsl
    shaders/toon.vert.glsl
    DESTINATION
    ${CMAKE_BINARY_DIR}
)
