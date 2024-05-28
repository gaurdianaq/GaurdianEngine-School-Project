#ifndef _LIGHT_SYSTEM_HG
#define _LIGHT_SYSTEM_HG

#include "../EntitySystem.h"

//handles processing of lights
class LightSystem : public EntitySystem
{
public:
	LightSystem();
	void Process();
};

#endif