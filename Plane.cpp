#include "Plane.h"

#include "EngineTime.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "Renderer.h"
#include "ShaderLibrary.h"

namespace GDEngine {
	Plane::Plane(std::string name) : AGameObject(name)
	{
		this->m_type = GameObjectType::Plane;

		this->texture = TextureLibrary::getInstance()->getTexture(TextureName::DEFAULT);

		Vector3D positionList[] =
		{
			Vector3D(-0.8f,0.0f,-0.8f),
			Vector3D(-0.8f,0.0f, -0.8f),
			Vector3D(0.8f, 0.0f, -0.8f),
			Vector3D(0.8f, 0.0f,-0.8f),

			Vector3D(0.8f, 0.0f,0.8f),
			Vector3D(0.8f, 0.0f, 0.8f),
			Vector3D(-0.8f,0.0f, 0.8f),
			Vector3D(-0.8f,0.0f,0.8f)
		};

		Vector2D texCoordList[] =
		{
			Vector2D(0.0f, 0.0f),
			Vector2D(0.0f, 2.0f),
			Vector2D(2.0f, 0.0f),
			Vector2D(2.0f, 2.0f),
		};

		texVertex vertexList[] =
		{
			{positionList[0], texCoordList[1]},
			{positionList[1], texCoordList[0]},
			{positionList[2], texCoordList[2]},
			{positionList[3], texCoordList[3]},

			{positionList[4], texCoordList[1]},
			{positionList[5], texCoordList[0]},
			{positionList[6], texCoordList[2]},
			{positionList[7], texCoordList[3]},

			{positionList[1], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[2], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[0], texCoordList[0]},
			{positionList[3], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[3], texCoordList[1]},
			{positionList[2], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[1], texCoordList[2]},
			{positionList[0], texCoordList[3]},
		};

		RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

		ShaderNames shaderNames;

		void* shaderByteCode = nullptr;
		size_t sizeShader = 0;

		ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

		m_vertexBuffer = renderSystem->createTexturedVertexBuffer(vertexList, sizeof(texVertex), ARRAYSIZE(vertexList), shaderByteCode, sizeShader);

		unsigned int indexList[] = {
			0,1,2,
			2,3,0,

			4,5,6,
			6,7,4,

			8,9,10,
			10,11,8,

			12,13,14,
			14,15,12,

			16,17,18,
			18,19,16,

			20,21,22,
			22,23,20
		};

		m_indexBuffer = renderSystem->createIndexBuffer(indexList, ARRAYSIZE(indexList));

		CBObjectData cbData;
		angle = 0.0f;
		cbData.time = angle;

		m_constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBObjectData));
	}

	Plane::Plane(std::string guid, std::string name) : AGameObject(guid, name)
	{
		this->m_type = GameObjectType::Plane;

		this->texture = TextureLibrary::getInstance()->getTexture(TextureName::DEFAULT);

		Vector3D positionList[] =
		{
			Vector3D(-1.0f,0.0f,-1.0f),
			Vector3D(-1.0f,0.0f, -1.0f),
			Vector3D(1.0f, 0.0f, -1.0f),
			Vector3D(1.0f, 0.0f,-1.0f),

			Vector3D(1.0f, 0.0f,1.0f),
			Vector3D(1.0f, 0.0f, 1.0f),
			Vector3D(-1.0f,0.0f, 1.0f),
			Vector3D(-1.0f,0.0f,1.0f)
		};

		Vector2D texCoordList[] =
		{
			Vector2D(0.0f, 0.0f),
			Vector2D(0.0f, 2.0f),
			Vector2D(2.0f, 0.0f),
			Vector2D(2.0f, 2.0f),
		};

		texVertex vertexList[] =
		{
			{positionList[0], texCoordList[1]},
			{positionList[1], texCoordList[0]},
			{positionList[2], texCoordList[2]},
			{positionList[3], texCoordList[3]},

			{positionList[4], texCoordList[1]},
			{positionList[5], texCoordList[0]},
			{positionList[6], texCoordList[2]},
			{positionList[7], texCoordList[3]},

			{positionList[1], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[2], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[0], texCoordList[0]},
			{positionList[3], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[3], texCoordList[1]},
			{positionList[2], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[1], texCoordList[2]},
			{positionList[0], texCoordList[3]},
		};

		RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

		ShaderNames shaderNames;

		void* shaderByteCode = nullptr;
		size_t sizeShader = 0;

		ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

		m_vertexBuffer = renderSystem->createTexturedVertexBuffer(vertexList, sizeof(texVertex), ARRAYSIZE(vertexList), shaderByteCode, sizeShader);

		unsigned int indexList[] = {
			0,1,2,
			2,3,0,

			4,5,6,
			6,7,4,

			8,9,10,
			10,11,8,

			12,13,14,
			14,15,12,

			16,17,18,
			18,19,16,

			20,21,22,
			22,23,20
		};

		m_indexBuffer = renderSystem->createIndexBuffer(indexList, ARRAYSIZE(indexList));

		CBObjectData cbData;
		angle = 0.0f;
		cbData.time = angle;

		m_constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBObjectData));
	}

	Plane::~Plane()
	{
		delete m_constantBuffer;
		delete m_vertexBuffer;
		AGameObject::~AGameObject();
	}

	void Plane::onCreate()
	{
		AGameObject::onCreate();
	}

	void Plane::update(float deltaTime)
	{
		AGameObject::update(deltaTime);
		RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
		CBObjectData cbObjectData;

		cbObjectData.time = 0.0f;

		this->updateLocalMatrix();

		cbObjectData.worldMatrix.setMatrix(this->m_localMatrix);

		m_constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cbObjectData);
	}

	// Sets shaders and draws afterwards
	void Plane::draw(int width, int height)
	{
		ShaderNames shaderNames;
		RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

		VertexShader* vertexShader;
		PixelShader* pixelShader;

		vertexShader = ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME);
		pixelShader = ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME);

		if (this->texture != nullptr)
			renderSystem->getImmediateDeviceContext()->setTexture(this->texture);

		renderSystem->getImmediateDeviceContext()->setConstantBuffer(m_constantBuffer, 0);

		std::vector<AComponent*> rendererList = this->getComponentsOfType(AComponent::Renderer);
		if (!rendererList.empty())
		{
			ARenderer* renderer;
			for (AComponent* component : rendererList) {
				renderer = (ARenderer*)component;
				renderer->perform(EngineTime::getDeltaTime());
			}

			rendererList = this->getComponentsOfTypeRecursive(AComponent::Renderer);

			for (AComponent* component : rendererList) {
				renderer = (ARenderer*)component;
				renderer->perform(EngineTime::getDeltaTime());
			}
			return;
		}

		renderSystem->getImmediateDeviceContext()->setVertexShader(vertexShader);
		renderSystem->getImmediateDeviceContext()->setPixelShader(pixelShader);

		renderSystem->getImmediateDeviceContext()->setVertexBuffer(m_vertexBuffer);
		renderSystem->getImmediateDeviceContext()->setIndexBuffer(m_indexBuffer);

		renderSystem->getImmediateDeviceContext()->drawIndexedTriangleList(m_indexBuffer->getSizeIndexList(), 0, 0);
	}

	void Plane::onDestroy()
	{
	}
}