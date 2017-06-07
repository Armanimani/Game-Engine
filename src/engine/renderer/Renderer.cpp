#include "Renderer.h"

#include "../shader/BasicShader.h"
#include "../shader/SimplePositionShader.h"
#include "../shader/SimpleColorShader.h"
#include "../shader/SimpleDiffuseColorShader.h"
#include "../debug/Debug.h"
#include "../database/TypeDatabase.h"
#include "../shader/SimpleDiffuseReflectiveShader.h"
#include "../shader/SimpleVertexADSShader.h"
#include "../shader/SimpleFragmentADSShader.h"
#include "../shader/SimpleFragmentADS2FaceShader.h"
#include "../shader/SimpleVertexADSFlatShader.h"
#include "../shader/SimpleDebug2FaceShader.h"
#include "../shader/SimpleFragmentDiscardShader.h"
#include "../shader/text/SimpleTextShader.h"
#include "../shader/text/SingedDistanceTextShader.h"
#include "../shader/text/SingnedDistanceOutlineTextShader.h"
#include "../shader/SimpleFragmentADSToonShader.h"
#include "../shader/SimpleFogShader.h"
#include "../shader/SimpleTextureShader.h"
#include "../shader/SimpleDoubleTextureShader.h"
#include "../light/Light.h"
#include "../light/AmbientLight.h"

void Renderer::init(const std::shared_ptr<SceneManager> manager)
{
	sceneManager = manager;
	
	sharedData = std::make_shared<ShaderSharedData>();
	sharedData->setSceneManager(manager);

	shaderMap.insert(std::make_pair(ShaderType::BasicShader, std::make_shared<BasicShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimplePositionShader, std::make_shared<SimplePositionShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleColorShader, std::make_shared<SimpleColorShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleDiffuseColorShader, std::make_shared<SimpleDiffuseColorShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleDiffuseReflectiveShader, std::make_shared<SimpleDiffuseReflectiveShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleVertexADSShader, std::make_shared<SimpleVertexADSShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleFragmentADSShader, std::make_shared<SimpleFragmentADSShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleFragmentADS2FaceShader, std::make_shared<SimpleFragmentADS2FaceShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleVertexADSFlatShader, std::make_shared<SimpleVertexADSFlatShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleDebug2FaceShader, std::make_shared<SimpleDebug2FaceShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleFragmentDiscardShader, std::make_shared<SimpleFragmentDiscardShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleTextShader, std::make_shared<SimpleTextShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SignedDistanceTextShader, std::make_shared<SignedDistanceTextShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SignedDistanceOutlineTextShader, std::make_shared<SignedDistanceOutlineTextShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleFragmentADSToonShader, std::make_shared<SimpleFragmentADSToonShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleFogShader, std::make_shared<SimpleFogShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleTextureShader, std::make_shared<SimpleTextureShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleDoubleTextureShader, std::make_shared<SimpleDoubleTextureShader>()));


	for (auto i = shaderMap.cbegin(); i != shaderMap.cend(); ++i)
	{
		TypeDatabase::registerShaderType((*i).second);
		i->second->setSharedData(sharedData);
	}
}

void Renderer::prepare()
{
	glClearColor(engineSettings->backgroundColor.r, engineSettings->backgroundColor.g, engineSettings->backgroundColor.b, engineSettings->backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}

void Renderer::prepare_GUIText()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
}

void Renderer::render()
{
	prepare();
	viewportManager->prepare(); // maybe not optimized!

	for (auto i = shaderMap.begin(); i != shaderMap.end(); ++i)
	{
		(*i).second->prepare();
	}

	for (auto i = 0; i != viewportManager->getSize(); i++)
	{
		viewportManager->getViewport(i)->prepare();
		sceneManager->cameraManager.activateCamera(viewportManager->getViewport(i)->getCamera()->getName());
		sharedData->prepare(); // TODO: can be optimized!

		for (auto it : sceneManager->entityMap.getMap())
		{
			std::shared_ptr<Entity> entity = it.second;
			if (!entity->getHidden())
			{
				std::shared_ptr<Shader> shader = shaderMap.find(entity->getModel()->getMaterial()->getShaderType())->second;
				shader->render(entity);
			}
		}
	}

	prepare_GUIText();
	for (auto it : sceneManager->GUITextManager.getMap())
	{
		std::shared_ptr<GUITextModel> model = it.second;
		std::shared_ptr<TextShader> shader = std::static_pointer_cast<TextShader>(shaderMap.find(model->getMaterial()->getShaderType())->second);
		shader->render(model);
		model->getMesh()->cleanUp();
		model.reset();
	}
	sceneManager->GUITextManager.cleanUp();
	finilize_GUIText();
}

void Renderer::finilize_GUIText()
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::installShaders()
{
	for (auto i = shaderMap.cbegin(); i != shaderMap.cend(); ++i)
	{
		i->second->install();
	}
	sharedData->init();
}

void Renderer::clearShaders()
{
	for (auto i = shaderMap.cbegin(); i != shaderMap.cend(); ++i)
	{
		i->second->cleanUp();
	}
	shaderMap.clear();
}

void Renderer::cleanUp()
{
	clearShaders();
}

void Renderer::update()
{
	for (std::size_t i = static_cast<std::size_t>(0); i != viewportManager->getSize(); ++i)
	{
		viewportManager->getViewport(i)->getCamera()->updateMatrix();
	}
}

std::shared_ptr<Shader> Renderer::getShader(const ShaderType & type)
{
	auto it = shaderMap.find(type);

	if (it == shaderMap.cend())
	{
		Debug::print(type);
		Debug::print("Shader not found!");
		Debug::print(" ");
		return nullptr;
	}
	return it->second;
}
