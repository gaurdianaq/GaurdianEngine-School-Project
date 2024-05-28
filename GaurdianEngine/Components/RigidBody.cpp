#include "RigidBody.h"

const std::string RigidBody::_componentType = "RigidBody";

RigidBody::RigidBody()
{
	componentType = &_componentType;
}

RigidBody::~RigidBody()
{

}

void RigidBody::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("mass");
	writer->Double(mass);
	writer->Key("inverseMass");
	writer->Double(inverseMass);
	writer->EndObject();
}

void RigidBody::Deserialize(const Value& value)
{
	mass = value["mass"].GetDouble();
	inverseMass = value["inverseMass"].GetDouble();
}