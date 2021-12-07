#include "Component.h"
#include "mymath.h"

#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct Mesh;
	struct Texture;

	struct PBR : Component
	{
		void onAwake();
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		void mouseUpdate();

		void renderCube();
		void renderQuad();
		void renderSphere();

		void setMesh(std::shared_ptr<Mesh> _mesh);

		void setAlbedo(std::shared_ptr<Texture> _albedo);
		void setNormal(std::shared_ptr<Texture> _normal);
		void setMetallic(std::shared_ptr<Texture> _metallic);
		void setRoughness(std::shared_ptr<Texture> _roughness);
		void setAo(std::shared_ptr<Texture> _ao);
		void setEmissive(std::shared_ptr<Texture> _emissive);

		// Load shader functions
		void setShader(const GLchar* _vert, const GLchar* _frag);
		void PBR::setCubemapShader(const GLchar* _vert, const GLchar* _frag);

	private:
		friend struct myengine::Core;

		/**
		* Used for storing the Core and navigating up the hierarchy.
		*/
		std::weak_ptr<Core> core;

		/**
		* \brief Shader to create and use.
		*
		* Creates a shader program using the linked paths for the vertex and fragment shaders.
		* \attention This one is used for the model.
		*/
		std::shared_ptr<myrenderer::ShaderProgram> shader;

		std::shared_ptr<myrenderer::ShaderProgram> cubemapShader;
		std::shared_ptr<myrenderer::ShaderProgram> backgroundShader;
		std::shared_ptr<myrenderer::ShaderProgram> irradianceShader;
		std::shared_ptr<myrenderer::ShaderProgram> prefilterShader;
		std::shared_ptr<myrenderer::ShaderProgram> brdfShader;

		/**
		* \brief Shader to create and use.
		*
		* Creates a shader program using the linked paths for the vertex and fragment shaders.
		* \attention This one is used for the light box that is within the scene.
		*/
		std::shared_ptr<myrenderer::ShaderProgram> lightShader;

		/**
		* \brief The VAO to load the model with.
		*
		* Creates a VertexArray object for the main model.
		*
		* \see myrenderer::VertexArray
		*/
		std::shared_ptr<myrenderer::VertexArray> vao;

		/**
		* \brief The VAO for the light.
		*
		* Creates a VertexArray object for the light box.
		* \see myrenderer::VertexArray
		*/
		std::shared_ptr<myrenderer::VertexArray> lightVao;

		/**
		* \brief The positions VBO for the light box.
		*
		* Creates a VertexBuffer for the light box, that holds all the positions for each vertex of the object.
		*/
		std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;

		/**
		* \brief The textures VBO.
		*
		* Creates a VertexBuffer object for the textures of the object.
		*
		* \see TriangleRenderer
		*/
		std::shared_ptr<myrenderer::VertexBuffer> texturesVbo;

		/**
		* \brief The model's texture
		*
		* Stores texture and gets used to bind with the VAO when drawing it.
		*/
		std::shared_ptr<myrenderer::Texture> albedoMap;
		std::shared_ptr<myrenderer::Texture> normalMap;
		std::shared_ptr<myrenderer::Texture> metallicMap;
		std::shared_ptr<myrenderer::Texture> roughnessMap;
		std::shared_ptr<myrenderer::Texture> aoMap;
		std::shared_ptr<myrenderer::Texture> emissiveMap;

		// PBR
		unsigned int envCubeMap;
		unsigned int irradianceMap;
		unsigned int prefilterMap;
		unsigned int brdfLUTTexture;

		mat4 captureProjection;
		unsigned int hdrTexture;
		unsigned int captureFBO;
		unsigned int captureRBO;

		mat4 projection;
	

		mat4 captureViews[6] =
		{
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		};

		vec3 pointLightPositions[4] = {
			vec3(0.7f,  0.2f,  2.0f),
			vec3(2.3f, -3.3f, -4.0f),
			vec3(-4.0f,  2.0f, -12.0f),
			vec3(0.0f,  0.0f, -3.0f)
		};
	};
}