#include "SceneFileController.h"
#include <algorithm>

#include <rapidXML\rapidxml.hpp>
#include <rapidXML\rapidxml_utils.hpp>
#include <rapidXML\rapidxml_print.hpp>
#include "MeshFileController.h"
#include "MaterialFileController.h"
#include "FileController.h"

const std::string SCENE("scene");
const std::string MESH("mesh");
const std::string MATERIAL("material");
const std::string MODELS("models");
const std::string MODEL("model");
const std::string NAME("name");
const std::string ENTITIES("entities");
const std::string ENTITY("entity");
const std::string POSITION("position");
const std::string ROTATION("rotation");
const std::string SCALE("scale");
const std::string X("x");
const std::string Y("y");
const std::string Z("z");

void SceneFileController::readSceneDataFile(std::shared_ptr<SceneManager> manager, const std::string& file)
{
	rapidxml::file<> xmlFile(file.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *root = doc.first_node();
	
	std::string temp;



	for (rapidxml::xml_node<> *cat = root->first_node(); cat; cat = cat->next_sibling())
	{

		if (cat->name() == MESH)
		{
			std::string value = cat->value();
			value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());
			
			while (true)
			{
				auto pos = value.find(',');

				if (pos == std::string::npos)
				{
					manager->meshMap.addItem(MeshFileController::readFile(value));
					break;
				}
				temp = value.substr(0, pos);
				manager->meshMap.addItem(MeshFileController::readFile(temp));
				value.erase(value.cbegin(), value.cbegin() + pos + 1);
			}
		}
		else if (cat->name() == MATERIAL)
		{
			std::string value = cat->value();
			value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());

			while (true)
			{
				auto pos = value.find(',');

				if (pos == std::string::npos)
				{
					manager->materialMap.addItem(MaterialFileController::readFile(value));
					break;
				}
				temp = value.substr(0, pos);
				manager->materialMap.addItem(MaterialFileController::readFile(temp));
				value.erase(value.cbegin(), value.cbegin() + pos + 1);
			}
		}
		else if (cat->name() == MODELS)
		{
			std::string name;
			std::string meshName;
			std::string materialName;
			for (rapidxml::xml_node<> *models = cat->first_node(); models; models = models->next_sibling())
			{
				for (rapidxml::xml_node<> *props = models->first_node(); props; props = props->next_sibling())
				{
					if (props->name() == NAME) name = props->value();
					if (props->name() == MESH) meshName = props->value();
					if (props->name() == MATERIAL) materialName = props->value();
				}
				manager->modelMap.addItem(std::make_shared<Model>(name, manager->meshMap.getItem(meshName), manager->materialMap.getItem(materialName)));
			}
		}
		else if (cat->name() == ENTITIES)
		{
			std::string name;
			std::string model;
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			for (rapidxml::xml_node<> *entities = cat->first_node(); entities; entities = entities->next_sibling())
			{
				for (rapidxml::xml_node<> *props = entities->first_node(); props; props = props->next_sibling())
				{
					if (props->name() == NAME) name = props->value();
					if (props->name() == MODEL) model = props->value();
					if (props->name() == POSITION)
					{
						position = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					}
					if (props->name() == ROTATION)
					{
						rotation = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					}
					if (props->name() == SCALE)
					{
						scale = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					}
				}
				manager->entityMap.addItem(std::make_shared<Entity>(name, manager->modelMap.getItem(model), position, rotation, scale));
				
			}
		}

	}
}

