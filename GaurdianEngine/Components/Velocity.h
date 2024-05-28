#ifndef _VELOCITY_HG
#define _VELOCITY_HG

#include "../Core/Component.h"
#include <glm/vec3.hpp>

class Velocity : public Component
{
public:
	Velocity();
	~Velocity();
	glm::vec3 minVelocity;
	glm::vec3 maxVelocity;

	glm::vec3 currentVelocity;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif // !_VELOCITY_HG
