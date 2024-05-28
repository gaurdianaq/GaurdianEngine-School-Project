#ifndef _RIGID_BODY_HG
#define _RIGID_BODY_HG

#include "../Core/Component.h"

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();
	float mass;
	float inverseMass;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif // !_RIGID_BODY_HG
