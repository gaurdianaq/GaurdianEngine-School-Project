#include "MeshInit.h"
#include "../../Components/MeshComponent.h"

void MeshInit::Process(Entity* entity)
{
	MeshComponent* meshComponent = entity->GetComponent<MeshComponent>();
	Mesh* mesh = resourceManager.getMesh(meshComponent->meshName); //should already be there from constructor
	if (meshComponent == nullptr)
	{
		std::cout << "No mesh component attached to entity. Skipping." << std::endl;
		return;
	}

	meshComponent->vao_id = mesh->vao_id;
	meshComponent->numIndices = mesh->indices.size();
}