#include "FactoryArgs.h"

//sets aside some space in memory to store whatever arg value we're returning via a nullptr so we're not calling new every time
float fValue;
double dValue;
int iValue;
long long llValue;
unsigned int uiValue;
unsigned long long ullValue;

//it's assumed that the programmer 
void* ProcessArg(Arg arg)
{
	if (arg.argType == "float")
	{
		fValue = stof(arg.argValue);
		return &fValue;
	}
	else if (arg.argType == "double")
	{
		dValue = stod(arg.argValue);
		return &dValue;
	}
	else if (arg.argType == "int")
	{
		iValue = stoi(arg.argValue);
		return &iValue;
	}
	else if (arg.argType == "longlong")
	{
		llValue = stoll(arg.argValue);
		return &llValue;
	}
	else if (arg.argType == "uint")
	{
		uiValue = stoul(arg.argValue);
		return &uiValue;
	}
	else if (arg.argType == "ulonglong")
	{
		ullValue = stoull(arg.argValue);
		return &ullValue;
	}
	return nullptr;
}
