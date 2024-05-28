#include "BuilderSystem.h"
#include "../Builders/BallBuilder.h"

BuilderSystem::BuilderSystem()
{
	builders["Ball"] = new BallBuilder();
}

void BuilderSystem::Process()
{
	ProcessMessages();
}

void BuilderSystem::ProcessMessages()
{
	for (int i = 0; i < messages.size(); ++i)
	{
		Message message = messages.front();
		builders[message.messageName]->Build(message.messageData);
		messages.pop();
	}
}