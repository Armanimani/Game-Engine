#pragma once
#include <memory>
#include "../mesh/Mesh.h"

class MeshFileController
{
public:
	static std::shared_ptr<Mesh> readFile(const std::string& path);
};