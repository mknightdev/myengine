cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src
)

add_library(myengine
	src/myengine/Core.cpp
	src/myengine/Core.h
	src/myengine/myengine.h
	src/myengine/Entity.cpp
	src/myengine/Entity.h
	src/myengine/Component.h
	src/myengine/Keyboard.h
	src/myengine/Environment.h
)

add_executable(game
	src/demo/main.cpp
	src/demo/bob.cpp
)

target_link_libraries(game myengine)