#pragma once

#include "Fog.h"
#include <unordered_map>
#include <memory>

class FogManager
{
public:
	void addItem(const std::shared_ptr<Fog> item);
	void removeItem(const std::string& name);
	
	inline const std::unordered_map<std::string, std::shared_ptr<Fog>>& getMap() { return map; }

	inline void cleanUp() { map.clear();  }
protected:
	std::unordered_map<std::string, std::shared_ptr<Fog>> map;
};

//TODO: add support for multiple fogs!