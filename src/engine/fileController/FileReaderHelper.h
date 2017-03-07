#pragma once
#include <vector>
#include <glew\GL\glew.h>
#include <string>
#include "../mesh/MeshAttribute.h"

class FileReaderHelper
{
public:
	static void readValues(std::vector<GLfloat>& vec, std::string& value);
	static void readValues(std::vector<GLuint>& vec, std::string& value);
	static void readValues(std::vector<MeshAttribute>& vec, std::string& value);
};