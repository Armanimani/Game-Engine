#pragma once
#include "EngineEventCode.h"
#include "glm\glm.hpp"

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

	struct ChangeBackgroundEvent : public Event
	{
		ChangeBackgroundEvent(const glm::vec4& data) : Event(EventCode::changeBackground), data(data) {}
		glm::vec4 data;
	};
}
