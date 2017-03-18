#pragma once
#include "Camera.h"
#include <unordered_map>

class CameraManager
{
public:
	void addCamera(const std::shared_ptr<Camera> cam);
	void removeCamera(const std::string& name);
	void activateCamera(const std::string& name);
	inline const std::shared_ptr<Camera> getActiveCamera() { return activeCamera; }

	const std::shared_ptr<Camera> getCamera(const std::string& name);
	inline const std::unordered_map<std::string, std::shared_ptr<Camera>>& getMap() { return map; }
	void updateMatrix();
	inline void cleanUp() { map.clear(); }

protected:
	std::unordered_map<std::string, std::shared_ptr<Camera>> map;
	std::shared_ptr<Camera> activeCamera;
};