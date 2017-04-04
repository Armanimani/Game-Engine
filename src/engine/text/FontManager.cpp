#include "FontManager.h"

void FontManager::addFont(const std::shared_ptr<Font> font)
{
	auto it = map.find(font->getName());
	if (it == map.cend())
	{
		map.insert(std::make_pair(font->getName(), font));
	}
}

void FontManager::removeFont(const std::string & name)
{
	// TODO
}

const std::shared_ptr<Font> FontManager::getFont(const std::string & name)
{
	auto it = map.find(name);
	if (it == map.cend()) return nullptr;
	return (*it).second;
}
