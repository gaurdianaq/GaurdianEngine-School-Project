#ifndef _MESH_HG
#define _MESH_HG

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec2.hpp>
#include <vector>
#include "../Resource.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normalPosition;
	glm::vec3 colour;
	glm::vec2 uv;
};

class Mesh : public Resource
{
public:
	Mesh(std::string _filePath, std::string _friendlyName);
	Mesh();
	unsigned int vao_id;
	unsigned int vbo_id;
	unsigned int ebo_id;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _resourceType;
};

#endif // !_MESH_HG
