#include "Scene.h"
#include "../debug/Debug.h"
#include "../viewport/layout/ViewportLayoutDefault.h"
#include "../viewport/layout/ViewportLayoutH2V1.h"
#include "../viewport/layout/ViewportLayoutH1V2.h"
#include "../viewport/layout/ViewportLayoutH2V2.h"

// TODO add changelayout

void Scene::handleInputEvent(const InputEvent& event, const InputHandlerCode& code)
{
	Debug::print(event);
}

void Scene::setViewports()
{
	std::shared_ptr<ViewportLayout> layout = std::make_shared<ViewportLayoutDefault>(windowSettings);
	std::vector<std::shared_ptr<Camera>> cams;
	cams.push_back(manager->cameraManager.getCamera("mainCamera"));
	viewportManager->setLayout(layout, cams);

	//std::shared_ptr<ViewportLayoutH2V1> layout = std::make_shared<ViewportLayoutH2V1>(windowSettings, 0.5);
	//std::vector<std::shared_ptr<Camera>> cams;
	//cams.push_back(manager->cameraManager.getCamera("mainCamera"));
	//cams.push_back(manager->cameraManager.getCamera("orthoCam"));
	//viewportManager->setLayout(layout, cams);

	//std::shared_ptr<ViewportLayoutH1V2> layout = std::make_shared<ViewportLayoutH1V2>(windowSettings, 0.5);
	//std::vector<std::shared_ptr<Camera>> cams;
	//cams.push_back(manager->cameraManager.getCamera("mainCamera"));
	//cams.push_back(manager->cameraManager.getCamera("orthoCam"));
	//viewportManager->setLayout(layout, cams);

	//std::shared_ptr<ViewportLayoutH2V2> layout = std::make_shared<ViewportLayoutH2V2>(windowSettings, 0.5, 0.5);
	//std::vector<std::shared_ptr<Camera>> cams;
	//cams.push_back(manager->cameraManager.getCamera("mainCamera"));
	//cams.push_back(manager->cameraManager.getCamera("orthoCam"));
	//cams.push_back(manager->cameraManager.getCamera("arcBallCam"));
	//cams.push_back(manager->cameraManager.getCamera("orthoCam2D"));
	//viewportManager->setLayout(layout, cams);
}

void Scene::defaultInputEventHandle(const InputEvent & event)
{
	if (event.type == InputEventType::KEY_DOWN)
	{
		setKeyState(event.key);
	}
	else if (event.type == InputEventType::KEY_UP)
	{
		setKeyState(event.key, false);
	}
	
	if (event.type == InputEventType::MOUSE_DOWN)
	{
		cam = viewportManager->findCamera(event.posX, event.posY);
		switch (event.key)
		{
		case(KeyCode::MOUSE_L):
		{
			inputData.mousePrevPosL = glm::vec2(event.posX, event.posY);
			break;
		}
		case (KeyCode::MOUSE_R):
		{
			inputData.mousePrevPosR = glm::vec2(event.posX, event.posY);
			break;
		}
		case (KeyCode::MOUSE_M):
		{
			inputData.mousePrevPosM = glm::vec2(event.posX, event.posY);
		}
		}
	}
	else if (event.type == InputEventType::MOUSE_WHEEL)
	{
		cam = viewportManager->findCamera(event.posX, event.posY);
		inputData.mouseWheelDelta = event.wheelDelta;
	}
}

void Scene::defaultCameraInputHandler(const InputEvent & event, const InputHandlerCode& code)
{
	
	if (code == InputHandlerCode::onMouse_wheel)
	{
		if (event.shiftDown)
		{
			cam->moveForward(event.wheelDelta / 250.0f);
		}
		else
		{
			cam->zoom(event.wheelDelta / 250.0f);
		}
	}
	else if (code == InputHandlerCode::onMouse_move && (event.mouseLDown || event.mouseRDown || event.mouseMDown))
	{
		if (event.mouseLDown)
		{
			inputData.mouseDragL = glm::vec2(event.posX, event.posY) - inputData.mousePrevPosL;
			inputData.mousePrevPosL = glm::vec2(event.posX, event.posY);
			cam->translate(glm::vec2(-inputData.mouseDragL.x, inputData.mouseDragL.y) / 250.0f);
		}
		if (event.mouseRDown)
		{
			inputData.mouseDragR = glm::vec2(event.posX, event.posY) - inputData.mousePrevPosR;
			inputData.mousePrevPosR = glm::vec2(event.posX, event.posY);
			if (event.shiftDown)
			{
				cam->rotateUp(inputData.mouseDragR.x / 10.0f);
			}
			else if (event.ctrlDown)
			{
				cam->rotateRight(inputData.mouseDragR.y / 10.0f);
			}
			else
			{
				cam->orbit(inputData.mouseDragR / 10.0f);
			}

		}
		if(event.mouseMDown)
		{
			inputData.mouseDragM = glm::vec2(event.posX, event.posY) - inputData.mousePrevPosM;
			inputData.mousePrevPosM = glm::vec2(event.posX, event.posY);
			cam->rotateForward(inputData.mouseDragM.x / 10.0f);
		}
	}
}

void Scene::changeViewportLayout(const std::shared_ptr<ViewportLayout> layout, const std::vector<std::shared_ptr<Camera>> cams)
{
	viewportManager->cleanUp();
	viewportManager->setLayout(layout, cams);
}
