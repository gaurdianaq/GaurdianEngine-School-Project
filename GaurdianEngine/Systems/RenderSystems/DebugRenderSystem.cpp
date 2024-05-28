#include "DebugRenderSystem.h"
#include "../../Components/DebugRenderComponent.h"
#include "../../Components/Transform.h"
#include <glm/gtc/type_ptr.hpp>
#include "../../Core/SceneManager.h"
#include "../../Headers/Global.h"
#include "../../ResourceManager/ShaderManager/ShaderManager.h"

DebugRenderSystem::DebugRenderSystem()
{
	entitiesToProcess = sceneManager->GetEntityByComponent("DebugRender");
	shaderProgramID = shaderManager->GetShaderProgram();
	matModel_location = glGetUniformLocation(shaderProgramID, "matModel");
	matModelInvTrans_location = glGetUniformLocation(shaderProgramID, "matModelInvTrans");
	objectDiffuseColour_UniLoc = glGetUniformLocation(shaderProgramID, "objectDiffuse");
	bDontUseLighting_UniLoc = glGetUniformLocation(shaderProgramID, "bDontUseLighting");
}

void DebugRenderSystem::Process()
{
	for (unsigned int i = 0; i < entitiesToProcess->size(); ++i)
	{
		Entity* entity = entitiesToProcess->at(i);
		DebugRenderComponent* debugShape = static_cast<DebugRenderComponent*>(entity->GetComponent("DebugRender"));
		Transform* modelTransform = static_cast<Transform*>(entity->GetComponent("Transform"));

		//skip this entity if it does not have a transform and a meshrenderer or if it's not currently active
		if (debugShape == nullptr || modelTransform == nullptr || !entity->isActive || !debugShape->isActive)
		{
			if (debugShape == nullptr)
			{
				std::cout << "No mesh component on Entity" << std::endl;
			}
			if (modelTransform == nullptr)
			{
				std::cout << "No transform component on Entity" << std::endl;
			}
			continue;
		}

		glm::mat4x4 matModel = glm::mat4(1.0f) * glm::translate(glm::mat4(1.0f), modelTransform->position + debugShape->offset);
		matModel = matModel * glm::mat4(modelTransform->orientation);
		glm::mat4x4 matModelInvTrans = glm::inverse(glm::transpose(matModel));
		matModel = matModel	* glm::scale(glm::mat4(1.0f), modelTransform->scale * debugShape->size);

		glUniformMatrix4fv(matModel_location, 1, GL_FALSE, glm::value_ptr(matModel));
		glUniformMatrix4fv(matModelInvTrans_location, 1, GL_FALSE, glm::value_ptr(matModelInvTrans));

		glUniform4f(objectDiffuseColour_UniLoc,
			debugShape->colour.r,
			debugShape->colour.g,
			debugShape->colour.b,
			debugShape->colour.a);

		glUniform1f(useVertexColour_UniLoc, (float)GL_FALSE);

		glUniform1f(bDontUseLighting_UniLoc, (float)GL_TRUE);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);

		glBindVertexArray(debugShape->vao_id);

		glDrawElements(GL_TRIANGLES, debugShape->numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}