#ifndef _BOX_COLLIDER_HG
#define _BOX_COLLIDER_HG

#include "Collider.h"
#include <glm/vec3.hpp>

//Not yet implemented
class BoxCollider : public Collider
{
public:
	BoxCollider();
	~BoxCollider();
	glm::vec3 midPointOffset; //an offset from the transform of the object
	glm::vec3 radius; //radius from midpoint for each axis + the midpointoffset;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
};

#endif // !_BOX_COLLIDER_HG
