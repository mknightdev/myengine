#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	//std::shared_ptr<Entity> entity = core->addEntity();
	//std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
	//mr->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/grenade/grenade"));
	////// texture
	//mr->setTexture(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_albedo"));
	//// shader
	//mr->setShader("../resources/shaders/pbrTexVert.txt", "../resources/shaders/pbrTexFrag.txt");

	//// ENTITY & COMPONENTS
	////====================
	std::shared_ptr<Entity> pbrEntity = core->addEntity();
	std::shared_ptr<PBR> pbr = pbrEntity->addComponent<PBR>();

	// MODEL & TEXTURES
	//=================
	pbr->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/grenade/grenade"));
	pbr->setAlbedo(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_albedo"));
	pbr->setNormal(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_normal"));
	pbr->setMetallic(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_metallic"));
	pbr->setRoughness(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_roughness"));
	pbr->setAo(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_ao"));
	pbr->setEmissive(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_emissive"));

	// SHADERS
	//========
	pbr->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag.txt");
	pbr->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	pbr->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
	pbr->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
	pbr->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag.txt");
	pbr->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

	// STEAM SPHERE
	//=============
	std::shared_ptr<Entity> pbrEntity2 = core->addEntity();
	std::shared_ptr<PBR> pbr2 = pbrEntity2->addComponent<PBR>();

	// MODEL & TEXTURES
	//=================
	pbr2->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/pbrsphere/pbrsphere"));
	pbr2->setAlbedo(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_albedo"));
	pbr2->setNormal(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_normal"));
	pbr2->setMetallic(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_metallic"));
	pbr2->setRoughness(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_roughness"));
	pbr2->setAo(core->getResourceManager()->load<Texture>("../resources/models/pbrsphere/pbrsphere_ao"));
	pbr2->setEmissive(core->getResourceManager()->load<Texture>(""));

	// SHADERS
	//========
	pbr2->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag2.txt");
	pbr2->setCubemapShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	pbr2->setIrradianceShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/irradianceFrag.txt");
	pbr2->setPrefilterShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/prefilterFrag.txt");
	pbr2->setBRDFShader("../resources/shaders/pbr/brdfVert.txt", "../resources/shaders/pbr/brdfFrag.txt");
	pbr2->setBackgroundShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

	pbr2->getTransform()->setPosition(vec3(-1, 0, -2.5f));

	//std::shared_ptr<AudioClip> s = core->getResourceManager()->load<AudioClip>("doorbell");

	// TODO
	// Create an engine texture that creates a myrenderer::Texture simiilar to Mesh
	// In the initialise function, add .png, .bitmap, .jpeg, etc and try for each
		// Audio would have .ogg in initiliase
	// take out "using namespace myrenderer" to avoid conflicts

	core->start();

	return 0;
}
