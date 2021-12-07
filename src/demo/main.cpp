#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> entity = core->addEntity();
	std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
	mr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/grenade/grenade"));
	//// texture
	mr->setTexture(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_albedo"));
	// shader
	mr->setShader("resources/shaders/pbrTexVert.txt", "resources/shaders/pbrTexFrag.txt");

	// ENTITY & COMPONENTS
	//====================
	//std::shared_ptr<Entity> pbrEntity = core->addEntity();
	//std::shared_ptr<PBR> pbr = pbrEntity->addComponent<PBR>();

	// TEXTURES
	//=========
	//pbr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/grenade/grenade"));
	//pbr->setAlbedo(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_albedo"));
	//pbr->setNormal(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_normal"));
	//pbr->setMetallic(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_metallic"));
	//pbr->setRoughness(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_roughness"));
	//pbr->setAo(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_ao"));
	//pbr->setEmissive(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_emissive"));

	// SHADERS
	//========
	//pbr->setShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag.txt");
	//pbr->setCubemapShader("resources/shaders/pbr/cubemapVert.txt", "resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");
	
	//std::shared_ptr<AudioClip> s = core->getResourceManager()->load<AudioClip>("doorbell");

	// TODO
	// Create an engine texture that creates a myrenderer::Texture simiilar to Mesh
	// In the initialise function, add .png, .bitmap, .jpeg, etc and try for each
		// Audio would have .ogg in initiliase
	// take out "using namespace myrenderer" to avoid conflicts

	core->start();

	return 0;
}
