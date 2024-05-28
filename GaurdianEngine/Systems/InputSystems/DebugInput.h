#ifndef _DEBUG_INPUT_HG
#define _DEBUG_INPUT_HG

#include "../MessageSystem.h"
#include "../../Core/iMessageSender.h"
#include <GLFW/glfw3.h>
#include "../../Core/Entity.h"

enum class InputMode { Camera, Model, Light, Audio };

//input system for debugging (moving models 
class DebugInput : public MessageSystem
{
public:
	DebugInput();
	void Process();
	void SetWindow(GLFWwindow* _window);
	void SetMsgSender(iMessageSender* msgSender);
protected:
	void ProcessMessages();
private:
	GLFWwindow* window;
	Entity* selectedEntity;
	Entity* currentCamera;
	iMessageSender* msgSender;
	unsigned int index; //the index used to access an object in the currently selected vector
	InputMode mode; //the currently selected input mode
	float speed;
	float rotateModifier;
	std::unordered_map<InputMode, std::vector<Entity*>*> entitiesToControl;
};

#endif