#pragma once
#include "EngineEventCode.h"
#include "..\clock\Cock.h"
#include "glm\glm.hpp"

namespace engine
{
	struct DelayedEvent
	{
		DelayedEvent(const EventCode& code, const double& lag) : code(code) 
		{
			execTime = Clock::time + lag;
		}
		EventCode code = EventCode::noCode;
		double execTime;
	};

	struct DelayedShutdownEvent : DelayedEvent
	{
		DelayedShutdownEvent(const double& lag) : DelayedEvent(EventCode::shutdown, lag) {}
	};

	struct DelayedChangeBackgroundEvent : DelayedEvent
	{
		DelayedChangeBackgroundEvent(const double& lag, const glm::vec4& color) : DelayedEvent(EventCode::changeBackground, lag), color(color) {}
		glm::vec4 color;
	};
}