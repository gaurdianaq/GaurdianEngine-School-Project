#ifndef _BUILDER_MESSAGES_HG
#define _BUILDER_MESSAGES_HG

#include "../Core/Message.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

//data needed to make a ball
struct BuildBallData : public iMessageData
{
	BuildBallData(std::string _ballName, float _ballSize, float _ballWeight, glm::vec3 _maxVelocity, glm::vec3 _acceleration, glm::vec3 _position, glm::vec4 _ballDiffuse, glm::vec4 _ballSpecular);
	std::string ballName;
	float ballSize;
	float ballWeight;
	glm::vec3 position;
	glm::vec3 acceleration;
	glm::vec3 maxVelocity;
	glm::vec4 ballDiffuse;
	glm::vec4 ballSpecular;
};

#endif