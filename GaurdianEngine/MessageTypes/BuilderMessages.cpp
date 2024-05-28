#include "BuilderMessages.h"

BuildBallData::BuildBallData(std::string _ballName, float _ballSize, float _ballWeight, glm::vec3 _maxVelocity, glm::vec3 _acceleration, glm::vec3 _position, glm::vec4 _ballDiffuse, glm::vec4 _ballSpecular)
{
	ballName = _ballName;
	ballSize = _ballSize;
	ballWeight = _ballWeight;
	ballDiffuse = _ballDiffuse;
	ballSpecular = _ballSpecular;
	position = _position;
	acceleration = _acceleration;
	maxVelocity = _maxVelocity;
}