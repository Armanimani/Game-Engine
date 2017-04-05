#pragma once
#include <glm\glm.hpp>
#include <glew\GL\glew.h>

struct MaterialProperties
{
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 color2 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 colorBack = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularColorBack = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat ambientReflectivity = 0.0f;
	GLfloat diffuseReflectivity = 0.0f;
	GLfloat specularReflectivity = 0.0f;
	GLfloat shininessFactor = 0.0f;
	GLfloat discardScale = 10.0f;
	GLfloat discardThickness = 0.0f;

	GLfloat fontEdge = 0.0f;
	GLfloat fontWidth = 0.0f;
	GLfloat fontOutlineEdge = 0.0f;
	GLfloat fontOutlineWidth = 0.0f;
	GLfloat fontOutlineOffsetX = 0.0f;
	GLfloat fontOutlineOffsetY = 0.0f;
};