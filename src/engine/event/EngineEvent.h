#pragma once
#include "EngineEventCode.h"
#include "glm\glm.hpp"
#include <string>

namespace engine{
	struct Event
	{
		Event(const EventCode& code) : code(code) {}
		EventCode code = EventCode::noCode;
	};

	struct ShutdownEvent : public Event
	{
		ShutdownEvent() : Event(EventCode::shutdown) {}
	};

	struct ChangeBackgroundEvent : Event
	{
		ChangeBackgroundEvent(const glm::vec4& data) : Event(EventCode::changeBackground), data(data) {}
		glm::vec4 data;
	};

	struct ChangeMaterialEvent : Event
	{
		ChangeMaterialEvent(const std::string& entityName, const std::string& materialName) : Event(EventCode::changeMaterial), entityName(entityName), materialName(materialName) {}
		std::string entityName;
		std::string materialName;
	};
}
