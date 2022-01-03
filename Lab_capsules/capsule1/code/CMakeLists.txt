cmake_minimum_required(VERSION 3.8)

project(capsule01) #The name of your choice for the project comes here

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)

set(CMAKE_CXX_STANDARD 11)

link_directories(/opt/local/lib/)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPLATFORM_OSX")

add_executable(${PROJECT_NAME} capsule01.cpp) #The name of the cpp file and its path can vary

target_link_libraries(${PROJECT_NAME} OpenGL::GL glew glfw)
