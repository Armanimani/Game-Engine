#pragma once
#include "EngineEventCode.h"
#include "glm\glm.hpp"

struct EngineEvent
{
	EngineEvent(const EngineEventCode& code) : code(code) {}
	EngineEvent(const EngineEventCode& code, glm::vec4 data) : code(code), vec4Data(data) {}
	EngineEventCode code = EngineEventCode::noCode;
	glm::vec4 vec4Data;
};
