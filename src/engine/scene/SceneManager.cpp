#include "SceneManager.h"
#include "../debug/Debug.h"

SceneManager::SceneManager()
{
}

void SceneManager::addMesh(const std::shared_ptr<Mesh> mesh)
{
	auto it = meshMap.find(mesh->getName());
	if (it != meshMap.cend())
	{
		Debug::print(mesh->getName());
		Debug::print("Duplicate Mesh!");
		Debug::print(" ");
		return;
	}
	meshMap.insert(std::make_pair(mesh->getName(), mesh));
}

const std::shared_ptr<Mesh> SceneManager::getMesh(const std::string & name)
{
	auto it = meshMap.find(name);

	if (it == meshMap.cend())
	{
		Debug::print(name);
		Debug::print("Mesh not found!");
		Debug::print(" ");
		return nullptr;
	}
	return it->second;
}

void SceneManager::clearMesh()
{
	meshMap.clear();
}

void SceneManager::addMaterial(const std::shared_ptr<Material> mat)
{
	auto it = materialMap.find(mat->getName());
	if (it != materialMap.cend())
	{
		Debug::print(mat->getName());
		Debug::print("Duplicate Material!");
		Debug::print(" ");
		return;
	}
	materialMap.insert(std::make_pair(mat->getName(), mat));
}

const std::shared_ptr<Material> SceneManager::getMaterial(const std::string & name)
{
	auto it = materialMap.find(name);
	if (it == materialMap.end())
	{
		Debug::print(name);
		Debug::print("Material not found");
		Debug::print(" ");
		return nullptr;
	}
	return it->second;
}

void SceneManager::clearMaterial()
{
	materialMap.clear();
}

void SceneManager::addModel(const std::shared_ptr<Model> model)
{
	auto it = modelMap.find(model->getName());

	if (it != modelMap.cend())
	{
		Debug::print(model->getName());
		Debug::print("Model not found!");
		Debug::print(" ");
		return;
	}
	modelMap.insert(std::make_pair(model->getName(), model));
}

const std::shared_ptr<Model> SceneManager::getModel(const std::string & name)
{
	auto it = modelMap.find(name);

	if (it == modelMap.cend())
	{
		Debug::print(name);
		Debug::print("Model not found!");
		Debug::print(" ");
		return nullptr;
	}
	return it->second;
}

void SceneManager::clearModel()
{
	modelMap.clear();
}

void SceneManager::cleanUp()
{
	clearMesh();
	clearMaterial();
	clearModel();

}
