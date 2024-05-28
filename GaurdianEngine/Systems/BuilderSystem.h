#ifndef _BUILDER_SYSTEM_HG
#define _BUILDER_SYSTEM_HG

#include "../Core/System.h"
#include "../Core/MessageReceiver.h"
#include "../Core/Builder.h"
#include <unordered_map>

//stores all the builders, when it receives a message, it will call the appropriate builder and pass the message data
class BuilderSystem : public System, public MessageReceiver
{
public:
	BuilderSystem();
	void Process();
protected:
	void ProcessMessages();
	std::unordered_map<std::string, Builder*> builders;
};

#endif