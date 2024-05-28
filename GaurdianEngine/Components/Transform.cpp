#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::~Transform()
{

}

const std::string Transform::_componentType = "Transform";

Transform::Transform()
{
	componentType = &_componentType;
	position = glm::vec3(0);
	orientation = glm::quat();
	scale = glm::vec3(1.0f);
}

Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, bool isDegrees, glm::vec3 _scale)
{
	position = _position;
	scale = _scale;
	setOrientation(_rotation, isDegrees);
}

void Transform::adjustOrientation(glm::vec3 _rotation, bool isDegrees)
{
	if (isDegrees) //if isDegrees is true we convert the rotation value to radians before adjusting the quaternion
	{
		_rotation = glm::vec3(glm::radians(_rotation.x), glm::radians(_rotation.y), glm::radians(_rotation.z));
	}

	glm::quat rotationAdjust(_rotation);

	orientation *= rotationAdjust;
}

void Transform::setOrientation(glm::vec3 _rotation, bool isDegrees)
{
	if (isDegrees) //if isDegrees is true we convert the rotation value to radians before adjusting the quaternion
	{
		_rotation = glm::vec3(glm::radians(_rotation.x), glm::radians(_rotation.y), glm::radians(_rotation.z));
	}

	orientation = glm::quat(_rotation);
}


glm::mat4x4 Transform::GetMatModel()
{
	matModel = glm::mat4(1.0f) *
		glm::translate(glm::mat4(1.0f), position) * glm::mat4(orientation);
	matModelInvTrans = glm::inverse(glm::transpose(matModel));
	matModel = matModel * glm::scale(glm::mat4(1.0f), scale);
	return matModel;
}

glm::mat4 Transform::GetMatModelInvTrans()
{
	return matModelInvTrans;
}

void Transform::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("position");
	writer->StartObject();
	writer->Key("x");
	writer->Double(position.x);
	writer->Key("y");
	writer->Double(position.y);
	writer->Key("z");
	writer->Double(position.z);
	writer->EndObject();
	writer->Key("rotation");
	writer->StartObject();
	writer->Key("x");
	writer->Double(glm::degrees(glm::eulerAngles(orientation).x));
	writer->Key("y");
	writer->Double(glm::degrees(glm::eulerAngles(orientation).y));
	writer->Key("z");
	writer->Double(glm::degrees(glm::eulerAngles(orientation).z));
	writer->EndObject();
	writer->Key("scale");
	writer->StartObject();
	writer->Key("x");
	writer->Double(scale.x);
	writer->Key("y");
	writer->Double(scale.y);
	writer->Key("z");
	writer->Double(scale.z);
	writer->EndObject();
	writer->EndObject();
}

void Transform::Deserialize(const Value& value)
{
	position = glm::vec3(value["position"]["x"].GetDouble(),
		value["position"]["y"].GetDouble(),
		value["position"]["z"].GetDouble());
	setOrientation(glm::vec3(value["rotation"]["x"].GetDouble(),
		value["rotation"]["y"].GetDouble(),
		value["rotation"]["z"].GetDouble()), true);
	scale = glm::vec3(value["scale"]["x"].GetDouble(),
		value["scale"]["y"].GetDouble(),
		value["scale"]["z"].GetDouble());
}