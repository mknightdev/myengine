cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src		# For myengine.h
	contrib		# For glm.hpp, bugl.h & stb_image.h
)

if (MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")

	include_directories(
		contrib/msvc-windows-x86/SDL2/include	# For SDL.h
		contrib/msvc-windows-x86/glew/include
		contrib/msvc-windows-x86/OpenAL/include	# For AL/alc.h & AL/al.h
		#contrib/msvc-windows-x64/SDL2/include
		#contrib/msvc-windows-x64/glew/include	# For glew.h
		#contrib/msvc-windows-x64/OpenAL/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/OpenAL/lib
	#${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x64/SDL2/lib
	#${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x64/glew/lib
	#${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x64/OpenAL/lib
)
else()
endif()	

# Avoid the weird SDL2main hack
if (MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(myengine
	
	# Engine Stuff
	src/myengine/myengine.h
	src/myengine/mymath.h
	src/myengine/Core.cpp
	src/myengine/Core.h
	src/myengine/Environment.cpp
	src/myengine/Environment.h
	src/myengine/Entity.cpp
	src/myengine/Entity.h
	src/myengine/Keyboard.cpp
	src/myengine/Keyboard.h
	src/myengine/Mouse.cpp
	src/myengine/Mouse.h
	src/myengine/AudioClip.cpp
	src/myengine/AudioClip.h
	src/myengine/Exception.cpp
	src/myengine/Exception.h
	src/myengine/Camera.cpp
	src/myengine/Camera.h

	# Components
	src/myengine/Component.cpp
	src/myengine/Component.h
	src/myengine/Collider.cpp
	src/myengine/Collider.h
	src/myengine/MeshRenderer.cpp
	src/myengine/MeshRenderer.h
	src/myengine/SoundSource.cpp
	src/myengine/SoundSource.h
	src/myengine/SphereCollider.cpp
	src/myengine/SphereCollider.h
	src/myengine/Transform.cpp
	src/myengine/Transform.h
	src/myengine/TriangleRenderer.cpp
	src/myengine/TriangleRenderer.h
	src/myengine/ModelRenderer.cpp
	src/myengine/ModelRenderer.h

	src/myengine/MenuScreen.cpp
	src/myengine/MenuScreen.h
	src/myengine/PBRScreen.cpp
	src/myengine/PBRScreen.h

	# Resources
	src/myengine/Resource.cpp
	src/myengine/Resource.h
	src/myengine/ResourceManager.cpp
	src/myengine/ResourceManager.h
	src/myengine/Mesh.cpp
	src/myengine/Mesh.h
	src/myengine/Texture.cpp
	src/myengine/Texture.h
	src/myengine/Shader.cpp
	src/myengine/Shader.h

	# GCP
	src/myengine/PBR.cpp
	src/myengine/PBR.h
)

add_library(myrenderer
	src/myrenderer/myrenderer.h
	src/myrenderer/Model.cpp
	src/myrenderer/Model.h
	src/myrenderer/ShaderProgram.cpp
	src/myrenderer/ShaderProgram.h
	src/myrenderer/Texture.cpp
	src/myrenderer/Texture.h
	src/myrenderer/VertexArray.cpp
	src/myrenderer/VertexArray.h
	src/myrenderer/VertexBuffer.cpp
	src/myrenderer/VertexBuffer.h
)

if (MSVC)
	target_link_libraries(myengine SDL2 glew32 opengl32 openal32)
else()
	target_link_libraries(myengine SDL2 GLU GLEW GL openal)
endif()

target_link_libraries(myengine SDL2)

if (MSVC)
	target_link_libraries(myrenderer SDL2 glew32 opengl32 openal32)
else()
	target_link_libraries(myrenderer SDL2 GLU GLEW GL openal)
endif()

add_executable(game
	src/demo/main.cpp
)

target_link_libraries(game myengine myrenderer) 