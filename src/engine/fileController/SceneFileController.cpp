#include "SceneFileController.h"
#include <algorithm>

#include <rapidXML\rapidxml.hpp>
#include <rapidXML\rapidxml_utils.hpp>
#include <rapidXML\rapidxml_print.hpp>
#include "MeshFileController.h"
#include "MaterialFileController.h"
#include "FileController.h"
#include "../database/TypeDatabase.h"
#include "../camera/FreeCamera.h"

const std::string SCENE("scene");
const std::string MESHES("meshes");
const std::string MESH("mesh");
const std::string MATERIALS("materials");
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
const std::string CAMERA("camera");
const std::string CAMERAS("cameras");
const std::string TYPE("type");
const std::string ACTIVE("active");
const std::string PROJECTION("projection");
const std::string FOV("FOV");
const std::string FAR_PLANE("farPlane");
const std::string NEAR_PLANE("nearPlane");
const std::string FRUSTUM("frustum");
const std::string STRUE("true");
const std::string SFALSE("false");

void SceneFileController::readSceneDataFile(std::shared_ptr<SceneManager> manager, const std::shared_ptr<WindowSettings> windowSettings, const std::string& file)
{
	rapidxml::file<> xmlFile(file.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *root = doc.first_node();
	
	std::string temp;

	for (rapidxml::xml_node<> *cat = root->first_node(); cat; cat = cat->next_sibling())
	{

		if (cat->name() == MESHES)
		{
			for (rapidxml::xml_node<> *m = cat->first_node(); m; m = m->next_sibling())
			{
				std::string value = m->value();
				manager->meshMap.addItem(MeshFileController::readFile(value));
			}
		}
		else if (cat->name() == MATERIALS)
		{
			for (rapidxml::xml_node<> *m = cat->first_node(); m; m = m->next_sibling())
			{
				std::string value = m->value();
				manager->materialMap.addItem(MaterialFileController::readFile(value));
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
		else if (cat->name() == CAMERAS)
		{
			std::string name;
			CameraType type;
			CameraProjectionType projectionType;
			glm::vec3 position;
		GLboolean active;
			CameraFrustum frustum;

			for (rapidxml::xml_node<> *cams = cat->first_node(); cams; cams = cams->next_sibling())
			{
				for (rapidxml::xml_node<> *props = cams->first_node(); props; props = props->next_sibling())
				{
					if (props->name() == NAME) name = props->value();
					else if (props->name() == TYPE) type = TypeDatabase::getCameraType(props->value());
					else if (props->name() == PROJECTION) projectionType = TypeDatabase::getCameraProjectionType(props->value());
					else if (props->name() == ACTIVE) 
						props->value() == STRUE ? active = true : active = false;
					else if (props->name() == POSITION)
					{
						position = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					}
					else if (props->name() == FRUSTUM)
					{
						frustum.FOV = std::stof(props->first_attribute(FOV.c_str())->value());
						frustum.nearPlane = std::stof(props->first_attribute(NEAR_PLANE.c_str())->value());
						frustum.farPlane = std::stof(props->first_attribute(FAR_PLANE.c_str())->value());
					}
				}
				std::shared_ptr<Camera> cam;
				frustum.viewportWidth = std::make_shared<unsigned short int>(windowSettings->windowResolution.x);
				frustum.viewportHeight = std::make_shared<unsigned short int>(windowSettings->windowResolution.y);

				if (type == CameraType::free) cam = std::make_shared<FreeCamera>(name, frustum, type, projectionType, position);
				// NOTE: Other camera types
				manager->cameraManager.addCamera(cam);
				if (active) manager->cameraManager.activateCamera(name);
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
	rapidxml::xml_node<>* cameras = doc.allocate_node(rapidxml::node_element, CAMERAS.c_str());

	const std::unordered_map<std::string, std::shared_ptr<Mesh>>* mapMesh = &(manager->meshMap.getMap());
	rapidxml::xml_node<>* meshes = doc.allocate_node(rapidxml::node_element, MESHES.c_str());
	for (auto i = mapMesh->cbegin(); i != mapMesh->cend(); ++i)
	{
		rapidxml::xml_node<>* mesh = doc.allocate_node(rapidxml::node_element,MESH.c_str(),(*i).second->getPath().c_str());
		meshes->append_node(mesh);
	}
	root->append_node(meshes);

	const std::unordered_map<std::string, std::shared_ptr<Material>>* mapMaterial = &(manager->materialMap.getMap());
	rapidxml::xml_node<>* materials = doc.allocate_node(rapidxml::node_element, MATERIALS.c_str());
	for (auto i = mapMaterial->cbegin(); i != mapMaterial->cend(); ++i)
	{
		rapidxml::xml_node<>* material = doc.allocate_node(rapidxml::node_element, MATERIAL.c_str(), (*i).second->getPath().c_str());
		materials->append_node(material);
	}
	root->append_node(materials);


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
	
	const std::unordered_map<std::string, std::shared_ptr<Camera>>* cameraMap = &(manager->cameraManager.getMap());
	std::vector<std::string> stringvec2;
	stringvec2.reserve(cameraMap->size() * 6);
	std::vector<std::string> stringvec3;
	stringvec3.reserve(cameraMap->size() * 2);
	std::string valueTemp;
	for (auto i = cameraMap->cbegin(); i != cameraMap->cend(); ++i)
	{
		rapidxml::xml_node<>* camera = doc.allocate_node(rapidxml::node_element, CAMERA.c_str());
		std::shared_ptr<Camera> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		stringvec3.push_back(TypeDatabase::getCameraTypeName(m->getCameraType()));
		rapidxml::xml_node<>* typeSub = doc.allocate_node(rapidxml::node_element, TYPE.c_str(), stringvec3[stringvec3.size() - 1].c_str());
		stringvec3.push_back(TypeDatabase::getCameraProjectionTypeName(m->getCameraProjectionType()));
		rapidxml::xml_node<>* projectionSub = doc.allocate_node(rapidxml::node_element, PROJECTION.c_str(), stringvec3[stringvec3.size() - 1].c_str());
		m->isActive() ? valueTemp = "true" : valueTemp = "false";
		rapidxml::xml_node<>* activeSub = doc.allocate_node(rapidxml::node_element, ACTIVE.c_str(), valueTemp.c_str());

		glm::vec3 pos = m->getPosition();
		rapidxml::xml_node<>* posSub = doc.allocate_node(rapidxml::node_element, POSITION.c_str());
		stringvec2.push_back(std::to_string(pos.x));
		rapidxml::xml_attribute<> *posX = doc.allocate_attribute(X.c_str(), stringvec2[stringvec2.size() - 1].c_str());
		stringvec2.push_back(std::to_string(pos.y));
		rapidxml::xml_attribute<> *posY = doc.allocate_attribute(Y.c_str(), stringvec2[stringvec2.size() - 1].c_str());
		stringvec2.push_back(std::to_string(pos.z));
		rapidxml::xml_attribute<> *posZ = doc.allocate_attribute(Z.c_str(), stringvec2[stringvec2.size() - 1].c_str());
		posSub->append_attribute(posX);
		posSub->append_attribute(posY);
		posSub->append_attribute(posZ);

		rapidxml::xml_node<>* frustumSub = doc.allocate_node(rapidxml::node_element, FRUSTUM.c_str());
		stringvec2.push_back(std::to_string(m->getFrostum().FOV));
		rapidxml::xml_attribute<>* fov = doc.allocate_attribute(FOV.c_str(), stringvec2[stringvec2.size() - 1].c_str());
		stringvec2.push_back(std::to_string(m->getFrostum().nearPlane));
		rapidxml::xml_attribute<>* nearPlane = doc.allocate_attribute(NEAR_PLANE.c_str(), stringvec2[stringvec2.size() - 1].c_str());
		stringvec2.push_back(std::to_string(m->getFrostum().farPlane));
		rapidxml::xml_attribute<>* farPlane = doc.allocate_attribute(FAR_PLANE.c_str(), stringvec2[stringvec2.size() - 1].c_str());
		frustumSub->append_attribute(fov);
		frustumSub->append_attribute(nearPlane);
		frustumSub->append_attribute(farPlane);

		camera->append_node(nameSub);
		camera->append_node(typeSub);
		camera->append_node(projectionSub);
		camera->append_node(activeSub);
		camera->append_node(frustumSub);
		camera->append_node(posSub);
		cameras->append_node(camera);
	}

	root->append_node(cameras);

	doc.append_node(root);

	std::ofstream file;
	if (!FileController::openFile(file, path)) return;
	file << doc;
	FileController::closeFile(file, path);
}
