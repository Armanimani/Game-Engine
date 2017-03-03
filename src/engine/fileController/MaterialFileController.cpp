#include "MaterialFileController.h"
#include "FileController.h"
#include <sstream>
#include <algorithm>

std::shared_ptr<Material> MaterialFileController::readFile(const std::string & path)
{
	auto it = path.find('.');
	if (path.substr(it + 1, 3) != "mat")
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
	while (std::getline(file, line, ';'))
	{
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
		std::stringstream stream(line);
		auto it = line.find('=');
		key = std::string(line.begin(), line.begin() + it);
		value = std::string(line.begin() + it + 1, line.end());

		if (key == "name")
		{
			name = value;
		}

		if (key == "shaderType")
		{
			if (value == "BasicShader")
			{
				shaderType = ShaderType::BasicShader;
			}
			else if (value == "SimplePositionShader")
			{
				shaderType = ShaderType::SimplePositionShader;
			}
			else if (value == "SimpleColorShader")
			{
				shaderType = ShaderType::SimpleColorShader;
			}
			else
			{
				Debug::print(path);
				Debug::print(value);
				Debug::print("undefined Shader class");
				Debug::print(" ");
				FileController::closeFile(file, path);
				return nullptr;
			}
		}
	}

	FileController::closeFile(file, path);

	return std::make_shared<Material>(name, shaderType);
}

void MaterialFileController::writeFile(const std::string & path, const std::shared_ptr<Material> mat)
{
	auto it = path.find('.');
	if (path.substr(it + 1, 3) != "mat")
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

	if (mat->getShaderType() == ShaderType::BasicShader)
	{
		file << "shaderType = " << "BasicShader" << ";\n";
	}
	else if (mat->getShaderType() == ShaderType::SimplePositionShader)
	{
		file << "shaderType = " << "SimplePositionShader" << ";\n";
	}
	else if (mat->getShaderType() == ShaderType::SimpleColorShader)
	{
		file << "shaderType = " << "SimpleColorShader" << ";\n";
	}
	else
	{
		Debug::print(path);
		Debug::print(mat->getName());
		Debug::print("undefined Shader class");
		Debug::print(" ");
		FileController::closeFile(file, path);
		return;
	}

	FileController::closeFile(file, path);
}
