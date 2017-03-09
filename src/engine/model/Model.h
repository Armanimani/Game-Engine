#pragma once
#include <memory>
#include "../material/Material.h"
#include "../mesh/Mesh.h"

class Model
{
public:
	Model(const std::string& name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : name(name), mesh(mesh), material(material) {}

	inline const std::shared_ptr<Mesh> getMesh() { return mesh; }
	inline void setMesh(std::shared_ptr<Mesh> newMesh) { mesh = newMesh; }
	inline const std::shared_ptr<Material> getMaterial() { return material; }
	inline void setMaterial(std::shared_ptr<Material> newMaterial) { material = newMaterial; }
	inline const std::string& getName() { return name; }

protected:
	std::string name;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
};