#include "ShaderManager.h"

#include "BasicShader.h"
#include "SimplePositionShader.h"
#include "SimpleColorShader.h"
#include "../debug/Debug.h"

void ShaderManager::init()
{
	shaderMap.insert(std::make_pair(ShaderType::BasicShader, std::make_shared<BasicShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimplePositionShader, std::make_shared<SimplePositionShader>()));
	shaderMap.insert(std::make_pair(ShaderType::SimpleColorShader, std::make_shared<SimpleColorShader>()));
}

void ShaderManager::installShaders()
{
	for (auto i = shaderMap.cbegin(); i != shaderMap.cend(); ++i)
	{
		i->second->install();
	}
}

void ShaderManager::clearShaders()
{
	for (auto i = shaderMap.cbegin(); i != shaderMap.cend(); ++i)
	{
		i->second->cleanUp();
	}
	shaderMap.clear();
}

void ShaderManager::cleanUp()
{
	clearShaders();
}

std::shared_ptr<Shader> ShaderManager::getShader(const ShaderType & type)
{
	auto it = shaderMap.find(type);
	
	if (it == shaderMap.cend())
	{
		Debug::print(type);
		return nullptr;
	}
	return it->second;
}
