#pragma once
#include "../model/GUITextModel.h"
#include <unordered_map>

class GUITextManager
{
public:
	void addText(const std::shared_ptr<GUITextModel> model);
	inline void cleanUp() { map.clear(); }
	inline const std::unordered_map<std::string, std::shared_ptr<GUITextModel>> getMap() { return map; 
	}
protected:
	std::unordered_map<std::string, std::shared_ptr<GUITextModel>> map;
};