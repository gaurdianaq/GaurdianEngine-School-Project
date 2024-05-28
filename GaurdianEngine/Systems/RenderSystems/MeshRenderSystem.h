#ifndef _MODEL_RENDER_SERVICE_HG
#define _MODEL_RENDER_SERVICE_HG

#include "../EntitySystem.h"
#include "../../Components/CameraComponent.h"

//stores all the uniform locations related to rendering meshes and makes the appropriate opengl calls
class MeshRenderSystem : public EntitySystem
{
public:
	MeshRenderSystem();
	void Process();
private:
	int skyboxID;
	int matModel_location;
	int matModelInvTrans_location;
	int useVertexColour_UniLoc;
	int bDontUseLighting_UniLoc;
	int objectDiffuseColour_UniLoc;
	int objectSpecularColour_Uniloc;
	int tex00_UniLoc;
	int tex01_UniLoc;
	int tex02_UniLoc;
	int tex03_UniLoc;
	int tex04_UniLoc;
	int tex05_UniLoc;
	int tex06_UniLoc;
	int tex07_UniLoc;

	int skyBoxCubeMap_UniLoc;
	int useSkyBoxTexture_UniLoc;

	int blendWeights[8];

	int texBW_0_UniLoc;
	int texBW_1_UniLoc;
	unsigned int shaderProgramID;
};

#endif // !_MODEL_RENDER_SERVICE_HG
