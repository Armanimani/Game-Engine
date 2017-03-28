#pragma once
#include <vector>
#include <glew\GL\glew.h>
#include <string>
#include "../mesh/MeshAttribute.h"
#include "glm\glm.hpp"

class FileReaderHelper
{
public:
	static void readValues(std::vector<GLfloat>& vec, std::string& value);
	static void readValues(std::vector<GLuint>& vec, std::string& value);
	static void readValues(std::vector<MeshAttribute>& vec, std::string& value);
	static void readValues(glm::vec3& vec, std::string& value);
	static void readValues(glm::vec4& vec, std::string& value);
};