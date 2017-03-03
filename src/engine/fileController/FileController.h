#pragma once
#include <fstream>
#include "../debug/Debug.h"

class FileController
{
public:
	static bool openFile(std::ofstream& file, const std::string& path);
	static bool closeFile(std::ofstream& file, const std::string& path);
	static bool openFile(std::ifstream& file, const std::string& path);
	static bool closeFile(std::ifstream& file, const std::string& path);
};