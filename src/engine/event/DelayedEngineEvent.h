#pragma once
#include "EngineEventCode.h"
#include "..\clock\Cock.h"
#include "glm\glm.hpp"
#include <string>

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

	struct DelayedChangeMaterialEvent : DelayedEvent
	{
		DelayedChangeMaterialEvent(const double& lag, const std::string& entityName, const std::string& materialName) : DelayedEvent(EventCode::changeMaterial, lag), entityName(entityName), materialName(materialName) {}
		std::string entityName;
		std::string materialName;
	};
}