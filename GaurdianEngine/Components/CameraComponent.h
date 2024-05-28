#ifndef _CAMERA_COMPONENT_HG
#define _CAMERA_COMPONENT_HG

#include "../Core/Component.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	float fov;
	float aspect;
	float nearClip;
	float farClip;

	glm::vec3 cameraEye;

	void AdjustX(float amount);
	void AdjustY(float amount);
	void AdjustZ(float amount);

	void AdjustYaw(float angleDegrees);
	void AdjustPitch(float angleDegrees);
	void AdjustRoll(float angleDegrees);

	glm::vec3 getWorldPosition();
	glm::vec3 getCameraDirection();
	glm::vec3 getUpVector();

	void setCameraOrientation(glm::vec3 eulerAngles, bool isDegrees);
	void adjCameraOrientation(glm::vec3 eulerAngles, bool isDegrees);

protected:
	glm::vec3 cameraUp;
	glm::vec3 cameraAt;
	glm::quat orientation;

	void updateAtFromOrientation();
	void updateUpFromOrientation();

	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif // !_CAMERA_COMPONENT_HG
