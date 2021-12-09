#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;

void rowOne(std::shared_ptr<Core> _core)
{
	//// ENTITY & COMPONENTS
	////====================
	std::shared_ptr<Entity> pbrEntity = _core->addEntity();
	std::shared_ptr<PBR> pbr = pbrEntity->addComponent<PBR>();

	// BEATEN METAL SPHERE
	//=================
	pbr->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_albedo"));
	pbr->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_normal"));
	pbr->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_metallic"));
	pbr->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_roughness"));
	pbr->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_ao"));
	pbr->setEmissive(_core->getResourceManager()->load<Texture>(""));

	// SHADERS
	//========
	pbr->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag2.txt");
	pbr->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	pbr->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
	pbr->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
	pbr->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag2.txt");
	pbr->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

	pbr->getTransform()->setPosition(vec3(0, 0, -2.5f));

	//// ENTITY & COMPONENTS
	////====================
	std::shared_ptr<Entity> pbrEntity2 = _core->addEntity();
	std::shared_ptr<PBR> pbr2 = pbrEntity2->addComponent<PBR>();

	// METAL SPHERE
	//=================
	pbr2->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr2->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_albedo"));
	pbr2->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_normal"));
	pbr2->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_metallic"));
	pbr2->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_roughness"));
	pbr2->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_ao"));
	pbr2->setEmissive(_core->getResourceManager()->load<Texture>(""));

	// SHADERS
	//========
	pbr2->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag2.txt");
	pbr2->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	pbr2->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
	pbr2->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
	pbr2->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag2.txt");
	pbr2->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

	pbr2->getTransform()->setPosition(vec3(-2, 0, -2.5f));

	//// ENTITY & COMPONENTS
	////====================
	std::shared_ptr<Entity> pbrEntity3 = _core->addEntity();
	std::shared_ptr<PBR> pbr3 = pbrEntity3->addComponent<PBR>();

	// BRICK SPHERE
	//=================
	pbr3->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr3->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_albedo"));
	pbr3->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_normal"));
	pbr3->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_metallic"));
	pbr3->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_roughness"));
	pbr3->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_ao"));
	pbr3->setEmissive(_core->getResourceManager()->load<Texture>(""));

	// SHADERS
	//========
	pbr3->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag2.txt");
	pbr3->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	pbr3->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
	pbr3->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
	pbr3->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag2.txt");
	pbr3->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

	pbr3->getTransform()->setPosition(vec3(-4, 0, -2.5f));

	//// ENTITY & COMPONENTS
	////====================
	std::shared_ptr<Entity> pbrEntity4 = _core->addEntity();
	std::shared_ptr<PBR> pbr4 = pbrEntity4->addComponent<PBR>();

	// LAVA SPHERE
	//=================
	pbr4->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr4->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_albedo"));
	pbr4->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_normal"));
	pbr4->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_metallic"));
	pbr4->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_roughness"));
	pbr4->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_ao"));
	pbr4->setEmissive(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_emissive"));

	// SHADERS
	//========
	pbr4->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag2.txt");
	pbr4->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	pbr4->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
	pbr4->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
	pbr4->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag2.txt");
	pbr4->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

	pbr4->getTransform()->setPosition(vec3(2, 0, -2.5f));
}

void rowTwo(std::shared_ptr<Core> _core)
{
	//// ENTITY & COMPONENTS
	////====================
	std::shared_ptr<Entity> pbrEntity = _core->addEntity();
	std::shared_ptr<PBR> pbr = pbrEntity->addComponent<PBR>();

	// BEATEN METAL SPHERE
	//=================
	pbr->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_albedo"));
	pbr->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_normal"));
	pbr->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_metallic"));
	pbr->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_roughness"));
	pbr->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/beaten_metal/beatenmetal_ao"));
	pbr->setEmissive(_core->getResourceManager()->load<Texture>(""));

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
	std::shared_ptr<Entity> pbrEntity2 = _core->addEntity();
	std::shared_ptr<PBR> pbr2 = pbrEntity2->addComponent<PBR>();

	// METAL SPHERE
	//=================
	pbr2->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr2->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_albedo"));
	pbr2->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_normal"));
	pbr2->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_metallic"));
	pbr2->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_roughness"));
	pbr2->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/metal/metal_ao"));
	pbr2->setEmissive(_core->getResourceManager()->load<Texture>(""));

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
	std::shared_ptr<Entity> pbrEntity3 = _core->addEntity();
	std::shared_ptr<PBR> pbr3 = pbrEntity3->addComponent<PBR>();

	// BRICK SPHERE
	//=================
	pbr3->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr3->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_albedo"));
	pbr3->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_normal"));
	pbr3->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_metallic"));
	pbr3->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_roughness"));
	pbr3->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/brick/brick_ao"));
	pbr3->setEmissive(_core->getResourceManager()->load<Texture>(""));

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
	std::shared_ptr<Entity> pbrEntity4 = _core->addEntity();
	std::shared_ptr<PBR> pbr4 = pbrEntity4->addComponent<PBR>();

	// LAVA SPHERE
	//=================
	pbr4->setMesh(_core->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
	pbr4->setAlbedo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_albedo"));
	pbr4->setNormal(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_normal"));
	pbr4->setMetallic(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_metallic"));
	pbr4->setRoughness(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_roughness"));
	pbr4->setAo(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_ao"));
	pbr4->setEmissive(_core->getResourceManager()->load<Texture>("../resources/models/sphere/lava/lava_emissive"));

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

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	rowOne(core);
	rowTwo(core);

	//std::shared_ptr<Entity> entity = core->addEntity();
	//std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
	//mr->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/grenade/grenade"));
	////// texture
	//mr->setTexture(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_albedo"));
	//// shader
	//mr->setShader("../resources/shaders/pbrTexVert.txt", "../resources/shaders/pbrTexFrag.txt");


	//// STEAM SPHERE
	////=============
	//std::shared_ptr<Entity> pbrEntity2 = core->addEntity();
	//std::shared_ptr<PBR> pbr2 = pbrEntity2->addComponent<PBR>();

	//// MODEL & TEXTURES
	////=================
	//pbr2->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/pbrsphere/pbrsphere"));
	//pbr2->setAlbedo(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_albedo"));
	//pbr2->setNormal(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_normal"));
	//pbr2->setMetallic(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_metallic"));
	//pbr2->setRoughness(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_roughness"));
	//pbr2->setAo(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_ao"));
	//pbr2->setEmissive(core->getResourceManager()->load<Texture>(""));

	//// SHADERS
	////========
	//pbr2->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag2.txt");
	//pbr2->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	//pbr2->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
	//pbr2->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
	//pbr2->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag.txt");
	//pbr2->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

	//pbr2->getTransform()->setPosition(vec3(-1, 0, -2.5f));

	//std::shared_ptr<AudioClip> s = core->getResourceManager()->load<AudioClip>("doorbell");

	// TODO
	// Create an engine texture that creates a myrenderer::Texture simiilar to Mesh
	// In the initialise function, add .png, .bitmap, .jpeg, etc and try for each
		// Audio would have .ogg in initiliase
	// take out "using namespace myrenderer" to avoid conflicts

	core->start();

	return 0;
}
