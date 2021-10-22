cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src	# For myengine.h
	contrib	# For glm.hpp
)

if (MSVC)
	include_directories(
		contrib/msvc-windows-x86/SDL2/include	# For SDL.h
		contrib/msvc-windows-x86/glew/include
		# contrib/msvc-windows-x64/SDL2/include
		# contrib/msvc-windows-x64/glew/include		# For glew.h
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
	# ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x64/SDL2/lib
	# ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x64/glew/lib

)
else()
endif()	

# Avoid the weird SDL2main hack
if (MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(myengine
	src/myengine/Core.cpp
	src/myengine/Entity.cpp
	src/myengine/Component.cpp
	src/myengine/Environment.cpp
	src/myengine/Core.h
	src/myengine/Entity.h
	src/myengine/Component.h
	src/myengine/Environment.h
)

if (MSVC)
	target_link_libraries(myengine SDL2 glew32 opengl32)
else()
	target_link_libraries(myengine SDL2 GLU GLEW GL)
endif()

target_link_libraries(myengine SDL2)

add_executable(game
	src/demo/main.cpp
	src/demo/bob.cpp
)

target_link_libraries(game myengine)