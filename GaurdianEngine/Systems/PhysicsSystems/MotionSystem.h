#ifndef _MOTION_SYSTEM_HG
#define _MOTION_SYSTEM_HG

#include "../EntitySystem.h"

//handles physics based motion of entities, so things such as gravity, velocity, acceleration
class MotionSystem : public EntitySystem
{
public:
	MotionSystem();
	~MotionSystem();
	void Process();
private:
	float deltaTime;
	const float maxDeltaTime = 0.1f;
	float currentTime, lastTime;
};

#endif