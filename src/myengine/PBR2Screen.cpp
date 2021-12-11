#include "PBR2Screen.h"
#include "Transform.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "mymath.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

#include "stb_image.h"
#include "GL\glew.h"

#include <myengine/myengine.h>

namespace myengine
{
	void PBR2Screen::onInitialize()
	{
		// Load icons and models
		std::cout << "PBR2Screen Initialised" << std::endl;

		//// ENTITY & COMPONENTS
		////====================
		std::shared_ptr<Entity> pbrEntity = getCore()->addEntity();
		std::shared_ptr<PBR> pbr = pbrEntity->addComponent<PBR>();

		// BEATEN METAL SPHERE
		//=================
		pbr->setMesh(getCore()->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
		pbr->setAlbedo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_albedo"));
		pbr->setNormal(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_normal"));
		pbr->setMetallic(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_metallic"));
		pbr->setRoughness(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_roughness"));
		pbr->setAo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_ao"));
		pbr->setEmissive(getCore()->getResourceManager()->load<Texture>(""));

		// SHADERS
		//========
		pbr->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag.txt");
		pbr->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
		pbr->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
		pbr->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
		pbr->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag.txt");
		pbr->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

		pbr->getTransform()->setPosition(vec3(0, 2, -2.5f));

		//// ENTITY & COMPONENTS
		////====================
		std::shared_ptr<Entity> pbrEntity2 = getCore()->addEntity();
		std::shared_ptr<PBR> pbr2 = pbrEntity2->addComponent<PBR>();

		// METAL SPHERE
		//=================
		pbr2->setMesh(getCore()->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
		pbr2->setAlbedo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_albedo"));
		pbr2->setNormal(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_normal"));
		pbr2->setMetallic(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_metallic"));
		pbr2->setRoughness(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_roughness"));
		pbr2->setAo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_ao"));
		pbr2->setEmissive(getCore()->getResourceManager()->load<Texture>(""));

		// SHADERS
		//========
		pbr2->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag.txt");
		pbr2->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
		pbr2->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
		pbr2->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
		pbr2->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag.txt");
		pbr2->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

		pbr2->getTransform()->setPosition(vec3(-2, 2, -2.5f));

		//// ENTITY & COMPONENTS
		////====================
		std::shared_ptr<Entity> pbrEntity3 = getCore()->addEntity();
		std::shared_ptr<PBR> pbr3 = pbrEntity3->addComponent<PBR>();

		// BRICK SPHERE
		//=================
		pbr3->setMesh(getCore()->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
		pbr3->setAlbedo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_albedo"));
		pbr3->setNormal(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_normal"));
		pbr3->setMetallic(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_metallic"));
		pbr3->setRoughness(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_roughness"));
		pbr3->setAo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_ao"));
		pbr3->setEmissive(getCore()->getResourceManager()->load<Texture>(""));

		// SHADERS
		//========
		pbr3->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag.txt");
		pbr3->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
		pbr3->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
		pbr3->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
		pbr3->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag.txt");
		pbr3->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

		pbr3->getTransform()->setPosition(vec3(-4, 2, -2.5f));

		//// ENTITY & COMPONENTS
		////====================
		std::shared_ptr<Entity> pbrEntity4 = getCore()->addEntity();
		std::shared_ptr<PBR> pbr4 = pbrEntity4->addComponent<PBR>();

		// LAVA SPHERE
		//=================
		pbr4->setMesh(getCore()->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
		pbr4->setAlbedo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_albedo"));
		pbr4->setNormal(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_normal"));
		pbr4->setMetallic(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_metallic"));
		pbr4->setRoughness(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_roughness"));
		pbr4->setAo(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_ao"));
		pbr4->setEmissive(getCore()->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_emissive"));

		// SHADERS
		//========
		pbr4->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag.txt");
		pbr4->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
		pbr4->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
		pbr4->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
		pbr4->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag.txt");
		pbr4->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

		pbr4->getTransform()->setPosition(vec3(2, 2, -2.5f));
	}

	void PBR2Screen::onTick(float _deltaTime)
	{
		//std::cout << "PBR2Screen TICK" << std::endl;

		if (getKeyboard()->getKeyDown(SDLK_LEFT))
		{
			std::cout << "Press RIGHT ARROW to return to previous screen" << std::endl;

			// Clear the entiies ready for new screen
			getCore()->clear();

			std::shared_ptr<Entity> pbrEntity2 = getCore()->addEntity();
			std::shared_ptr<PBRScreen> PBR2Screen2 = pbrEntity2->addComponent<PBRScreen>();
		}
	}
}