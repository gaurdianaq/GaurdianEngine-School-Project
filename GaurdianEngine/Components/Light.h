#ifndef _LIGHT_HG
#define _LIGHT_HG

#include "../Core/Component.h"
#include <glm/vec4.hpp>

class Light : public Component
{
public:
	Light();
	~Light();
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 atten;
	glm::vec4 param1;
	glm::vec4 param2;
	
	int diffuse_UniLoc;
	int atten_UniLoc;
	int position_UniLoc;
	int direction_UniLoc;
	int param1_UniLoc;
	int param2_UniLoc;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif
