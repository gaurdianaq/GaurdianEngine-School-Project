#include "CameraComponent.h"

const std::string CameraComponent::_componentType = "Camera";

CameraComponent::CameraComponent()
{
	componentType = &_componentType;
	cameraEye = glm::vec3(0.0f, 0.0f, 0.0f);
	
	orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	updateAtFromOrientation();
	updateUpFromOrientation();
}

/*
glm::mat4x4 CameraComponent::GetMatView()
{
	matView = glm::lookAt(cameraEye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return matView;
}*/

CameraComponent::~CameraComponent()
{

}

glm::vec3 CameraComponent::getWorldPosition()
{
	return cameraEye + cameraAt;
}

glm::vec3 CameraComponent::getCameraDirection()
{
	updateAtFromOrientation();

	return cameraAt;
}

void CameraComponent::AdjustZ(float amount)
{
	glm::vec3 direction = getWorldPosition() - cameraEye;

	direction = glm::normalize(direction);

	glm::vec3 amountToMove = direction * amount;

	cameraEye += amountToMove;
}

void CameraComponent::AdjustY(float amount)
{
	glm::vec3 amountToMove = glm::normalize(getUpVector()) * amount;

	cameraEye += amountToMove;
}

void CameraComponent::AdjustX(float amount)
{
	glm::vec3 amountToMove = glm::normalize(glm::cross(getCameraDirection(), getUpVector())) * amount;

	cameraEye += amountToMove;
}

void CameraComponent::AdjustPitch(float angleDegrees)
{
	adjCameraOrientation(glm::vec3(angleDegrees, 0.0f, 0.0f), true);

	updateAtFromOrientation();
	updateUpFromOrientation();
}

void CameraComponent::AdjustYaw(float angleDegrees)
{
	adjCameraOrientation(glm::vec3(0.0f, angleDegrees, 0.0f), true);

	updateAtFromOrientation();
	updateUpFromOrientation();
}

void CameraComponent::AdjustRoll(float angleDegrees)
{
	adjCameraOrientation(glm::vec3(0.0f, 0.0f, angleDegrees), true);

	updateAtFromOrientation();
	updateUpFromOrientation();
}

void CameraComponent::setCameraOrientation(glm::vec3 eulerAngles, bool isDegrees)
{
	if (isDegrees)
	{
		eulerAngles = glm::vec3(glm::radians(eulerAngles.x),
			glm::radians(eulerAngles.y),
			glm::radians(eulerAngles.z));
	}

	orientation = glm::quat(glm::vec3(eulerAngles.x, eulerAngles.y, eulerAngles.z));
}

void CameraComponent::adjCameraOrientation(glm::vec3 eulerAngles, bool isDegrees)
{
	if (isDegrees)
	{
		eulerAngles = glm::vec3(glm::radians(eulerAngles.x),
			glm::radians(eulerAngles.y),
			glm::radians(eulerAngles.z));
	}

	glm::quat rotationAdjust(eulerAngles);

	orientation *= rotationAdjust;
}

void CameraComponent::updateUpFromOrientation()
{
	glm::mat4 matRotation = glm::mat4(orientation);

	glm::vec4 upVector = glm::vec4(0, 1.0f, 0, 1.0f);

	glm::vec4 newUp = matRotation * upVector;

	cameraUp = glm::vec3(newUp);
}

void CameraComponent::updateAtFromOrientation()
{
	glm::mat4 matRotation = glm::mat4(orientation);

	glm::vec4 frontOfCamera = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 newAt = matRotation * frontOfCamera;

	cameraAt = glm::vec3(newAt);
}

glm::vec3 CameraComponent::getUpVector()
{
	return cameraUp;
}

void CameraComponent::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("fov");
	writer->Double(fov);
	writer->Key("aspect");
	writer->Double(aspect);
	writer->Key("nearClip");
	writer->Double(nearClip);
	writer->Key("farClip");
	writer->Double(farClip);
	writer->Key("cameraEye");
	writer->StartObject();
	writer->Key("x");
	writer->Double(cameraEye.x);
	writer->Key("y");
	writer->Double(cameraEye.y);
	writer->Key("z");
	writer->Double(cameraEye.z);
	writer->EndObject();
	writer->Key("cameraAt");
	writer->StartObject();
	writer->Key("x");
	writer->Double(cameraAt.x);
	writer->Key("y");
	writer->Double(cameraAt.y);
	writer->Key("z");
	writer->Double(cameraAt.z);
	writer->EndObject();
	writer->EndObject();
}

void CameraComponent::Deserialize(const Value& value)
{

	fov = value["fov"].GetDouble();
	aspect = value["aspect"].GetDouble();
	nearClip = value["nearClip"].GetDouble();
	farClip = value["farClip"].GetDouble();

	cameraEye = glm::vec3(value["cameraEye"]["x"].GetDouble(),
		value["cameraEye"]["y"].GetDouble(),
		value["cameraEye"]["z"].GetDouble());

	glm::vec3 tempCameraAt = glm::vec3(value["cameraAt"]["x"].GetDouble(),
		value["cameraAt"]["y"].GetDouble(),
		value["cameraAt"]["z"].GetDouble());

	setCameraOrientation(tempCameraAt, true);
	updateAtFromOrientation();
	updateUpFromOrientation();
}