#pragma once
#include <memory>
#include "../material/Material.h"
#include "../mesh/Mesh.h"

class Model
{
public:
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : mesh(mesh), material(material) {}

	inline const std::shared_ptr<Mesh> getMesh() { return mesh; }
	inline const std::shared_ptr<Material> getMaterial() { return material; }

protected:

	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
};