#include "Component.h"

Component::~Component()
{
	delete componentType;
}