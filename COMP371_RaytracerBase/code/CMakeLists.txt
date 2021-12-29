
cmake_minimum_required(VERSION 3.0)

project(raytracer) 


#IMPORTANT COMPILING DIRECTIVES

# 1
# Enable this when you start working on your solution and you add the file RayTracer.h 
# in the src folder; Without this file the code base will not compile therefore in your 
# code this define is disabled
# Also do not forget to create the src folder under code
#add_compile_options(-DSTUDENT_SOLUTION)


# 2
# This define is used by the teaching team to compile and run the official solution
# Students: for your project this define should always be commented out
# If we commit it by mistake please disable it and let us know
add_compile_options(-DCOURSE_SOLUTION)


set(CMAKE_CXX_STANDARD 14)


find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)
include_directories(${Eigen3_INCLUDE_DIRS})
link_directories(${Eigen3_INCLUDE_DIRS})

# not sure why on my machine the above options don't work
# I need to add it manually here
include_directories(/opt/local/include/)
include_directories(/opt/local/include/eigen3/)

#Additions for the lab
include_directories(/encs/include/)
include_directories(/encs/pkg/eigen-3.3.7/root/)
link_directories(/encs/lib64/)

# If you need too manually add the paths to your Eigen library, you can add it here
# do not delete the other 

#internal includes
include_directories(src/)
include_directories(external/)
aux_source_directory(external SOURCE)
aux_source_directory(src SOURCE)


add_executable(raytracer main.cpp ${SOURCE}) #The name of the cpp file and its path can vary

# link only to Eigen
target_link_libraries(${PROJECT_NAME}
#   ${Eigen3_LIBRARIES}
#/encs/pkg/eigen-3.3.7/root
   )
