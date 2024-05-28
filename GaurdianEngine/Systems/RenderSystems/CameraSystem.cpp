#include "CameraSystem.h"
#include <glm/gtc/type_ptr.hpp>
#include "../../Headers/Global.h"
#include "../../ResourceManager/ShaderManager/ShaderManager.h"
#include "../../Core/SceneManager.h"



CameraSystem::CameraSystem()
{
	Entity* pActiveCamera = sceneManager->GetActiveCamera();
	shaderProgramID = shaderManager->GetShaderProgram();
	matView = glm::mat4(1.0f);
	matProjection = glm::mat4(1.0f);
	matView_location = glGetUniformLocation(shaderProgramID, "matView");
	matProj_location = glGetUniformLocation(shaderProgramID, "matProj");
	eye_location = glGetUniformLocation(shaderProgramID, "eyeLocation");
	currentCameraComponent = static_cast<CameraComponent*>(pActiveCamera->GetComponent("Camera"));
	currentCameraTransform = static_cast<Transform*>(pActiveCamera->GetComponent("Transform"));
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::Process()
{
	matView = glm::lookAt(currentCameraComponent->cameraEye, currentCameraComponent->getWorldPosition(), currentCameraComponent->getUpVector());
	matProjection = glm::perspective(currentCameraComponent->fov, currentCameraComponent->aspect, currentCameraComponent->nearClip, currentCameraComponent->farClip);
	glUseProgram(shaderProgramID);

	glUniform3f(eye_location, currentCameraComponent->cameraEye.x, currentCameraComponent->cameraEye.y, currentCameraComponent->cameraEye.z);

	glUniformMatrix4fv(matView_location, 1, GL_FALSE, glm::value_ptr(matView));
	glUniformMatrix4fv(matProj_location, 1, GL_FALSE, glm::value_ptr(matProjection));
	
}