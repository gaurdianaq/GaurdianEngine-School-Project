#ifndef _MESH_RENDERER_HG
#define _MESH_RENDERER_HG

#include "../Core/Component.h"
#include <string>
#include <vector>
#include <glm/vec4.hpp>

struct texInfo
{
	unsigned int texID;
	float texBlendStrength;
};

class MeshComponent : public Component
{
public:
	MeshComponent();
	~MeshComponent();

	std::string meshName;
	unsigned int vao_id;
	unsigned int numIndices;
	glm::vec4 materialDiffuse;
	glm::vec4 materialSpecular;
	bool useVertColour;
	bool useLighting; //would eventually like to replace this with a material system which can load individual shaders (some affected by lighting and some not)
	bool isWireFrame;
	std::vector<texInfo> vecTexture;
protected:
	std::vector<std::string> textureNames; //the names of the textures
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif // !_MESH_RENDERER_HG
