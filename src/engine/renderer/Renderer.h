#pragma once

#include "../shader/Shader.h"
#include <unordered_map>
#include "../entity/Entity.h"
#include "../scene/SceneManager.h"

class Renderer
{
public:
	void init(const std::shared_ptr<SceneManager> manager);
	void render();
	void installShaders();
	void clearShaders();
	void cleanUp();
	std::shared_ptr<Shader> getShader(const ShaderType& type);

protected:
	std::shared_ptr<SceneManager> sceneManager;
	std::unordered_map<ShaderType, std::shared_ptr<Shader>> shaderMap;
};