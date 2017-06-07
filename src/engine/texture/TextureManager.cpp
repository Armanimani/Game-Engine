#include "TextureManager.h"

void TextureManager::addTexture(const std::shared_ptr<ModelTexture> texture)
{
	auto it = map.find(texture->getName());
	if (it == map.cend())
	{
		map.insert(std::make_pair(texture->getName(), texture));
	}
}

void TextureManager::removeTexture(const std::string & name)
{
	//TODO
}

const std::shared_ptr<ModelTexture> TextureManager::getTexture(const std::string & name)
{
	auto it = map.find(name);
	if (it == map.cend()) return nullptr;
	return (*it).second;
}
