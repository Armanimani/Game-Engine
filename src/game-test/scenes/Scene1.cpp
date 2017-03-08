#include "Scene1.h"
#include "../../engine/debug/Debug.h"

void Scene1::handleInputEvent(const InputEvent & event, const InputHandlerCode & code)
{
	if (event.type == InputEventType::KEY_DOWN)
	{
		switch (event.key)
		{
		case (KeyCode::F4):
		{
			if (event.ctrlDown)
			{
				registerEngineEvent(std::make_shared<engine::ShutdownEvent>());
			}
			break;
		}
		case (KeyCode::NUM1):
		{
			registerEngineEvent(std::make_shared<engine::ChangeBackgroundEvent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
			break;
		}
		case (KeyCode::NUM2):
		{
			registerEngineEvent(std::make_shared<engine::ChangeBackgroundEvent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
			break;
		}
		case (KeyCode::NUM3):
		{
			registerEngineEvent(std::make_shared<engine::ChangeBackgroundEvent>(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
			break;
		}
		case (KeyCode::NUM4):
		{
			registerEngineEvent(std::make_shared<engine::ChangeBackgroundEvent>(glm::vec4(1.0f, 1.0f, 0.0f, 0.5f)));
			break;
		}
		case (KeyCode::NUM5):
		{
			registerEngineEvent(std::make_shared<engine::ChangeBackgroundEvent>(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
			break;
		}
		case (KeyCode::F5):
		{
			if (event.ctrlDown)
			{
				registerDelayedEngineEvent(std::make_shared<engine::DelayedShutdownEvent>(5.0));
			}
			break;
		}
		case (KeyCode::NUM6):
			registerDelayedEngineEvent(std::make_shared<engine::DelayedChangeBackgroundEvent>(5.0, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		}
	}
}

void Scene1::update()
{

}
