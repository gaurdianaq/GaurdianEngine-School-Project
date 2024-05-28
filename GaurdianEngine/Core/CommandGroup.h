#ifndef _COMMAND_GROUP_HG
#define _COMMAND_GROUP_HG

#include "iCommand.h"

class CommandGroup : iCommand
{
public:
	CommandGroup(bool _isParallel);

	void Update(double deltaTime);

	std::vector<iCommand*> commands;
private:
	bool bIsFinished;
	bool isParallel;
};

#endif