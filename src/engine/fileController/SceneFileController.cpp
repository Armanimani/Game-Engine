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
#include "../camera/OrthoFreeCamera.h"
#include "../camera/OrthoFreeCamera2D.h"
#include "../camera/FPSCamera.h"
#include "../camera/TargetCamera.h"
#include "../camera/ArcBallCamera.h"
#include "../light/Light.h"
#include "../light/AmbientLight.h"
#include "../light/PointLight.h"
#include "../light/DirectionalLight.h"
#include "FontFileController.h"
#include "../texture/ModelTexture.h"

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
const std::string DIRECTION("direction");
const std::string VIEW("view");
const std::string LEFT("left");
const std::string RIGHT("right");
const std::string TOP("top");
const std::string BOTTOM("bottom");
const std::string BACK("back");
const std::string FRONT("front");
const std::string TARGET("target");
const std::string LIGHTS("lights");
const std::string LIGHT("light");
const std::string COLOR("color");
const std::string R("r");
const std::string G("g");
const std::string B("b");
const std::string A("a");
const std::string INTENSITY("intensity");
const std::string DIFFUSE_INTENSITY("diffuseIntensity");
const std::string SPECULAR_INTENSITY("specularIntensity");
const std::string DIFFUSE_COLOR("diffuseColor");
const std::string SPECULAR_COLOR("specularColor");
const std::string EXPONENT("exponent");
const std::string CUTOFF("cutoff");
const std::string SHADOW("shadow");
const std::string ATTENUATION("attenuation");
const std::string HIDDEN("hidden");
const std::string FONTS("fonts");
const std::string FONT("font");
const std::string FOGS("fogs");
const std::string FOG("fog");
const std::string DENSITY("density");
const std::string TEXTURES("textures");
const std::string TEXTURE("texture");
const std::string DIMENSION("dimension");
const std::string WIDTH("width");
const std::string HEIGHT("height");
const std::string PATH("path");
const std::string ID("ID");
const std::string LOCATION("location");

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
		else if (cat->name() == TEXTURES)
		{
			std::string name;
			std::string path;
			GLuint height;
			GLuint width;
			GLuint loc;

			for (rapidxml::xml_node<> *textures = cat->first_node(); textures; textures = textures->next_sibling())
			{
				for (rapidxml::xml_node<> *props = textures->first_node(); props; props = props->next_sibling())
				{
					if (props->name() == NAME) name = props->value();
					if (props->name() == PATH) path = props->value();
					if (props->name() == DIMENSION)
					{
						width = std::stof(props->first_attribute(WIDTH.c_str())->value());
						height = std::stof(props->first_attribute(HEIGHT.c_str())->value());
					}
					if (props->name() == LOCATION) loc = std::stoi(props->value());
				}
				manager->textureMap.addItem(std::make_shared<ModelTexture>(name, path, width, height, loc));
			}
		}
		else if (cat->name() == MATERIALS)
		{
			for (rapidxml::xml_node<> *m = cat->first_node(); m; m = m->next_sibling())
			{
				std::string value = m->value();
				manager->materialMap.addItem(MaterialFileController::readFile(value, manager));
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
			GLboolean hidden = false;
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
					if (props->name() == HIDDEN)
					{
						props->value() == STRUE ? hidden = true : hidden = false;
					}
				}
				std::shared_ptr<Entity> entity = std::make_shared<Entity>(name, manager->modelMap.getItem(model), position, rotation, scale);
				entity->setHidden(hidden);
				manager->entityMap.addItem(entity);
			}
		}
		else if (cat->name() == CAMERAS)
		{
			std::string name;
			CameraType type;
			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 target;
			GLboolean active;
			CameraFrustum frustum;

			for (rapidxml::xml_node<> *cams = cat->first_node(); cams; cams = cams->next_sibling())
			{
				for (rapidxml::xml_node<> *props = cams->first_node(); props; props = props->next_sibling())
				{
					if (props->name() == NAME) name = props->value();
					else if (props->name() == TYPE) type = TypeDatabase::getCameraType(props->value());
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
					else if (props->name() == DIRECTION)
					{
						direction = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					}
					else if (props->name() == VIEW)
					{
						frustum.viewLeft = std::stof(props->first_attribute(LEFT.c_str())->value());
						frustum.viewRight = std::stof(props->first_attribute(RIGHT.c_str())->value());
						frustum.viewTop = std::stof(props->first_attribute(TOP.c_str())->value());
						frustum.viewBottom = std::stof(props->first_attribute(BOTTOM.c_str())->value());
						frustum.viewFront = std::stof(props->first_attribute(FRONT.c_str())->value());
						frustum.viewBack = std::stof(props->first_attribute(BACK.c_str())->value());
					}
					else if (props->name() == TARGET)
					{
						target = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					}
				}
				std::shared_ptr<Camera> cam;
				frustum.viewportWidth = std::make_shared<unsigned short int>(windowSettings->windowResolution.x);
				frustum.viewportHeight = std::make_shared<unsigned short int>(windowSettings->windowResolution.y);

				if (type == CameraType::free)
				{
					cam = std::make_shared<FreeCamera>(name, frustum, type, position, direction);
				}
				else if (type == CameraType::orthoFree)
				{
					cam = std::make_shared<OrthoFreeCamera>(name, frustum, type, position, direction);
				}
				else if (type == CameraType::orthoFree2D)
				{
					cam = std::make_shared<OrthoFreeCamera2D>(name, frustum, type, position, direction);
				}
				else if (type == CameraType::FPS)
				{
					cam = std::make_shared<FPSCamera>(name, frustum, type, position, direction);
				}
				else if (type == CameraType::target)
				{
					cam = std::make_shared<TargetCamera>(name, frustum, type, position, target);
				}
				else if (type == CameraType::arcBall)
				{
					cam = std::make_shared<ArcBallCamera>(name, frustum, type, position, target);
				}
				// NOTE: Other camera types
				manager->cameraManager.addCamera(cam);
				if (active) manager->cameraManager.activateCamera(name);
			}
		}
		else if (cat->name() == LIGHTS)
		{
			std::string name;
			LightType type;
			glm::vec3 position;
			glm::vec4 color;
			glm::vec3 direction;
			GLfloat intensity;
			GLfloat diffuseIntensity;
			GLfloat specularIntensity;
			GLfloat attenuation;
			glm::vec4 diffuseColor;
			glm::vec4 specularColor;
			GLboolean shadow;
			GLfloat exponent;
			GLfloat cutoff;
			for (rapidxml::xml_node<> *lights = cat->first_node(); lights; lights = lights->next_sibling())
			{
				for (rapidxml::xml_node<> *props = lights->first_node(); props; props = props->next_sibling())
				{
					if (props->name() == NAME) name = props->value();
					else if (props->name() == TYPE) type = TypeDatabase::getLightType(props->value());
					else if (props->name() == POSITION)
					{
						position = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					}
					else if (props->name() == COLOR)
					{
						color = glm::vec4(std::stof(props->first_attribute(R.c_str())->value()), std::stof(props->first_attribute(G.c_str())->value()), std::stof(props->first_attribute(B.c_str())->value()), std::stof(props->first_attribute(A.c_str())->value()));
					}
					else if (props->name() == DIFFUSE_COLOR)
					{
						diffuseColor = glm::vec4(std::stof(props->first_attribute(R.c_str())->value()), std::stof(props->first_attribute(G.c_str())->value()), std::stof(props->first_attribute(B.c_str())->value()), std::stof(props->first_attribute(A.c_str())->value()));
					}
					else if (props->name() == SPECULAR_COLOR)
					{
						specularColor = glm::vec4(std::stof(props->first_attribute(R.c_str())->value()), std::stof(props->first_attribute(G.c_str())->value()), std::stof(props->first_attribute(B.c_str())->value()), std::stof(props->first_attribute(A.c_str())->value()));
					}
					else if (props->name() == INTENSITY)
						intensity = std::stof(std::string(props->value()));
					else if (props->name() == DIFFUSE_INTENSITY)
						diffuseIntensity = std::stof(std::string(props->value()));
					else if (props->name() == SPECULAR_INTENSITY)
						specularIntensity = std::stof(std::string(props->value()));
					else if (props->name() == ATTENUATION)
						attenuation = std::stof(std::string(props->value()));
					else if (props->name() == SHADOW)
						props->value() == STRUE ? shadow = true : shadow = false;
					else if (props->name() == DIRECTION)
						direction = glm::vec3(std::stof(props->first_attribute(X.c_str())->value()), std::stof(props->first_attribute(Y.c_str())->value()), std::stof(props->first_attribute(Z.c_str())->value()));
					else if (props->name() == EXPONENT)
						exponent = std::stof(std::string(props->value()));
					else if (props->name() == CUTOFF)
						cutoff = std::stof(std::string(props->value()));
				}

				std::shared_ptr<Light> light;

				if (type == LightType::ambient)
				{
					light = std::make_shared<AmbientLight>(name, position, intensity, color, attenuation);
				}
				else if (type == LightType::point)
				{
					light = std::make_shared<PointLight>(name, position, diffuseColor, specularColor, diffuseIntensity, specularIntensity, attenuation, shadow);
				}
				else if (type == LightType::directional)
				{
					light = std::make_shared<DirectionalLight>(name, direction, diffuseColor, specularColor, diffuseIntensity, specularIntensity, shadow);
				}
				else if (type == LightType::spot)
				{
					light = std::make_shared<SpotLight>(name, position, direction, diffuseColor, specularColor, diffuseIntensity, specularIntensity, attenuation, exponent, cutoff, shadow);
				}

				manager->lightManager.addLight(light);
				//TODO other light types
			}
		}
		else if (cat->name() == FONTS)
		{
			for (rapidxml::xml_node<> *font = cat->first_node(); font; font = font->next_sibling())
			{
				std::string value = font->value();
				manager->fontManager.addFont(FontFileController::readFile(value));
			}
		}
		else if (cat->name() == FOGS) //For now ! need to add support for multiple fogs!
		{
			for (rapidxml::xml_node<> *fog = cat->first_node(); fog; fog = fog->next_sibling())
			{
				std::string name;
				glm::vec4 color;
				GLfloat density;
				for (rapidxml::xml_node<> *props = fog->first_node(); props; props = props->next_sibling())
				{
					if (props->name() == NAME) name = props->value();
					else if (props->name() == COLOR)
					{
						color = glm::vec4(std::stof(props->first_attribute(R.c_str())->value()), std::stof(props->first_attribute(G.c_str())->value()), std::stof(props->first_attribute(B.c_str())->value()), std::stof(props->first_attribute(A.c_str())->value()));
					}
					else if (props->name() == DENSITY) density = std::stof(props->value());
				}
				manager->fogManager.addItem(std::make_shared<Fog>(name, color, density));
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
	rapidxml::xml_node<>* lights = doc.allocate_node(rapidxml::node_element, LIGHTS.c_str());
	rapidxml::xml_node<>* fogs = doc.allocate_node(rapidxml::node_element, FOGS.c_str());

	std::vector<std::shared_ptr<std::string>> temp;

	const std::unordered_map<std::string, std::shared_ptr<Mesh>>* mapMesh = &(manager->meshMap.getMap());
	rapidxml::xml_node<>* meshes = doc.allocate_node(rapidxml::node_element, MESHES.c_str());
	for (auto i = mapMesh->cbegin(); i != mapMesh->cend(); ++i)
	{
		rapidxml::xml_node<>* mesh = doc.allocate_node(rapidxml::node_element,MESH.c_str(),(*i).second->getPath().c_str());
		meshes->append_node(mesh);
	}
	root->append_node(meshes);

	const std::unordered_map<std::string, std::shared_ptr<ModelTexture>>* mapTexture = &(manager->textureMap.getMap());
	rapidxml::xml_node<>* textures = doc.allocate_node(rapidxml::node_element, TEXTURES.c_str());
	for (auto i = mapTexture->cbegin(); i != mapTexture->cend(); ++i)
	{
		rapidxml::xml_node<>* texture = doc.allocate_node(rapidxml::node_element, TEXTURE.c_str());
		std::shared_ptr<ModelTexture> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		rapidxml::xml_node<>* pathSub = doc.allocate_node(rapidxml::node_element, PATH.c_str(), m->getPath().c_str());
		
		rapidxml::xml_node<>* dimensionSub = doc.allocate_node(rapidxml::node_element, DIMENSION.c_str());
		const unsigned int width = static_cast<const unsigned int>(m->getWidth());
		const unsigned int height = static_cast<const unsigned int>(m->getHeight());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(width)));
		rapidxml::xml_attribute<> *widthAt = doc.allocate_attribute(WIDTH.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(width)));
		rapidxml::xml_attribute<> *heightAt = doc.allocate_attribute(HEIGHT.c_str(), temp[temp.size() - 1].get()->c_str());
		dimensionSub->append_attribute(widthAt);
		dimensionSub->append_attribute(heightAt);

		const unsigned int loc = static_cast<const unsigned int>(m->getLocation());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(loc)));
		rapidxml::xml_node<>* IDSub = doc.allocate_node(rapidxml::node_element, LOCATION.c_str(), temp[temp.size() - 1].get()->c_str());
		

		texture->append_node(nameSub);
		texture->append_node(pathSub);
		texture->append_node(dimensionSub);
		texture->append_node(IDSub);

		textures->append_node(texture);
	}
	root->append_node(textures);

	const std::unordered_map<std::string, std::shared_ptr<Material>>* mapMaterial = &(manager->materialMap.getMap());
	rapidxml::xml_node<>* materials = doc.allocate_node(rapidxml::node_element, MATERIALS.c_str());
	for (auto i = mapMaterial->cbegin(); i != mapMaterial->cend(); ++i)
	{
		rapidxml::xml_node<>* material = doc.allocate_node(rapidxml::node_element, MATERIAL.c_str(), (*i).second->getPath().c_str());
		materials->append_node(material);
	}
	root->append_node(materials);

	const std::unordered_map<std::string, std::shared_ptr<Font>>* mapFont = &(manager->fontManager.getMap());
	rapidxml::xml_node<>* fonts = doc.allocate_node(rapidxml::node_element, FONTS.c_str());
	for (auto i = mapFont->cbegin(); i != mapFont->cend(); ++i)
	{
		rapidxml::xml_node<>* font = doc.allocate_node(rapidxml::node_element, FONT.c_str(), (*i).second->getPath().c_str());
		fonts->append_node(font);
	}
	root->append_node(fonts);

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

	const std::unordered_map<std::string, std::shared_ptr<Entity>>* entityMap = &(manager->entityMap.getMap());
	for (auto i = entityMap->cbegin(); i != entityMap->cend(); ++i)
	{
		rapidxml::xml_node<>* entity = doc.allocate_node(rapidxml::node_element, ENTITY.c_str());
		std::shared_ptr<Entity> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		rapidxml::xml_node<>* modelSub = doc.allocate_node(rapidxml::node_element, MODEL.c_str(), m->getModel()->getName().c_str());

		glm::vec3 pos = m->getPosition();
		rapidxml::xml_node<>* posSub = doc.allocate_node(rapidxml::node_element, POSITION.c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.x)));
		rapidxml::xml_attribute<> *posX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.y)));
		rapidxml::xml_attribute<> *posY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.z)));
		rapidxml::xml_attribute<> *posZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
		posSub->append_attribute(posX);
		posSub->append_attribute(posY);
		posSub->append_attribute(posZ);

		glm::vec3 rot = m->getRotation();
		rapidxml::xml_node<>* rotSub = doc.allocate_node(rapidxml::node_element, ROTATION.c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(rot.x)));
		rapidxml::xml_attribute<> *rotX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(rot.y)));
		rapidxml::xml_attribute<> *rotY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(rot.z)));
		rapidxml::xml_attribute<> *rotZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
		rotSub->append_attribute(rotX);
		rotSub->append_attribute(rotY);
		rotSub->append_attribute(rotZ);

		glm::vec3 sc = m->getScale();
		rapidxml::xml_node<>* scSub = doc.allocate_node(rapidxml::node_element, SCALE.c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(sc.x)));
		rapidxml::xml_attribute<> *scX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(sc.y)));
		rapidxml::xml_attribute<> *scY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(sc.z)));
		rapidxml::xml_attribute<> *scZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
		scSub->append_attribute(scX);
		scSub->append_attribute(scY);
		scSub->append_attribute(scZ);

		m->getHidden() ? temp.emplace_back(std::make_shared<std::string>("true")) : temp.emplace_back(std::make_shared<std::string>("false"));
		rapidxml::xml_node<>* hiddenSub = doc.allocate_node(rapidxml::node_element, HIDDEN.c_str(), temp[temp.size() - 1].get()->c_str());

		entity->append_node(nameSub);
		entity->append_node(modelSub);
		entity->append_node(posSub);
		entity->append_node(rotSub);
		entity->append_node(scSub);
		entity->append_node(hiddenSub);
		entities->append_node(entity);
	}
	root->append_node(entities);
	
	const std::unordered_map<std::string, std::shared_ptr<Camera>>* cameraMap = &(manager->cameraManager.getMap());
	for (auto i = cameraMap->cbegin(); i != cameraMap->cend(); ++i)
	{
		rapidxml::xml_node<>* camera = doc.allocate_node(rapidxml::node_element, CAMERA.c_str());
		std::shared_ptr<Camera> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		temp.emplace_back(std::make_shared<std::string>(TypeDatabase::getCameraTypeName(m->getCameraType())));
		rapidxml::xml_node<>* typeSub = doc.allocate_node(rapidxml::node_element, TYPE.c_str(), temp[temp.size() - 1].get()->c_str());
		m->isActive() ? temp.emplace_back(std::make_shared<std::string>("true"))  : temp.emplace_back(std::make_shared<std::string>("false"));
		rapidxml::xml_node<>* activeSub = doc.allocate_node(rapidxml::node_element, ACTIVE.c_str(), temp[temp.size() - 1].get()->c_str());

		glm::vec3 pos = m->getPosition();
		rapidxml::xml_node<>* posSub = doc.allocate_node(rapidxml::node_element, POSITION.c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.x)));
		rapidxml::xml_attribute<> *posX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.y)));
		rapidxml::xml_attribute<> *posY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.z)));
		rapidxml::xml_attribute<> *posZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
		posSub->append_attribute(posX);
		posSub->append_attribute(posY);
		posSub->append_attribute(posZ);

		rapidxml::xml_node<>* frustumSub = doc.allocate_node(rapidxml::node_element, FRUSTUM.c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().FOV)));
		rapidxml::xml_attribute<>* fov = doc.allocate_attribute(FOV.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().nearPlane)));
		rapidxml::xml_attribute<>* nearPlane = doc.allocate_attribute(NEAR_PLANE.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().farPlane)));
		rapidxml::xml_attribute<>* farPlane = doc.allocate_attribute(FAR_PLANE.c_str(), temp[temp.size() - 1].get()->c_str());
		frustumSub->append_attribute(fov);
		frustumSub->append_attribute(nearPlane);
		frustumSub->append_attribute(farPlane);

		camera->append_node(nameSub);
		camera->append_node(typeSub);
		camera->append_node(activeSub);
		camera->append_node(frustumSub);
		camera->append_node(posSub);

		if (m->getCameraType() != CameraType::target && m->getCameraType() != CameraType::arcBall)
		{
			glm::vec3 direction = m->getDirection();
			rapidxml::xml_node<>* dirSub = doc.allocate_node(rapidxml::node_element, DIRECTION.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(direction.x)));
			rapidxml::xml_attribute<> *dirX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(direction.y)));
			rapidxml::xml_attribute<> *dirY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(direction.z)));
			rapidxml::xml_attribute<> *dirZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
			dirSub->append_attribute(dirX);
			dirSub->append_attribute(dirY);
			dirSub->append_attribute(dirZ);

			camera->append_node(dirSub);
		}

		if (m->getCameraType() == CameraType::orthoFree || m->getCameraType() == CameraType::orthoFree2D)
		{
			rapidxml::xml_node<>* viewSub = doc.allocate_node(rapidxml::node_element, VIEW.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().viewLeft)));
			rapidxml::xml_attribute<> *left = doc.allocate_attribute(LEFT.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().viewRight)));
			rapidxml::xml_attribute<> *right = doc.allocate_attribute(RIGHT.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().viewTop)));
			rapidxml::xml_attribute<> *top = doc.allocate_attribute(TOP.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().viewBottom)));
			rapidxml::xml_attribute<> *bottom = doc.allocate_attribute(BOTTOM.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().viewFront)));
			rapidxml::xml_attribute<> *front = doc.allocate_attribute(FRONT.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getFrustum().viewBack)));
			rapidxml::xml_attribute<> *back = doc.allocate_attribute(BACK.c_str(), temp[temp.size() - 1].get()->c_str());

			viewSub->append_attribute(left);
			viewSub->append_attribute(right);
			viewSub->append_attribute(top);
			viewSub->append_attribute(bottom);
			viewSub->append_attribute(front);
			viewSub->append_attribute(back);

			camera->append_node(viewSub);
		}
		if (m->getCameraType() == CameraType::target || m->getCameraType() == CameraType::arcBall)
		{
			std::shared_ptr<TargetCamera> c = std::static_pointer_cast<TargetCamera>(m);
			glm::vec3 target = c->getTarget();
			rapidxml::xml_node<>* targetSub = doc.allocate_node(rapidxml::node_element, TARGET.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(target.x)));
			rapidxml::xml_attribute<> *targetX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(target.y)));
			rapidxml::xml_attribute<> *targetY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(target.z)));
			rapidxml::xml_attribute<> *targetZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
			targetSub->append_attribute(targetX);
			targetSub->append_attribute(targetY);
			targetSub->append_attribute(targetZ);

			camera->append_node(targetSub);

		}
		cameras->append_node(camera);
	}
	root->append_node(cameras);

	const std::unordered_map<std::string, std::shared_ptr<Light>>* lightMap = &(manager->lightManager.getMap());
	for (auto i = lightMap->cbegin(); i != lightMap->cend(); ++i)
	{
		rapidxml::xml_node<>* light = doc.allocate_node(rapidxml::node_element, LIGHT.c_str());
		std::shared_ptr<Light> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		light->append_node(nameSub);

		temp.emplace_back(std::make_shared<std::string>(TypeDatabase::getLightTypeName(m->getType())));
		rapidxml::xml_node<>* typeSub = doc.allocate_node(rapidxml::node_element, TYPE.c_str(), temp[temp.size() - 1].get()->c_str());
		light->append_node(typeSub);

		if (m->getType() != LightType::directional)
		{
			glm::vec3 pos = m->getPosition();
			rapidxml::xml_node<>* posSub = doc.allocate_node(rapidxml::node_element, POSITION.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.x)));
			rapidxml::xml_attribute<> *posX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.y)));
			rapidxml::xml_attribute<> *posY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(pos.z)));
			rapidxml::xml_attribute<> *posZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
			posSub->append_attribute(posX);
			posSub->append_attribute(posY);
			posSub->append_attribute(posZ);
			light->append_node(posSub);
		}

		if (m->getType() != LightType::directional)
		{
			temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getAttenuationFactor())));
			rapidxml::xml_node<>* attenuationSub = doc.allocate_node(rapidxml::node_element, ATTENUATION.c_str(), temp[temp.size() - 1].get()->c_str());
			light->append_node(attenuationSub);
		}

		if (m->getType() == LightType::ambient)
		{
			std::shared_ptr<AmbientLight> c = std::static_pointer_cast<AmbientLight>(m);
			glm::vec4 color = c->getColor();
			rapidxml::xml_node<>* colorSub = doc.allocate_node(rapidxml::node_element, COLOR.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.x)));
			rapidxml::xml_attribute<> *colorR = doc.allocate_attribute(R.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.y)));
			rapidxml::xml_attribute<> *colorG = doc.allocate_attribute(G.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.z)));
			rapidxml::xml_attribute<> *colorB = doc.allocate_attribute(B.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.a)));
			rapidxml::xml_attribute<> *colorA = doc.allocate_attribute(A.c_str(), temp[temp.size() - 1].get()->c_str());
			colorSub->append_attribute(colorR);
			colorSub->append_attribute(colorG);
			colorSub->append_attribute(colorB);
			colorSub->append_attribute(colorA);
			light->append_node(colorSub);
		}

		if (m->getType() == LightType::ambient)
		{
			std::shared_ptr<AmbientLight> c = std::static_pointer_cast<AmbientLight>(m);
			temp.emplace_back(std::make_shared<std::string>(std::to_string(c->getIntensity())));
			rapidxml::xml_node<>* ambientIntensitySub = doc.allocate_node(rapidxml::node_element, INTENSITY.c_str(), temp[temp.size() - 1].get()->c_str());
			light->append_node(ambientIntensitySub);
		}

		if (m->getType() == LightType::directional || m->getType() == LightType::spot)
		{
			std::shared_ptr<DirectionalLight> c = std::static_pointer_cast<DirectionalLight>(m);
			glm::vec3 direction = c->getDirection();
			rapidxml::xml_node<>* directionSub = doc.allocate_node(rapidxml::node_element, DIRECTION.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(direction.x)));
			rapidxml::xml_attribute<> *directionX = doc.allocate_attribute(X.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(direction.y)));
			rapidxml::xml_attribute<> *directionY = doc.allocate_attribute(Y.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(direction.z)));
			rapidxml::xml_attribute<> *directionZ = doc.allocate_attribute(Z.c_str(), temp[temp.size() - 1].get()->c_str());
			directionSub->append_attribute(directionX);
			directionSub->append_attribute(directionY);
			directionSub->append_attribute(directionZ);
			light->append_node(directionSub);
		}

		if (m->getType() == LightType::point || m->getType() == LightType::directional || m->getType() == LightType::spot)
		{
			glm::vec4 color;
			if (m->getType() == LightType::point)
			{
				std::shared_ptr<PointLight> c = std::static_pointer_cast<PointLight>(m);
				color = c->getDiffuseColor();
			}
			else if (m->getType() == LightType::directional)
			{
				std::shared_ptr<DirectionalLight> c = std::static_pointer_cast<DirectionalLight>(m);
				color = c->getDiffuseColor();
			}
			else if (m->getType() == LightType::spot)
			{
				std::shared_ptr<SpotLight> c = std::static_pointer_cast<SpotLight>(m);
				color = c->getDiffuseColor();
			}

			rapidxml::xml_node<>* diffuseColorSub = doc.allocate_node(rapidxml::node_element, DIFFUSE_COLOR.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.x)));
			rapidxml::xml_attribute<> *colorR = doc.allocate_attribute(R.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.y)));
			rapidxml::xml_attribute<> *colorG = doc.allocate_attribute(G.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.z)));
			rapidxml::xml_attribute<> *colorB = doc.allocate_attribute(B.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.a)));
			rapidxml::xml_attribute<> *colorA = doc.allocate_attribute(A.c_str(), temp[temp.size() - 1].get()->c_str());
			diffuseColorSub->append_attribute(colorR);
			diffuseColorSub->append_attribute(colorG);
			diffuseColorSub->append_attribute(colorB);
			diffuseColorSub->append_attribute(colorA);
			light->append_node(diffuseColorSub);
		}

		if (m->getType() == LightType::point || m->getType() == LightType::directional || m->getType() == LightType::spot)
		{
			GLfloat diffuseIntensity;
			if (m->getType() == LightType::point)
			{
				std::shared_ptr<PointLight> c = std::static_pointer_cast<PointLight>(m);
				diffuseIntensity = c->getDiffuseIntensity();
			}
			else if (m->getType() == LightType::directional)
			{
				std::shared_ptr<DirectionalLight> c = std::static_pointer_cast<DirectionalLight>(m);
				diffuseIntensity = c->getDiffuseIntensity();
			}
			else if (m->getType() == LightType::spot)
			{
				std::shared_ptr<SpotLight> c = std::static_pointer_cast<SpotLight>(m);
				diffuseIntensity = c->getDiffuseIntensity();
			}

			temp.emplace_back(std::make_shared<std::string>(std::to_string(diffuseIntensity)));
			rapidxml::xml_node<>* diffuseIntensitySub = doc.allocate_node(rapidxml::node_element, DIFFUSE_INTENSITY.c_str(), temp[temp.size() - 1].get()->c_str());
			light->append_node(diffuseIntensitySub);
		}

		if (m->getType() == LightType::point || m->getType() == LightType::directional || m->getType() == LightType::spot)
		{
			glm::vec4 color;
			if (m->getType() == LightType::point)
			{
				std::shared_ptr<PointLight> c = std::static_pointer_cast<PointLight>(m);
				color = c->getSpecularColor();
			}
			else if (m->getType() == LightType::directional)
			{
				std::shared_ptr<DirectionalLight> c = std::static_pointer_cast<DirectionalLight>(m);
				color = c->getSpecularColor();
			}
			else if (m->getType() == LightType::spot)
			{
				std::shared_ptr<SpotLight> c = std::static_pointer_cast<SpotLight>(m);
				color = c->getSpecularColor();
			}

			rapidxml::xml_node<>* specularColorSub = doc.allocate_node(rapidxml::node_element, SPECULAR_COLOR.c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.x)));
			rapidxml::xml_attribute<> *colorR = doc.allocate_attribute(R.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.y)));
			rapidxml::xml_attribute<> *colorG = doc.allocate_attribute(G.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.z)));
			rapidxml::xml_attribute<> *colorB = doc.allocate_attribute(B.c_str(), temp[temp.size() - 1].get()->c_str());
			temp.emplace_back(std::make_shared<std::string>(std::to_string(color.a)));
			rapidxml::xml_attribute<> *colorA = doc.allocate_attribute(A.c_str(), temp[temp.size() - 1].get()->c_str());
			specularColorSub->append_attribute(colorR);
			specularColorSub->append_attribute(colorG);
			specularColorSub->append_attribute(colorB);
			specularColorSub->append_attribute(colorA);
			light->append_node(specularColorSub);
		}


		if (m->getType() == LightType::point || m->getType() == LightType::directional || m->getType() == LightType::spot)
		{
			GLfloat specularIntensity;
			if (m->getType() == LightType::point)
			{
				std::shared_ptr<PointLight> c = std::static_pointer_cast<PointLight>(m);
				specularIntensity = c->getSpecularIntensity();
			}
			else if (m->getType() == LightType::directional)
			{
				std::shared_ptr<DirectionalLight> c = std::static_pointer_cast<DirectionalLight>(m);
				specularIntensity = c->getSpecularIntensity();
			}
			else if (m->getType() == LightType::spot)
			{
				std::shared_ptr<SpotLight> c = std::static_pointer_cast<SpotLight>(m);
				specularIntensity = c->getSpecularIntensity();
			}

			temp.emplace_back(std::make_shared<std::string>(std::to_string(specularIntensity)));
			rapidxml::xml_node<>* specularIntensitySub = doc.allocate_node(rapidxml::node_element, SPECULAR_INTENSITY.c_str(), temp[temp.size() - 1].get()->c_str());
			light->append_node(specularIntensitySub);
		}

		if (m->getType() == LightType::spot)
		{
			std::shared_ptr<SpotLight> c = std::static_pointer_cast<SpotLight>(m);
			temp.emplace_back(std::make_shared<std::string>(std::to_string(c->getExponent())));
			rapidxml::xml_node<>* exponentSub = doc.allocate_node(rapidxml::node_element, EXPONENT.c_str(), temp[temp.size() - 1].get()->c_str());
			light->append_node(exponentSub);

			temp.emplace_back(std::make_shared<std::string>(std::to_string(c->getCutoff())));
			rapidxml::xml_node<>* cutoffSub = doc.allocate_node(rapidxml::node_element, CUTOFF.c_str(), temp[temp.size() - 1].get()->c_str());
			light->append_node(cutoffSub);
		}

		if (m->getType() == LightType::point || m->getType() == LightType::directional || m->getType() == LightType::spot)
		{
			GLboolean shadow;
			if (m->getType() == LightType::point)
			{
				std::shared_ptr<PointLight> c = std::static_pointer_cast<PointLight>(m);
				shadow = c->getShadow();
			}
			else if (m->getType() == LightType::directional)
			{
				std::shared_ptr<DirectionalLight> c = std::static_pointer_cast<DirectionalLight>(m);
				shadow = c->getShadow();
			}
			else if (m->getType() == LightType::spot)
			{
				std::shared_ptr<SpotLight> c = std::static_pointer_cast<SpotLight>(m);
				shadow = c->getShadow();
			}

			shadow ? temp.emplace_back(std::make_shared<std::string>("true")) : temp.emplace_back(std::make_shared<std::string>("false"));
			rapidxml::xml_node<>* shadowSub = doc.allocate_node(rapidxml::node_element, SHADOW.c_str(), temp[temp.size() - 1].get()->c_str());
			light->append_node(shadowSub);
		}

		lights->append_node(light);
	}
	root->append_node(lights);

	const std::unordered_map<std::string, std::shared_ptr<Fog>>* fogMap = &(manager->fogManager.getMap());
	for (auto i = fogMap->cbegin(); i != fogMap->cend(); ++i)
	{
		rapidxml::xml_node<>* fog = doc.allocate_node(rapidxml::node_element, FOG.c_str());
		std::shared_ptr<Fog> m = (*i).second;
		rapidxml::xml_node<>* nameSub = doc.allocate_node(rapidxml::node_element, NAME.c_str(), m->getName().c_str());
		fog->append_node(nameSub);

		glm::vec4 color = m->getColor();
		rapidxml::xml_node<>* colorSub = doc.allocate_node(rapidxml::node_element, COLOR.c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(color.x)));
		rapidxml::xml_attribute<> *colorR = doc.allocate_attribute(R.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(color.y)));
		rapidxml::xml_attribute<> *colorG = doc.allocate_attribute(G.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(color.z)));
		rapidxml::xml_attribute<> *colorB = doc.allocate_attribute(B.c_str(), temp[temp.size() - 1].get()->c_str());
		temp.emplace_back(std::make_shared<std::string>(std::to_string(color.a)));
		rapidxml::xml_attribute<> *colorA = doc.allocate_attribute(A.c_str(), temp[temp.size() - 1].get()->c_str());
		colorSub->append_attribute(colorR);
		colorSub->append_attribute(colorG);
		colorSub->append_attribute(colorB);
		colorSub->append_attribute(colorA);
		fog->append_node(colorSub);


		temp.emplace_back(std::make_shared<std::string>(std::to_string(m->getDensity())));
		rapidxml::xml_node<>* densitySub = doc.allocate_node(rapidxml::node_element, DENSITY.c_str(), temp[temp.size() - 1].get()->c_str());
		fog->append_node(densitySub);

		fogs->append_node(fog);
	}

	root->append_node(fogs);

	doc.append_node(root);
	std::ofstream file;
	if (!FileController::openFile(file, path)) return;
	file << doc;
	FileController::closeFile(file, path);
}
