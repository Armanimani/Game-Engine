#include "FileReaderHelper.h"
#include <algorithm>
#include "../debug/Debug.h"
#include "../database/TypeDatabase.h"


void FileReaderHelper::readValues(std::vector<GLfloat>& vec, std::string & value)
{
	value.erase(std::remove(value.begin(), value.end(), '{'), value.end());
	value.erase(std::remove(value.begin(), value.end(), '}'), value.end());

	while (true)
	{
		auto pos = value.find(',');
		if (pos == std::string::npos)
		{
			vec.push_back(std::stof(value));
			break;
		}
		vec.push_back(std::stof(value.substr(0, pos)));
		value.erase(value.cbegin(), value.cbegin() + pos + 1);
	}
}

void FileReaderHelper::readValues(std::vector<GLuint>& vec, std::string & value)
{
	value.erase(std::remove(value.begin(), value.end(), '{'), value.end());
	value.erase(std::remove(value.begin(), value.end(), '}'), value.end());
	while (true)
	{
		auto pos = value.find(',');
		if (pos == std::string::npos)
		{
			vec.push_back((GLuint)std::stoi(value));
			break;
		}
		vec.push_back(std::stoi(value.substr(0, pos)));
		value.erase(value.cbegin(), value.cbegin() + pos + 1);
	}
}

void FileReaderHelper::readValues(std::vector<MeshAttribute>& vec, std::string & value)
{
	value.erase(std::remove(value.begin(), value.end(), '{'), value.end());
	value.erase(std::remove(value.begin(), value.end(), '}'), value.end());
	while (true)
	{
		auto pos = value.find(',');
		if (pos == std::string::npos)
		{
			vec.push_back(TypeDatabase::getMeshAttributeType(value));
			break;
		}
		vec.push_back(TypeDatabase::getMeshAttributeType(value.substr(0, pos)));
		value.erase(value.cbegin(), value.cbegin() + pos + 1);
	}
}

void FileReaderHelper::readValues(glm::vec3 & vec, std::string & value)
{
	std::vector<GLfloat> temp;
	while (true)
	{
		auto pos = value.find(',');
		if (pos == std::string::npos)
		{
			temp.push_back(std::stof(value));
			break;
		}
		temp.push_back(std::stof(value.substr(0, pos)));
		value.erase(value.cbegin(), value.cbegin() + pos + 1);
	}
	vec = glm::vec3(temp[0], temp[1], temp[2]);
}

