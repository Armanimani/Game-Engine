#include "Scene.h"
#include "../debug/Debug.h"

void Scene::handleInputEvent(const InputEvent& event, const InputHandlerCode& code)
{
	Debug::print(event);
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
		inputData.mouseWheelDelta = event.wheelDelta;
	}
}

void Scene::defaultCameraInputHandler(const InputEvent & event, const InputHandlerCode& code)
{
	if (code == InputHandlerCode::onMouse_wheel)
	{
		manager->cameraManager.getActiveCamera()->moveForward(event.wheelDelta / 250.0f);
	}
	else if (code == InputHandlerCode::onMouse_move && (event.mouseLDown || event.mouseRDown || event.mouseMDown))
	{
		if (event.mouseLDown)
		{
			inputData.mouseDragL = glm::vec2(event.posX, event.posY) - inputData.mousePrevPosL;
			inputData.mousePrevPosL = glm::vec2(event.posX, event.posY);
			manager->cameraManager.getActiveCamera()->translate(glm::vec2(-inputData.mouseDragL.x, inputData.mouseDragL.y) / 250.0f);
		}
		if (event.mouseRDown)
		{
			inputData.mouseDragR = glm::vec2(event.posX, event.posY) - inputData.mousePrevPosR;
			inputData.mousePrevPosR = glm::vec2(event.posX, event.posY);
			if (event.shiftDown)
			{
				manager->cameraManager.getActiveCamera()->rotateUp(inputData.mouseDragR.x / 100.0f);
			}
			else if (event.ctrlDown)
			{
				manager->cameraManager.getActiveCamera()->rotateRight(inputData.mouseDragR.y / 100.0f);
			}
			else
			{
				manager->cameraManager.getActiveCamera()->orbit(inputData.mouseDragR / 100.0f);
			}

		}
		if(event.mouseMDown)
		{
			inputData.mouseDragM = glm::vec2(event.posX, event.posY) - inputData.mousePrevPosM;
			inputData.mousePrevPosM = glm::vec2(event.posX, event.posY);
			manager->cameraManager.getActiveCamera()->rotateForward((inputData.mouseDragM.x + inputData.mouseDragM.y) / 250.0f);
		}
	}
}
