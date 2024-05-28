#ifndef _ACCELERATION_HG
#define _ACCELERATION_HG

#include "../Core/Component.h"
#include <glm/vec3.hpp>

class Acceleration : public Component
{
public:
	glm::vec3 minAcceleration;
	glm::vec3 maxAcceleration;

	glm::vec3 currentAcceleration;
	Acceleration();
	~Acceleration();
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif // !_ACCELERATION_HG
