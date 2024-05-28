#include "Collider.h"

const std::string Collider::_componentType = "Collider";

Collider::Collider()
{
	componentType = &_componentType;
}

Collider::~Collider()
{

}