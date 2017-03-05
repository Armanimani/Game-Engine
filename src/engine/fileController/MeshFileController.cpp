#include "MeshFileController.h"
#include "FileController.h"
#include <sstream>
#include <algorithm>
#include "FileReaderHelper.h"

std::shared_ptr<Mesh> MeshFileController::readFile(const std::string & path)
{
	std::string extension = path.substr(path.length() - 3, path.length());
	if (extension != "msh" && extension != "obj")
	{
		Debug::print(path);
		Debug::print("not a mesh File!");
		Debug::print(" ");
		return nullptr;
	}

	std::ifstream file;
	if (!FileController::openFile(file, path))
	{
		return nullptr;
	}

	if (extension == "msh")
	{
		std::string name;
		std::vector<GLfloat> verts;
		std::vector<GLuint> indices;
		std::vector<MeshAttribute> attribs;

		std::string line;
		std::string key;
		std::string value;

		while (std::getline(file, line, ';'))
		{
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			auto it = line.find('=');
			key = std::string(line.begin(), line.begin() + it);
			value = std::string(line.begin() + it + 1, line.end());

			if (key == "name")
			{
				name = value;
			}

			if (key == "verts")
			{
				FileReaderHelper::readValues(verts, value);
			}
			
			if (key == "indices")
			{
				FileReaderHelper::readValues(indices, value);
			}

			if (key == "attributes")
			{
				FileReaderHelper::readValues(attribs, value);
			}
		}

		return std::make_shared<Mesh>(name, verts, indices, attribs);
	}
	else if (extension == "obj")
	{
		Debug::print("obj file extension not yet implemented"); // TODO
		return nullptr;
	}

	return nullptr;
}
