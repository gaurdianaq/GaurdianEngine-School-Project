#include "Light.h"

const std::string Light::_componentType = "Light";

Light::Light()
{
	componentType = &_componentType;
}

Light::~Light()
{

}

void Light::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("diffuse");
	writer->StartObject();
	writer->Key("r");
	writer->Double(diffuse.r);
	writer->Key("g");
	writer->Double(diffuse.g);
	writer->Key("b");
	writer->Double(diffuse.b);
	writer->EndObject();
	writer->Key("atten");
	writer->StartObject();
	writer->Key("constant");
	writer->Double(atten.x);
	writer->Key("linear");
	writer->Double(atten.y);
	writer->Key("quadratic");
	writer->Double(atten.z);
	writer->Key("cutoff");
	writer->Double(atten.w);
	writer->EndObject();
	writer->Key("param1");
	writer->StartObject();
	writer->Key("lightType");
	writer->Double(param1.x);
	writer->Key("innerAngle");
	writer->Double(param1.y);
	writer->Key("outerAngle");
	writer->Double(param1.z);
	writer->EndObject();
	writer->Key("param2");
	writer->StartObject();
	writer->Key("x");
	writer->Double(param2.x);
	writer->EndObject();
	writer->EndObject();
}

void Light::Deserialize(const Value& value)
{
	diffuse = glm::vec4(value["diffuse"]["r"].GetDouble(),
		value["diffuse"]["g"].GetDouble(),
		value["diffuse"]["b"].GetDouble(), 1.0f);

	atten = glm::vec4(value["atten"]["constant"].GetDouble(),
		value["atten"]["linear"].GetDouble(),
		value["atten"]["quadratic"].GetDouble(),
		value["atten"]["cutoff"].GetDouble());

	param1 = glm::vec4(value["param1"]["lightType"].GetDouble(),
		value["param1"]["innerAngle"].GetDouble(),
		value["param1"]["outerAngle"].GetDouble(), 0.0f);

	param2 = glm::vec4(value["param2"]["x"].GetDouble(), 0.0f, 0.0f, 0.0f);
}