#include "MeshRenderSystem.h"
#include "../../Components/MeshComponent.h"
#include "../../Components/Transform.h"
#include <glm/gtc/type_ptr.hpp>
#include "../../Core/SceneManager.h"
#include "../../Headers/Global.h"
#include "../../ResourceManager/ShaderManager/ShaderManager.h"

MeshRenderSystem::MeshRenderSystem()
{
	entitiesToProcess = sceneManager->GetEntityByComponent("MeshComponent");
	shaderProgramID = shaderManager->GetShaderProgram();
	matModel_location = glGetUniformLocation(shaderProgramID, "matModel");
	matModelInvTrans_location = glGetUniformLocation(shaderProgramID, "matModelInvTrans");
	objectDiffuseColour_UniLoc = glGetUniformLocation(shaderProgramID, "objectDiffuse");
	objectSpecularColour_Uniloc = glGetUniformLocation(shaderProgramID, "objectSpecular");
	bDontUseLighting_UniLoc = glGetUniformLocation(shaderProgramID, "bDontUseLighting");

	tex00_UniLoc = glGetUniformLocation(shaderProgramID, "texture00");		// uniform sampler2D texture00;
	tex01_UniLoc = glGetUniformLocation(shaderProgramID, "texture01");		// uniform sampler2D texture01;
	tex02_UniLoc = glGetUniformLocation(shaderProgramID, "texture02");		// uniform sampler2D texture02;
	tex03_UniLoc = glGetUniformLocation(shaderProgramID, "texture03");		// uniform sampler2D texture03;
	tex04_UniLoc = glGetUniformLocation(shaderProgramID, "texture04");		// uniform sampler2D texture04;
	tex05_UniLoc = glGetUniformLocation(shaderProgramID, "texture05");		// uniform sampler2D texture05;
	tex06_UniLoc = glGetUniformLocation(shaderProgramID, "texture06");		// uniform sampler2D texture06;
	tex07_UniLoc = glGetUniformLocation(shaderProgramID, "texture07");		// uniform sampler2D texture07;

	texBW_0_UniLoc = glGetUniformLocation(shaderProgramID, "texBlendWeights[0]");	// uniform vec4 texBlendWeights[2];
	texBW_1_UniLoc = glGetUniformLocation(shaderProgramID, "texBlendWeights[1]");	// uniform vec4 texBlendWeights[2];

	skyBoxCubeMap_UniLoc = glGetUniformLocation(shaderProgramID, "skyBox");
	useSkyBoxTexture_UniLoc = glGetUniformLocation(shaderProgramID, "useSkyBox");
	skyboxID = sceneManager->GetSkyBox();
}

