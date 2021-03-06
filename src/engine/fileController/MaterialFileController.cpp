#include "MaterialFileController.h"
#include "FileController.h"
#include <sstream>
#include <algorithm>
#include "../database/TypeDatabase.h"
#include "../fileController/FileReaderHelper.h"

std::shared_ptr<Material> MaterialFileController::readFile(const std::string & path, const std::shared_ptr<SceneManager> manager)
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
		else if (key == "shader")
		{
			shaderType = TypeDatabase::getShaderType(value);
		}
		else if (key == "color")
		{
			glm::vec4 color;
			FileReaderHelper::readValues(color, value);
			props.color = color;
		}
		else if (key == "color2")
		{
			glm::vec4 color;
			FileReaderHelper::readValues(color, value);
			props.color2 = color;
		}
		else if (key == "specularColor")
		{
			glm::vec4 color;
			FileReaderHelper::readValues(color, value);
			props.specularColor = color;
		}
		else if (key == "colorBack")
		{
			glm::vec4 color;
			FileReaderHelper::readValues(color, value);
			props.colorBack = color;
		}
		else if (key == "specularColorBack")
		{
			glm::vec4 color;
			FileReaderHelper::readValues(color, value);
			props.specularColorBack = color;
		}
		else if (key == "diffuseReflectivity")
		{
			props.diffuseReflectivity = std::stof(value);
		}
		else if (key == "ambientReflectivity")
		{
			props.ambientReflectivity = std::stof(value);
		}
		else if (key == "specularReflectivity")
		{
			props.specularReflectivity = std::stof(value);
		}
		else if (key == "shininess")
		{
			props.shininessFactor = std::stof(value);
		}
		else if (key == "discardScale")
		{
			props.discardScale = std::stof(value);
		}
		else if (key == "discardThickness")
		{
			props.discardThickness = std::stof(value);
		}
		else if (key == "fontEdge")
		{
			props.fontEdge = std::stof(value);
		}
		else if (key == "fontWidth")
		{
			props.fontWidth = std::stof(value);
		}
		else if (key == "fontOutlineWidth")
		{
			props.fontOutlineWidth = std::stof(value);
		}
		else if (key == "fontOutlineEdge")
		{
			props.fontOutlineEdge = std::stof(value);
		}
		else if (key == "fontOutlineOffsetX")
		{
			props.fontOutlineOffsetX = std::stof(value);
		}
		else if (key == "fontOutlineOffsetY")
		{
			props.fontOutlineOffsetY = std::stof(value);
		}
		else if (key == "toonLevel")
		{
			props.toonLevel = std::stof(value);
		}
		else if (key == "texture0")
		{
			props.texture0 = manager->textureMap.getItem(value);
		}
		else if (key == "texture1")
		{
			props.texture1 = manager->textureMap.getItem(value);
		}
		else if (key == "texture2")
		{
			props.texture2 = manager->textureMap.getItem(value);
		}
		else if (key == "texture3")
		{
			props.texture3 = manager->textureMap.getItem(value);
		}
		else if (key == "texture4")
		{
			props.texture4 = manager->textureMap.getItem(value);
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
