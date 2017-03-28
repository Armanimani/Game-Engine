#pragma once
#include <glm\glm.hpp>
#include <glew\GL\glew.h>

struct MaterialProperties
{
	glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLfloat ambientReflectivity = 0.0f;
	GLfloat diffuseReflectivity = 0.0f;
	GLfloat specularReflectivity = 0.0f;
	GLfloat shininessFactor = 0.0f;
};