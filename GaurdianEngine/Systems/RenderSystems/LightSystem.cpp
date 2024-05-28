#include "../../Headers/Global.h"
#include "LightSystem.h"
#include "../../Components/Light.h"
#include "../../Components/Transform.h"
#include "../../Core/SceneManager.h"
#include "../../ResourceManager/ShaderManager/ShaderManager.h"

//sets all the uniform locations for each light
LightSystem::LightSystem()
{
	entitiesToProcess = sceneManager->GetEntityByComponent("Light");
	unsigned int counter = 0;
	int shaderProgram = shaderManager->GetShaderProgram();
	for (unsigned int i = 0; i < entitiesToProcess->size(); ++i)
	{
		Light* light = static_cast<Light*>(entitiesToProcess->at(i)->GetComponent("Light"));
		Transform* transform = static_cast<Transform*>(entitiesToProcess->at(i)->GetComponent("Transform"));
		light->diffuse_UniLoc = glGetUniformLocation(shaderProgram, ("theLights[" + std::to_string(counter) + "].diffuse").c_str());
		light->atten_UniLoc = glGetUniformLocation(shaderProgram, ("theLights[" + std::to_string(counter) + "].atten").c_str());
		light->position_UniLoc = glGetUniformLocation(shaderProgram, ("theLights[" + std::to_string(counter) + "].position").c_str());
		light->direction_UniLoc = glGetUniformLocation(shaderProgram, ("theLights[" + std::to_string(counter) + "].direction").c_str());
		light->param1_UniLoc = glGetUniformLocation(shaderProgram, ("theLights[" + std::to_string(counter) + "].param1").c_str());
		light->param2_UniLoc = glGetUniformLocation(shaderProgram, ("theLights[" + std::to_string(counter) + "].param2").c_str());
		++counter;
	}
}

void LightSystem::Process()
{
	
	for (unsigned int i = 0; i<entitiesToProcess->size(); ++i)
	{
		Entity* entity = entitiesToProcess->at(i);
		Light* light = static_cast<Light*>(entity->GetComponent("Light"));
		Transform* transform = static_cast<Transform*>(entity->GetComponent("Transform"));
		if (!entity->isActive || !light->isActive)
		{
			continue;
		}
		glUniform4f(light->position_UniLoc,
			transform->position.x, transform->position.y, transform->position.z, 1.0f);
		glUniform4f(light->diffuse_UniLoc,
			light->diffuse.x, light->diffuse.y, light->diffuse.z, 1.0f);
		glUniform4f(light->atten_UniLoc,
			light->atten.x, light->atten.y, light->atten.z, light->atten.w);
		glUniform4f(light->param2_UniLoc, light->param2.x, 0.0f, 0.0f, 0.0f);	// Turns it "on")
		glUniform4f(light->direction_UniLoc, transform->orientation.x, transform->orientation.y, transform->orientation.z, 1.0f);
		glUniform4f(light->param1_UniLoc, light->param1.x, light->param1.y, light->param1.z, light->param1.w);
		
	}
	
}