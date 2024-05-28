#ifndef _FACTORY_ARGS_HG
#define _FACTORY_ARGS_HG

#include <string>

struct Arg
{
	std::string argType;
	std::string argValue;
};

void* ProcessArg(Arg arg);

#endif