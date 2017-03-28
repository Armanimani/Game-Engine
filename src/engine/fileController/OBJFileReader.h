#pragma once
#include "FileController.h"
#include "../mesh/Mesh.h"

class OBJFileReader
{
public:
	static std::shared_ptr<Mesh> readOBJFile(const std::string& path,  std::istream &file);
};