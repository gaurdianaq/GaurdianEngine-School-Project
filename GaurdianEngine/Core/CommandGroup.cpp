#include "CommandGroup.h"

CommandGroup::CommandGroup(bool _isParallel)
{
	isParallel = _isParallel;
	bIsFinished = false;
}

void CommandGroup::Update(double deltaTime)
{

}

