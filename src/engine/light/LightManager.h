#pragma once
#include "Light.h"
#include "AmbientLight.h"
#include "SpotLight.h"
#include <vector>
#include <memory>
#include <unordered_map>

class LightManager
{
public:
	void addLight(const std::shared_ptr<Light>& light);
	void removeLight(const std::string& name);
	
	const std::vector <std::shared_ptr<SpotLight>> getActiveSpotLights();
	const std::vector <std::shared_ptr<AmbientLight>> getActiveAmbientLights();

	inline const std::unordered_map<std::string, std::shared_ptr<Light>>& getMap() { return map; }

	void cleanUp();

protected:
	std::unordered_map<std::string, std::shared_ptr<Light>> map;
};