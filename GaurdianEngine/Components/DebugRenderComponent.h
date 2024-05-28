#ifndef _DEBUG_RENDER_COMPONENT
#define _DEBUG_RENDER_COMPONENT

#include "../Core/Component.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

enum class DebugShape { Sphere, Box, Unknown };

class DebugRenderComponent : public Component
{
public:
	DebugRenderComponent();
	DebugRenderComponent(DebugShape _shape, glm::vec3 _size, glm::vec3 _offset, glm::vec4 _colour);
	~DebugRenderComponent();
	DebugShape shape;
	glm::vec3 size; //will be a seperate multiplier from transforms scale, so when calculating the matmodel this size will be multiplied onto the scale
	glm::vec4 colour;
	glm::vec3 offset; //offset from the transforms origin
	int vao_id;
	int numIndices;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif