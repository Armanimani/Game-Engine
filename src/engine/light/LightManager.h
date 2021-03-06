#pragma once
#include "Light.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include <vector>
#include <memory>
#include <unordered_map>

class LightManager
{
public:
	void addLight(const std::shared_ptr<Light>& light);
	void removeLight(const std::string& name);
	
	const std::vector<std::shared_ptr<PointLight>> getActivePointLights();
	const std::vector<std::shared_ptr<AmbientLight>> getActiveAmbientLights();
	const std::vector<std::shared_ptr<DirectionalLight>> getActiveDirectionalLights();
	const std::vector<std::shared_ptr<SpotLight>> getActiveSpotLights();

	inline const std::unordered_map<std::string, std::shared_ptr<Light>>& getMap() { return map; }

	void cleanUp();

protected:
	std::unordered_map<std::string, std::shared_ptr<Light>> map;
};