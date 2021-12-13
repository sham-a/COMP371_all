# CMake entry point
cmake_minimum_required (VERSION 3.0)
project(lab03s)

add_compile_options(-std=c++11) #optional to use c++11

find_package(OpenGL REQUIRED)
find_package(glew REQUIRED)
#find_package(glfw REQUIRED)
#find_package(glm REQUIRED)


set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLEW
	glfw
) 

add_definitions(
	-DRUNONMAC
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
	-DGLM_ENABLE_EXPERIMENTAL
	-DUSE_ZLIB_T
	-I/opt/local/include/
	-I/opt/local/include/GLFW/
)



link_directories(/opt/local/lib)

AUX_SOURCE_DIRECTORY(src SOURCES)

add_executable(lab03s ${SOURCES})


target_link_libraries(lab03s ${ALL_LIBS})
