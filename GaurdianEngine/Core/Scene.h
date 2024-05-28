#ifndef _SCENE_HG
#define _SCENE_HG

#include <vector>
#include <string>
#include "Entity.h"
#include "../ResourceManager/Resource.h"
#include <glm/vec3.hpp>

class Scene : public ISerializeable, public IDeserializeable
{
	friend class SceneManager; //Ensures that scene data can only be accessed via the sceneManager;
private:
	Scene(std::string _sceneName);
	std::string fileName;
	glm::vec3 backgroundColour;
	Entity* mainCamera; //will house the main camera, must contain a camera component
	std::string sceneName;
	void AddResourceToScene(Resource* resource);
	void Instantiate(Entity* entity);
	//Not sure if I need these remove object from scene functions when I have Destroy
	//void RemoveObjectFromScene(std::string objectName);
	//void RemoveObjectFromScene(Entity* entity);
	///////
	int skyBoxID;
	std::unordered_map<std::string, std::unordered_map<std::string, Resource*>> pSceneResources; //key is resource type, and resource name
	std::unordered_map<std::string, Entity*> pEntitiesByName; //For referencing a specific object by it's name
	std::unordered_map<std::string, std::vector<Entity*>> pEntitiesByComponent; //Allows for reference of gameobject by component, where the key will return a list of all gameobjects with that component
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(Document& document);
};

#endif // !_SCENE_HG
