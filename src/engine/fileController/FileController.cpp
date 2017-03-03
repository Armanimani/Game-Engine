#include "FileController.h"

bool FileController::openFile(std::ofstream & file, const std::string & path)
{
	file.open(path);
	if (!file.is_open())
	{
		Debug::print(path);
		Debug::print("Unable to open file");
		Debug::print(" ");
		return false;
	}
	return true;
}

bool FileController::closeFile(std::ofstream & file, const std::string & path)
{
	file.close();
	if (file.is_open())
	{
		Debug::print(path);
		Debug::print("Unable to close file");
		Debug::print(" ");
		return false;
	}
	return true;
}

bool FileController::openFile(std::ifstream & file, const std::string & path)
{
	file.open(path);
	if (!file.is_open())
	{
		Debug::print(path);
		Debug::print("Unable to open file");
		Debug::print(" ");
		return false;
	}
	return true;
}

bool FileController::closeFile(std::ifstream & file, const std::string & path)
{
	file.close();
	if (file.is_open())
	{
		Debug::print(path);
		Debug::print("Unable to close file");
		Debug::print(" ");
		return false;
	}
	return true;
}
