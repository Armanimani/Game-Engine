#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "../model/Model.h"
#include "../mesh/Mesh.h"
#include "../material/Material.h"
class SceneManager
{
public:
	SceneManager();

	void addMesh(const std::shared_ptr<Mesh> mesh);
	const std::shared_ptr<Mesh> getMesh(const std::string& name);
	void clearMesh();

	void addMaterial(const std::shared_ptr<Material> mat);
	const std::shared_ptr<Material> getMaterial(const std::string& name);
	void clearMaterial();

	void addModel(const std::shared_ptr<Model> model);
	const std::shared_ptr<Model> getModel(const std::string& name);
	void clearModel();

	void cleanUp();

protected:
	std::unordered_map<std::string, std::shared_ptr<Mesh>> meshMap;
	std::unordered_map<std::string, std::shared_ptr<Material>> materialMap;
	std::unordered_map<std::string, std::shared_ptr<Model>> modelMap;
};
