#include "GUITextManager.h"

void GUITextManager::addText(const std::shared_ptr<GUITextModel> model)
{
	auto it = map.find(model->getName());
	if (it == map.cend())
	{
		map.insert(std::make_pair(model->getName(), model));
	}
}