void SceneFileController::writeSceneDataFile(std::shared_ptr<SceneManager> manager, const std::string & path)
{
	std::string extension = path.substr(path.length() - 3, path.length());

	if (extension != "xml")
	{
		Debug::print(path);
		Debug::print("not a XML File!");
		Debug::print(" ");
		return;
	}

	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, SCENE.c_str());
	rapidxml::xml_node<>* models = doc.allocate_node(rapidxml::node_element, MODELS.c_str());
	rapidxml::xml_node<>* entities = doc.allocate_node(rapidxml::node_element, ENTITIES.c_str());

	std::string value;
	const std::unordered_map<std::string, std::shared_ptr<Mesh>>* mapMesh = &(manager->meshMap.getMap());
	for (auto i = mapMesh->cbegin(); i != mapMesh->cend(); ++i)
	{
		std::shared_ptr<Mesh> mesh = (*i).second;
		value.append(mesh->getPath());
		value.append(",");
	}
	value.erase(value.end() - 1, value.end());
	rapidxml::xml_node<>* mesh = doc.allocate_node(rapidxml::node_element,MESH.c_str(),value.c_str());
	root->append_node(mesh);

	std::string value2;
	const std::unordered_map<std::string, std::shared_ptr<Material>>* mapMaterial = &(manager->materialMap.getMap());
	for (auto i = mapMaterial->cbegin(); i != mapMaterial->cend(); ++i)
	{
		std::shared_ptr<Material> mat = (*i).second;
		value2.append(mat->getPath());
		value2.append(",");
	}
	value2.erase(value2.end() - 1, value2.end());
	rapidxml::xml_node<>* material = doc.allocate_node(rapidxml::node_element, MATERIAL.c_str(), value2.c_str());
	root->append_node(material);


	const std::unordered_map<std::string, std::shared_ptr<Model>>* mapModel = &(manager->modelMap.getMap());
	for (auto i = mapModel->cbegin(); i != mapModel->cend(); ++i)
	{
		rapidxml::xml_node<>* model = doc.allocate_node(rapidxml::node_element, MODEL.c_str());
		std::shared_ptr<Model> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		rapidxml::xml_node<>* meshSub = doc.allocate_node(rapidxml::node_element, MESH.c_str(), m->getMesh()->getName().c_str());
		rapidxml::xml_node<>* matSub = doc.allocate_node(rapidxml::node_element, MATERIAL.c_str(), m->getMaterial()->getName().c_str());

		model->append_node(nameSub);
		model->append_node(meshSub);
		model->append_node(matSub);

		models->append_node(model);
	}
	root->append_node(models);

	std::vector<std::string> stringvec;

	const std::unordered_map<std::string, std::shared_ptr<Entity>>* entityMap = &(manager->entityMap.getMap());
	stringvec.reserve(entityMap->size() * 12);
	for (auto i = entityMap->cbegin(); i != entityMap->cend(); ++i)
	{
		rapidxml::xml_node<>* entity = doc.allocate_node(rapidxml::node_element, ENTITY.c_str());
		std::shared_ptr<Entity> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		rapidxml::xml_node<>* modelSub = doc.allocate_node(rapidxml::node_element, MODEL.c_str(), m->getModel()->getName().c_str());

		glm::vec3 pos = m->getPosition();
		rapidxml::xml_node<>* posSub = doc.allocate_node(rapidxml::node_element, POSITION.c_str());
		stringvec.push_back(std::to_string(pos.x));
		rapidxml::xml_attribute<> *posX = doc.allocate_attribute(X.c_str(), stringvec[stringvec.size() - 1].c_str());
		stringvec.push_back(std::to_string(pos.y));
		rapidxml::xml_attribute<> *posY = doc.allocate_attribute(Y.c_str(), stringvec[stringvec.size() - 1].c_str());
		stringvec.push_back(std::to_string(pos.z));
		rapidxml::xml_attribute<> *posZ = doc.allocate_attribute(Z.c_str(), stringvec[stringvec.size() - 1].c_str());
		posSub->append_attribute(posX);
		posSub->append_attribute(posY);
		posSub->append_attribute(posZ);

		glm::vec3 rot = m->getRotation();
		rapidxml::xml_node<>* rotSub = doc.allocate_node(rapidxml::node_element, ROTATION.c_str());
		stringvec.push_back(std::to_string(rot.x));
		rapidxml::xml_attribute<> *rotX = doc.allocate_attribute(X.c_str(), stringvec[stringvec.size() - 1].c_str());
		stringvec.push_back(std::to_string(rot.y));
		rapidxml::xml_attribute<> *rotY = doc.allocate_attribute(Y.c_str(), stringvec[stringvec.size() - 1].c_str());
		stringvec.push_back(std::to_string(rot.z));
		rapidxml::xml_attribute<> *rotZ = doc.allocate_attribute(Z.c_str(), stringvec[stringvec.size() - 1].c_str());
		rotSub->append_attribute(rotX);
		rotSub->append_attribute(rotY);
		rotSub->append_attribute(rotZ);

		glm::vec3 sc = m->getScale();
		rapidxml::xml_node<>* scSub = doc.allocate_node(rapidxml::node_element, SCALE.c_str());
		stringvec.push_back(std::to_string(sc.x));
		rapidxml::xml_attribute<> *scX = doc.allocate_attribute(X.c_str(), stringvec[stringvec.size() - 1].c_str());
		stringvec.push_back(std::to_string(sc.y));
		rapidxml::xml_attribute<> *scY = doc.allocate_attribute(Y.c_str(), stringvec[stringvec.size() - 1].c_str());
		stringvec.push_back(std::to_string(sc.z));
		rapidxml::xml_attribute<> *scZ = doc.allocate_attribute(Z.c_str(), stringvec[stringvec.size() - 1].c_str());
		scSub->append_attribute(scX);
		scSub->append_attribute(scY);
		scSub->append_attribute(scZ);

		entity->append_node(nameSub);
		entity->append_node(modelSub);
		entity->append_node(posSub);
		entity->append_node(rotSub);
		entity->append_node(scSub);
		entities->append_node(entity);
	}
	root->append_node(entities);
	
	doc.append_node(root);

	std::ofstream file;
	if (!FileController::openFile(file, path)) return;
	file << doc;
	FileController::closeFile(file, path);
}
