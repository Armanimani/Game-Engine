#pragma once
#include "../material/Material.h"
#include <memory>
#include "../scene/SceneManager.h"

class MaterialFileController
{
public:
	static std::shared_ptr<Material> readFile(const std::string& path, const std::shared_ptr<SceneManager> manager);
	static void writeFile(const std::string& path, const std::shared_ptr<Material> mat);
	
};