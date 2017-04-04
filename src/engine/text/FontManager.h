#pragma once

#include "Font.h"
#include <unordered_map>
#include <memory>

class FontManager
{
public:
	void addFont(const std::shared_ptr<Font> font);
	void removeFont(const std::string& name);
	const std::shared_ptr<Font> getFont(const std::string& name);
	inline const std::unordered_map<std::string, std::shared_ptr<Font>>& getMap() { return map; }

	inline void cleanUp() { map.clear(); }

protected:
	std::unordered_map<std::string, std::shared_ptr<Font>> map;
};