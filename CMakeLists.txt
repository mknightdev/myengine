cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src	# For myengine.h
	contrib	# For glm.hpp
)

if (MSVC)
	include_directories(
		# contrib/msvc-windows-x86/SDL2/include  # For SDL.h
		contrib/msvc-windows-x86/SDL2/include
)

link_directories(
	# ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x64/SDL2/lib
)
else()
endif()	

# Avoid the weird SDL2main hack
if (MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(myengine
	src/myengine/Core.cpp
	src/myengine/Core.h
	src/myengine/myengine.h
	src/myengine/Entity.cpp
	src/myengine/Entity.h
	src/myengine/Component.h
	src/myengine/Component.cpp
	src/myengine/Keyboard.h
	src/myengine/Environment.h
	src/myengine/Environment.cpp
)

target_link_libraries(myengine SDL2)

add_executable(game
	src/demo/main.cpp
	src/demo/bob.cpp
)

target_link_libraries(game myengine)