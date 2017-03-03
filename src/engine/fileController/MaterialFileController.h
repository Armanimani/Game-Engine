#pragma once
#include "../material/Material.h"
#include <memory>

class MaterialFileController
{
public:
	static std::shared_ptr<Material> readFile(const std::string& path);
	static void writeFile(const std::string& path, const std::shared_ptr<Material> mat);
	
};