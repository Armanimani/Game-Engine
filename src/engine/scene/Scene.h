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
#include "../userInput/inputData/InputData.h"
#include "../viewport/ViewportManager.h"
#include "../window/WindowSettings.h"

class Scene
{
public:
	Scene(const std::string& name) : name(name) {}

	inline void setWindowHandle(const HWND& hwnd) { hWnd = &hwnd; }
	inline const HWND& getWindowHandle() const { return *hWnd; }

	inline const std::string& getName() { return name; }

	virtual void handleInputEvent(const InputEvent& event, const InputHandlerCode& code);

	inline const std::string& getDataFile() { return settings.dataFile; }
	inline void setDataFile(const std::string& path) { settings.dataFile = path; };

	virtual void setViewports(const std::shared_ptr<WindowSettings> windowSettings);

	inline void setEngineEventList(std::queue<std::shared_ptr<engine::Event>>& list) {engineEventList = &list;}
	inline void setDelayedEngineEventList(std::unordered_set<std::shared_ptr<engine::DelayedEvent>>& list) {delayedEngineEventList = &list;};
	inline void registerEngineEvent(const std::shared_ptr<engine::Event>& e) { engineEventList->push(e); }
	inline void registerDelayedEngineEvent(const std::shared_ptr<engine::DelayedEvent>& e) { delayedEngineEventList->insert(e); }

	inline void setSceneManager(const std::shared_ptr<SceneManager> manager) { this->manager = manager; }
	inline void setViewportManager(std::shared_ptr<ViewportManager> manager) { viewportManager = manager; }

	virtual void update() {};

protected:
	std::string name;
	const HWND* hWnd;
	SceneSettings settings;

	InputData inputData;

	std::queue<std::shared_ptr<engine::Event>>* engineEventList;
	std::unordered_set<std::shared_ptr<engine::DelayedEvent>>* delayedEngineEventList;

	std::shared_ptr<SceneManager> manager; //TODO: need to be removed later! need to only have a pointer of the materials set!
	std::shared_ptr<ViewportManager> viewportManager;

	const bool& getKeyState(const KeyCode& code) { return inputData.keys[static_cast<int>(code)]; }
	inline void setKeyState(const KeyCode& code, const bool& state = true) { inputData.keys[static_cast<int>(code)] = state; }

	virtual void defaultInputEventHandle(const InputEvent& event);
	virtual void handleInputKeys() {};

	void defaultCameraInputHandler(const InputEvent& event, const InputHandlerCode& code);

private:
	std::shared_ptr<Camera> cam;

};