void MeshRenderSystem::Process()
{
	glActiveTexture(30 + GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

	//uniform samplerCube textureSkyBox;
	glUniform1i(skyBoxCubeMap_UniLoc, 30);

	//uniform bool useSkyBoxTexture;
	glUniform1f(useSkyBoxTexture_UniLoc, (float)GL_TRUE);

	for (unsigned int i = 0; i<entitiesToProcess->size(); ++i)
	{
		Entity* entity = entitiesToProcess->at(i);
		MeshComponent* meshInfo = static_cast<MeshComponent*>(entity->GetComponent("MeshComponent"));
		Transform* modelTransform = static_cast<Transform*>(entity->GetComponent("Transform"));
		
		//skip this entity if it does not have a transform and a meshrenderer or if it's not currently active
		if (meshInfo == nullptr || modelTransform == nullptr || !entity->isActive || !meshInfo->isActive)
		{
			if (meshInfo == nullptr)
			{
				std::cout << "No mesh component on Entity" << std::endl;
			}
			if (modelTransform == nullptr)
			{
				std::cout << "No transform component on Entity" << std::endl;
			}
			continue;
		}

		for (int texBindIndex = 0; texBindIndex != meshInfo->vecTexture.size(); texBindIndex++)
		{
			// Bind to the the "texBindIndex" texture unit
			glActiveTexture(GL_TEXTURE0 + texBindIndex);			

			glBindTexture(GL_TEXTURE_2D, meshInfo->vecTexture[texBindIndex].texID);

			// Use a switch to pick the texture sampler and weight (strength)
			// BECAUSE the samplers can't be in an array
			switch (texBindIndex)
			{
			case 0:		// uniform sampler2D texture00  AND texBlendWeights[0].x;
				glUniform1i(tex00_UniLoc, texBindIndex);
				break;
			case 1:		// uniform sampler2D texture01  AND texBlendWeights[0].y;
				glUniform1i(tex01_UniLoc, texBindIndex);
				break;
			case 2:
				glUniform1i(tex02_UniLoc, texBindIndex);
				break;
			case 3:
				glUniform1i(tex03_UniLoc, texBindIndex);
				break;
			case 4:		// uniform sampler2D texture04  AND texBlendWeights[1].x;
				glUniform1i(tex04_UniLoc, texBindIndex);
				break;
			case 5:
				glUniform1i(tex05_UniLoc, texBindIndex);
				break;
			case 6:
				glUniform1i(tex06_UniLoc, texBindIndex);
				break;
			case 7:
				glUniform1i(tex07_UniLoc, texBindIndex);
				break;
			}//switch ( texBindIndex )

			// Set the blend weight (strengty)
			blendWeights[texBindIndex] = meshInfo->vecTexture[texBindIndex].texBlendStrength;

		}//for ( int texBindIndex

		// Set the weights (strengths) in the shader
		glUniform4f(texBW_0_UniLoc, blendWeights[0], blendWeights[1], blendWeights[2], blendWeights[3]);
		glUniform4f(texBW_1_UniLoc, blendWeights[4], blendWeights[5], blendWeights[6], blendWeights[7]);

		glUniformMatrix4fv(matModel_location, 1, GL_FALSE, glm::value_ptr(modelTransform->GetMatModel()));
		glUniformMatrix4fv(matModelInvTrans_location, 1, GL_FALSE, glm::value_ptr(modelTransform->GetMatModelInvTrans()));

		glUniform4f(objectDiffuseColour_UniLoc,
			meshInfo->materialDiffuse.r,
			meshInfo->materialDiffuse.g,
			meshInfo->materialDiffuse.b,
			meshInfo->materialDiffuse.a);

		glUniform4f(objectSpecularColour_Uniloc,
			meshInfo->materialSpecular.r,
			meshInfo->materialSpecular.g,
			meshInfo->materialSpecular.b,
			meshInfo->materialSpecular.a);

		if (meshInfo->useVertColour)
		{
			glUniform1f(useVertexColour_UniLoc, (float)GL_TRUE);
		}
		else
		{
			glUniform1f(useVertexColour_UniLoc, (float)GL_FALSE);
		}

		if (meshInfo->useLighting)
		{
			glUniform1f(bDontUseLighting_UniLoc, (float)GL_FALSE);
		}
		else
		{
			glUniform1f(bDontUseLighting_UniLoc, (float)GL_TRUE);
		}

		if (meshInfo->isWireFrame)
		{
			// Yes, draw it wireframe
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_CULL_FACE);	// Discared "back facing" triangles
										//glDisable( GL_DEPTH );		// Enables the KEEPING of the depth information
										//glDisable( GL_DEPTH_TEST );	// When drawing, checked the existing depth
		}
		else
		{
			// No, it's "solid" (or "Filled")
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_CULL_FACE);	// Discared "back facing" triangles
									//glEnable( GL_DEPTH );		// Enables the KEEPING of the depth information
									//glEnable( GL_DEPTH_TEST );	// When drawing, checked the existing depth
		}

		glBindVertexArray(meshInfo->vao_id);

		glDrawElements(GL_TRIANGLES, meshInfo->numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}	
}