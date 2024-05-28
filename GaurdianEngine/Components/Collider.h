#ifndef _COLLIDER_HG
#define _COLLIDER_HG

#include "../Core/Component.h"

enum class ColliderType { Sphere, Box };

//base collider type (since we need to check against collisions between different collider types, it made sense to have a base collider type
class Collider : public Component
{
public:
	ColliderType colliderType;
	bool collided; //will prevent another collision event from being spawned till the first has been consumed;
	Collider();
	~Collider();
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer) = 0;
	void Deserialize(const Value& value) = 0;
	const static std::string _componentType;
};

#endif // !_COLLIDER_HG
