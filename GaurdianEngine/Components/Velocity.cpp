#include "Velocity.h"

const std::string Velocity::_componentType = "Velocity";

Velocity::Velocity()
{
	componentType = &_componentType;
}

Velocity::~Velocity()
{

}

void Velocity::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("minVelocity");
	writer->StartObject();
	writer->Key("x");
	writer->Double(minVelocity.x);
	writer->Key("y");
	writer->Double(minVelocity.y);
	writer->Key("z");
	writer->Double(minVelocity.z);
	writer->EndObject();
	writer->Key("maxVelocity");
	writer->StartObject();
	writer->Key("x");
	writer->Double(maxVelocity.x);
	writer->Key("y");
	writer->Double(maxVelocity.y);
	writer->Key("z");
	writer->Double(maxVelocity.z);
	writer->EndObject();
	writer->Key("currentVelocity");
	writer->StartObject();
	writer->Key("x");
	writer->Double(currentVelocity.x);
	writer->Key("y");
	writer->Double(currentVelocity.y);
	writer->Key("z");
	writer->Double(currentVelocity.z);
	writer->EndObject();
	writer->EndObject();
}

void Velocity::Deserialize(const Value& value)
{
	minVelocity = glm::vec3(value["minVelocity"]["x"].GetDouble(),
		value["minVelocity"]["y"].GetDouble(),
		value["minVelocity"]["z"].GetDouble());
	maxVelocity = glm::vec3(value["maxVelocity"]["x"].GetDouble(),
		value["maxVelocity"]["y"].GetDouble(),
		value["maxVelocity"]["z"].GetDouble());
	currentVelocity = glm::vec3(value["currentVelocity"]["x"].GetDouble(),
		value["currentVelocity"]["y"].GetDouble(),
		value["currentVelocity"]["z"].GetDouble());
}