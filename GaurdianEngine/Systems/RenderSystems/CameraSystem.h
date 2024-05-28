#ifndef _CAMERA_SYSTEM_HG
#define _CAMERA_SYSTEM_HG

#include "../../Core/System.h"
#include "../../Components/Transform.h"
#include "../../Components/CameraComponent.h"

class CameraSystem : public System
{
public:
	CameraSystem();
	~CameraSystem();
	void Process();
private:
	Transform* currentCameraTransform;
	CameraComponent* currentCameraComponent;

	glm::mat4x4 matProjection;
	glm::mat4x4 matView;

	int matView_location;
	int matProj_location;
	int eye_location;
	unsigned int shaderProgramID;
};

#endif