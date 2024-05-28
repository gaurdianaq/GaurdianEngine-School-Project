#ifndef _SCENE_MANAGER
#define _SCENE_MANAGER

#include "Scene.h"
#include "../Serialization/Serializer.h"
#include <glm/vec3.hpp>

//used to manage scenes and access scene data
class SceneManager
{
public:
	void AddResourceToScene(std::string resourceType, std::string resourceName, std::string resourceFilePath);
	void AddResourceToScene(Resource* resource); //takes a pre-built resource and adds it to the scene
	void Instantiate(Entity* entity); //adds an entity to the scene
	void Destroy(Entity* entity); //removes an entity from the scene and destroys it
	int GetSkyBox();
	Entity* GetEntityByName(std::string entityName);
	std::vector<Entity*>* GetEntityByComponent(std::string componentType);
	Resource* GetResource(std::string resourceType, std::string resourceName);
	std::unordered_map<std::string, Resource*> GetResourcesByType(std::string resourceType);
	void SetActiveCamera(Entity* entity); //temp measure till I get proper implementation
	Entity* GetActiveCamera(); //will also be nuking this for something better
	void LoadScene(const char* filePath);
	void SaveScene(const char* filePath);
	void SaveScene(); //saves the scene to whatever the scene filepath is (defaultScene.json by default)
	glm::vec3 GetSceneColour(); //returns the background rendering colour for the scene
	static SceneManager* Instance();
private:
	Scene* activeScene;
	SceneManager();
	Serializer serializer;
	Deserializer deserializer;
	static SceneManager* instance;
};

#define sceneManager SceneManager::Instance()

#endif // !_SCENE_MANAGER
