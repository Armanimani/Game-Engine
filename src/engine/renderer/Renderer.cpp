#include "Renderer.h"

#include "../shader/BasicShader.h"
#include "../shader/SimplePositionShader.h"
#include "../shader/SimpleColorShader.h"
#include "../shader/SimpleDiffuseColorShader.h"
#include "../debug/Debug.h"

void Renderer::init(const std::shared_ptr<SceneManager> manager)
{
	sceneManager = manager;
	shaderMap.insert(std::make_pair(ShaderType::BasicShader, std::make_shared<BasicShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimplePositionShader, std::make_shared<SimplePositionShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleColorShader, std::make_shared<SimpleColorShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleDiffuseColorShader, std::make_shared<SimpleDiffuseColorShader>()));
}

void Renderer::render()
{
	for (auto it : sceneManager->entityMap.getMap())
	{
		std::shared_ptr<Entity> entity = it.second;
		std::shared_ptr<Shader> shader = shaderMap.find(entity->getModel()->getMaterial()->getShaderType())->second;
		shader->render(entity);
	}
}

void Renderer::installShaders()
{
	for (auto i = shaderMap.cbegin(); i != shaderMap.cend(); ++i)
	{
		i->second->install();
	}
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
