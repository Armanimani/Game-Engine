#include "SceneFileController.h"
#include <algorithm>

#include <rapidXML\rapidxml.hpp>
#include <rapidXML\rapidxml_utils.hpp>
#include "MeshFileController.h"
#include "MaterialFileController.h"

const std::string MESH("mesh");
const std::string MATERIAL("material");
const std::string MODELS("models");
const std::string MODEL("model");
const std::string NAME("name");
const std::string ENTITIES("entities");
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

void SceneFileController::writeSceneDataFile(std::shared_ptr<SceneManager> manager, const std::string & file)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_declaration);

	
	rapidxml::xml_node<>* material = doc.allocate_node(rapidxml::node_declaration);
	rapidxml::xml_node<>* models = doc.allocate_node(rapidxml::node_declaration);
	rapidxml::xml_node<>* entities = doc.allocate_node(rapidxml::node_declaration);


	std::string value;
	for (std::size_t i = 0; i != manager->meshMap.getMap().size(); ++i)
	{

	}
	rapidxml::xml_node<>* mesh = doc.allocate_node(rapidxml::node_element,MESH.c_str(),value.c_str());
}
