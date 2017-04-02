#pragma once

#include "../shader/Shader.h"
#include <unordered_map>
#include "../entity/Entity.h"
#include "../scene/SceneManager.h"
#include "../settings/EngineSettings.h"
#include "../window/WindowSettings.h"
#include "../shader/util/ShaderSharedData.h"
#include "../viewport/ViewportManager.h"

class Renderer
{
public:
	void init(const std::shared_ptr<SceneManager> manager);
	inline void setWindowSettings(std::shared_ptr<WindowSettings> settings) { windowSettings = settings; }
	inline void setEngineSettings(std::shared_ptr<EngineSettings> settings) { engineSettings = settings; }
	inline void setViewportManager(std::shared_ptr<ViewportManager> manager) { viewportManager = manager; }
	void prepare();
	void render();
	void installShaders();
	void clearShaders();
	void cleanUp();
	void update();
	std::shared_ptr<Shader> getShader(const ShaderType& type);

protected:
	std::shared_ptr<ShaderSharedData> sharedData;
	std::shared_ptr<SceneManager> sceneManager;
	std::unordered_map<ShaderType, std::shared_ptr<Shader>> shaderMap;
	std::shared_ptr<EngineSettings> engineSettings;
	std::shared_ptr<WindowSettings> windowSettings;
	std::shared_ptr<ViewportManager> viewportManager;
};