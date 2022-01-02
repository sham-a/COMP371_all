
cmake_minimum_required(VERSION 3.0)

project(capsule02) #The name of your choice for the project comes here

add_compile_options(-std=c++11) #optional to use c++11


include_directories(/opt/local/include/)
link_directories(/opt/local/lib/)


add_executable(capsule02 capsule02.cpp) #The name of the cpp file and its path can vary

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL -DPLATFORM_OSX")

target_link_libraries(${PROJECT_NAME} glew glfw )