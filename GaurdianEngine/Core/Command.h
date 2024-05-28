#ifndef _ICOMMAND_HG
#define _ICOMMAND_HG

#include "Entity.h"

class Command
{
	virtual void Update(double deltaTime) = 0;
	virtual bool isFinished() = 0;

	virtual ~Command();
};

#endif