#include "Acceleration.h"

const std::string Acceleration::_componentType = "Acceleration";

Acceleration::Acceleration()
{
	componentType = &_componentType;
}

Acceleration::~Acceleration()
{
	
}

void Acceleration::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("minAcceleration");
	writer->StartObject();
	writer->Key("x");
	writer->Double(minAcceleration.x);
	writer->Key("y");
	writer->Double(minAcceleration.y);
	writer->Key("z");
	writer->Double(minAcceleration.z);
	writer->EndObject();
	writer->Key("maxAcceleration");
	writer->StartObject();
	writer->Key("x");
	writer->Double(maxAcceleration.x);
	writer->Key("y");
	writer->Double(maxAcceleration.y);
	writer->Key("z");
	writer->Double(maxAcceleration.z);
	writer->EndObject();
	writer->Key("currentAcceleration");
	writer->StartObject();
	writer->Key("x");
	writer->Double(currentAcceleration.x);
	writer->Key("y");
	writer->Double(currentAcceleration.y);
	writer->Key("z");
	writer->Double(currentAcceleration.z);
	writer->EndObject();
	writer->EndObject();
}

void Acceleration::Deserialize(const Value& value)
{
	minAcceleration = glm::vec3(value["minAcceleration"]["x"].GetDouble(),
		value["minAcceleration"]["y"].GetDouble(),
		value["minAcceleration"]["z"].GetDouble());
	maxAcceleration = glm::vec3(value["maxAcceleration"]["x"].GetDouble(),
		value["maxAcceleration"]["y"].GetDouble(),
		value["maxAcceleration"]["z"].GetDouble());
	currentAcceleration = glm::vec3(value["currentAcceleration"]["x"].GetDouble(),
		value["currentAcceleration"]["y"].GetDouble(),
		value["currentAcceleration"]["z"].GetDouble());
}