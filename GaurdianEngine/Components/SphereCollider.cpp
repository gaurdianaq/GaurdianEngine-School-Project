#include "SphereCollider.h"

SphereCollider::SphereCollider()
{
	colliderType = ColliderType::Sphere; //might be able to get rid of this;
}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("radius");
	writer->Double(radius);
	writer->EndObject();
}

void SphereCollider::Deserialize(const Value& value)
{
	radius = value["radius"].GetDouble();
}