#include "FogManager.h"

void FogManager::addItem(const std::shared_ptr<Fog> item)
{
	if (map.size() == 0)
	{
		map.insert(std::make_pair(item->getName(), item));
	}
	else
	{
		auto it = map.find(item->getName());
		if (it == map.cend())
		{
			map.insert(std::make_pair(item->getName(), item));
		}
	}
}

void FogManager::removeItem(const std::string & name)
{
}
