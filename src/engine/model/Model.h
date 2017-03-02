#pragma once
#include <memory>
#include "../material/Material.h"
#include "../mesh/Mesh.h"
#include<string>

class Model
{
public:
	Model(const std::string& name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : name(name), mesh(mesh), material(material) {}

	inline const std::shared_ptr<Mesh> getMesh() { return mesh; }
	inline const std::shared_ptr<Material> getMaterial() { return material; }
	inline const std::string& getName() { return name; }

protected:
	std::string name;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
};