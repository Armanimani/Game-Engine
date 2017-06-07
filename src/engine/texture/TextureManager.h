#pragma once

#include "ModelTexture.h"
#include <memory>
#include <unordered_map>

class TextureManager
{
public:
	void addTexture(const std::shared_ptr<ModelTexture> text);
	void removeTexture(const std::string& name);
	const std::shared_ptr<ModelTexture> getTexture(const std::string& name);
	inline const std::unordered_map<std::string, std::shared_ptr<ModelTexture>>& getMap() { return map; }

	inline void cleanUp() { map.clear(); }

protected:
	std::unordered_map<std::string, std::shared_ptr<ModelTexture>> map;
};