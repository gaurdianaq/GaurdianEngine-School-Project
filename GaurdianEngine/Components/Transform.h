#ifndef _TRANSFORM_HG
#define _TRANSFORM_HG

#include "../Core/Component.h"
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

class Transform : public Component
{
public:
	~Transform();
	Transform();
	Transform(glm::vec3 _position, glm::vec3 _rotation, bool isDegrees, glm::vec3 _scale);
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scale;
	void setOrientation(glm::vec3 rotation, bool isDegrees);
	void adjustOrientation(glm::vec3 rotationAdjust, bool isDegrees);
	glm::mat4x4 GetMatModel();
	glm::mat4 GetMatModelInvTrans();
private:
	glm::mat4 matModel;
	glm::mat4 matModelInvTrans;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif // !_TRANSFORM_HG