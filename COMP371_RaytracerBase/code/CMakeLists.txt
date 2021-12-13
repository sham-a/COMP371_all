
cmake_minimum_required(VERSION 3.0)

project(raytracer) #The name of your choice for the project comes here

add_compile_options(-std=c++11) 


# Enable this when I compile the solution
# Disable if not
# Students: for your project this should always be commented out
add_compile_options(-DCOURSE_SOLUTION)

find_package(Eigen3 REQUIRED)

include_directories(EIGEN3_INCLUDE_DIR)
include_directories(${Eigen3_INCLUDE_DIRS})
link_directories(${Eigen3_INCLUDE_DIRS})

include_directories(/opt/local/include/)

include_directories(src/)
include_directories(external/)


aux_source_directory(external SOURCE)
aux_source_directory(src SOURCE)

add_executable(raytracer main.cpp ${SOURCE}) #The name of the cpp file and its path can vary

target_link_libraries(${PROJECT_NAME}
   ${Eigen3_LIBRARIES}
   )