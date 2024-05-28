#ifndef _SPHERE_COLLIDER_HG
#define _SPHERE_COLLIDER_HG

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	~SphereCollider();
	float radius;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
};

#endif // !_SPHERE_COLLIDER_HG
