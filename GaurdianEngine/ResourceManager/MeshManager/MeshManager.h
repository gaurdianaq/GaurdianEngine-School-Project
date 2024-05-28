#ifndef _MESH_MANAGER_HG
#define _MESH_MANAGER_HG

#include <unordered_map>
#include <string>
#include "../iResourceManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Mesh.h"

//handles loading and unloading of mesh resources
//uses assimp to handle loading meshes from file
class MeshManager : public iResourceManager
{
public:
	static MeshManager* Instance();
	~MeshManager();
	bool LoadResource(Resource* resource);
	void Init();
private:
	MeshManager();
	static MeshManager* instance;
	unsigned int program;
	int vpos_location;
	int vcol_location;
	int vnorm_location;
	int vuv_location;
	void loadMeshIntoGPU(std::string modelName);
	void unloadModel(std::string meshName);
	Assimp::Importer import;
};

#define meshManager MeshManager::Instance()

#endif // !_MESH_MANAGER_HG
