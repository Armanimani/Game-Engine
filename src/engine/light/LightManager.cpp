#include "LightManager.h"

void LightManager::addLight(const std::shared_ptr<Light>& light)
{
	if (map.size() == 0)
	{
		map.insert(std::make_pair(light->getName(), light));
	}
	else
	{
		auto it = map.find(light->getName());
		if (it == map.cend())
		{
			map.insert(std::make_pair(light->getName(), light));
		}
	}
}

void LightManager::removeLight(const std::string & name)
{
	//TODO
}

const std::vector<std::shared_ptr<SpotLight>> LightManager::getActiveSpotLights()
{
	std::vector<std::shared_ptr<SpotLight>> ret;
	ret.reserve(16);

	for (auto it = map.cbegin(); it != map.cend(); it++)
	{
		if ((*it).second->getOn() && (*it).second->getType() == LightType::spot) ret.push_back(std::static_pointer_cast<SpotLight>((*it).second));
	}

	return ret;
}

const std::vector<std::shared_ptr<AmbientLight>> LightManager::getActiveAmbientLights()
{
	std::vector<std::shared_ptr<AmbientLight>> ret;
	ret.reserve(16);

	for (auto it = map.cbegin(); it != map.cend(); it++)
	{
		if ((*it).second->getOn() && (*it).second->getType() == LightType::ambient) ret.push_back(std::static_pointer_cast<AmbientLight>((*it).second));
	}

	return ret;
}

void LightManager::cleanUp()
{
	map.clear();
}
