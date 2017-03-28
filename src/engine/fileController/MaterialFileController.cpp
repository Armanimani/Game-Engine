#include "MaterialFileController.h"
#include "FileController.h"
#include <sstream>
#include <algorithm>
#include "../database/TypeDatabase.h"
#include "../fileController/FileReaderHelper.h"

std::shared_ptr<Material> MaterialFileController::readFile(const std::string & path)
{
	if (path.substr(path.length() - 3, path.length()) != "mat")
	{
		Debug::print(path);
		Debug::print("not a material File!");
		Debug::print(" ");
		return nullptr;
	}

	std::ifstream file;
	if (!FileController::openFile(file, path))
	{
		return nullptr;
	}

	std::string name;
	ShaderType shaderType;

	std::string line;
	std::string key;
	std::string value;
	MaterialProperties props;
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

		if (key == "shader")
		{
			shaderType = TypeDatabase::getShaderType(value);
		}

		if (key == "diffuseColor")
		{
			glm::vec3 color;
			FileReaderHelper::readValues(color, value);
			props.diffuseColor = color;
		}
		if (key == "diffuseReflectivity")
		{
			props.diffuseReflectivity = std::stof(value);
		}
		if (key == "ambientReflectivity")
		{
			props.ambientReflectivity = std::stof(value);
		}
		if (key == "specularReflectivity")
		{
			props.specularReflectivity = std::stof(value);
		}
		if (key == "shininessFactor")
		{
			props.shininessFactor = std::stof(value);
		}
	}

	FileController::closeFile(file, path);
	std::shared_ptr<Material> ret = std::make_shared<Material>(name, shaderType);
	ret->setPath(path);
	ret->setProperties(props);
	return ret;
}

void MaterialFileController::writeFile(const std::string & path, const std::shared_ptr<Material> mat)
{

	//TODO
	if (path.substr(path.length() - 3, path.length()) != "mat")
	{
		Debug::print(path);
		Debug::print("not a material File!");
		Debug::print(" ");
		return;
	}

	std::ofstream file;
	if (!FileController::openFile(file, path))
	{
		return;
	}

	file << "name = " << mat->getName() << ";\n";

	TypeDatabase::getShaderTypeName(mat->getShaderType());

	FileController::closeFile(file, path);
}
