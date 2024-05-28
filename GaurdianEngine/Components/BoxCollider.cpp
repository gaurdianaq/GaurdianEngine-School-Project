#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	colliderType = ColliderType::Box;
}

BoxCollider::~BoxCollider()
{
	
}

void BoxCollider::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("radius");
	writer->StartObject();
	writer->Key("x");
	writer->Double(radius.x);
	writer->Key("y");
	writer->Double(radius.y);
	writer->Key("z");
	writer->Double(radius.z);
	writer->EndObject();
	writer->EndObject();
}

void BoxCollider::Deserialize(const Value& value)
{
	radius = glm::vec3(value["radius"]["x"].GetDouble(),
		value["radius"]["y"].GetDouble(),
		value["radius"]["z"].GetDouble());
}