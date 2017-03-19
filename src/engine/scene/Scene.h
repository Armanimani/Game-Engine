#pragma once
#include <Windows.h>
#include "../userInput/inputEvent/InputEvent.h"
#include "../userInput/inputEvent/InputHandlerCode.h"
#include <vector>
#include "../settings/SceneSettings.h"
#include <queue>
#include "../event/EngineEvent.h"
#include <memory>
#include <unordered_set>
#include "../event/DelayedEngineEvent.h"
#include "../scene/SceneManager.h"

class Scene
{
public:
	Scene(const std::string& name) : name(name) 
	{
		for (int i = 0; i != 256; ++i) keys[i] = false;
	}

	inline void setWindowHandle(const HWND& hwnd);
	inline const HWND& getWindowHandle() const;

	inline const std::string& getName() { return name; }

	virtual void handleInputEvent(const InputEvent& event, const InputHandlerCode& code);

	inline const std::string& getDataFile() { return settings.dataFile; }
	inline void setDataFile(const std::string& path) { settings.dataFile = path; };

	inline void setEngineEventList(std::queue<std::shared_ptr<engine::Event>>& list) {engineEventList = &list;}
	inline void setDelayedEngineEventList(std::unordered_set<std::shared_ptr<engine::DelayedEvent>>& list) {delayedEngineEventList = &list;};
	inline void registerEngineEvent(const std::shared_ptr<engine::Event>& e) { engineEventList->push(e); }
	inline void registerDelayedEngineEvent(const std::shared_ptr<engine::DelayedEvent>& e) { delayedEngineEventList->insert(e); }

	inline void setSceneManager(const std::shared_ptr<SceneManager> manager) { this->manager = manager; }

	virtual void update() {};

protected:
	std::string name;
	const HWND* hWnd;
	SceneSettings settings;

	std::queue<std::shared_ptr<engine::Event>>* engineEventList;
	std::unordered_set<std::shared_ptr<engine::DelayedEvent>>* delayedEngineEventList;

	std::shared_ptr<SceneManager> manager; //TODO: need to be removed later! need to only have a pointer of the materials set!
	
	bool keys[256];
};

const HWND& Scene::getWindowHandle() const
{
	return *hWnd;
}
void Scene::setWindowHandle(const HWND& hwnd)
{
	hWnd = &hwnd;
}