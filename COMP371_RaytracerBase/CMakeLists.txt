
cmake_minimum_required(VERSION 3.0)

project(raytracer) #The name of your choice for the project comes here

add_compile_options(-std=c++11) #optional to use c++11

find_package(Eigen3 REQUIRED)

include_directories(EIGEN3_INCLUDE_DIR)
include_directories(${Eigen3_INCLUDE_DIRS})
link_directories(${Eigen3_INCLUDE_DIRS})

include_directories(/opt/local/include/)

aux_source_directory(src/external SOURCE)

add_executable(raytracer src/main.cpp ${SOURCE}) #The name of the cpp file and its path can vary

target_link_libraries(${PROJECT_NAME}
   ${Eigen3_LIBRARIES}
   )