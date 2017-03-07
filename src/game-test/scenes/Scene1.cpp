#include "Scene1.h"
#include "../../engine/debug/Debug.h"

void Scene1::handleInputEvent(const InputEvent & event, const InputHandlerCode & code)
{
	switch (event.key)
	{
	case (KeyCode::F4):
	{
		if (event.ctrlDown)
		{
			engineEventList->push(std::make_shared<EngineEvent>(EngineEventCode::shutdown));
		}
		break;
	}
	case (KeyCode::NUM1):
	{
		engineEventList->push(std::make_shared<EngineEvent>(EngineEventCode::changeBackground, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		break;
	}
	case (KeyCode::NUM2):
	{
		engineEventList->push(std::make_shared<EngineEvent>(EngineEventCode::changeBackground, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
		break;
	}
	case (KeyCode::NUM3):
	{
		engineEventList->push(std::make_shared<EngineEvent>(EngineEventCode::changeBackground, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		break;
	}
	case (KeyCode::NUM4):
	{
		engineEventList->push(std::make_shared<EngineEvent>(EngineEventCode::changeBackground, glm::vec4(1.0f, 1.0f, 0.0f, 0.5f)));
		break;
	}
	case (KeyCode::NUM5):
	{
		engineEventList->push(std::make_shared<EngineEvent>(EngineEventCode::changeBackground, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
		break;
	}
	}
}
