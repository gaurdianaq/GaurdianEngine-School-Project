#ifndef _DEBUG_RENDER_SYSTEM_HG
#define _DEBUG_RENDER_SYSTEM_HG
#include "../EntitySystem.h"

class DebugRenderSystem : public EntitySystem
{
public:
	DebugRenderSystem();
	void Process();
private:
	int matModel_location;
	int matModelInvTrans_location;
	int useVertexColour_UniLoc;
	int bDontUseLighting_UniLoc; //use lighting will always be set to false for debug objects
	int objectDiffuseColour_UniLoc; //only has diffuse colour because it will never use lighting
	unsigned int shaderProgramID;
};

#endif