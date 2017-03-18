#include "CameraManager.h"

void CameraManager::addCamera(const std::shared_ptr<Camera> cam)
{
	if (map.size() == 0)
	{
		cam->setActive(true);
		map.insert(std::make_pair(cam->getName(), cam));
		activateCamera(cam->getName());
	}
	else
	{
		auto it = map.find(cam->getName());
		if (it == map.cend())
		{
			map.insert(std::make_pair(cam->getName(), cam));
		}
	}
}

void CameraManager::removeCamera(const std::string & name)
{
	//TODO
}

void CameraManager::activateCamera(const std::string & name)
{
	auto it = map.find(name);
	if (it == map.cend()) return;

	for (auto i = map.cbegin(); i != map.cend(); ++i)
	{
		(*i).second->setActive(false);
	}

	(*it).second->setActive(true);
	activeCamera = (*it).second;
}

const std::shared_ptr<Camera> CameraManager::getCamera(const std::string & name)
{
	auto it = map.find(name);
	if (it == map.cend()) return nullptr;

	return (*it).second;
}

void CameraManager::updateMatrix()
{
	for (auto i = map.cbegin(); i != map.cend(); ++i)
	{
		(*i).second->updateMatrix();
	}
}
