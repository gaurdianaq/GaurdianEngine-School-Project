#include <iostream>
#include <ctime>
#include <stdlib.h> 

#include "DebugInput.h"
#include "../../Core/MessageMediator.h"
#include "../../MessageTypes/BuilderMessages.h"
#include "../../Components/Transform.h"
#include "../../Components/MeshComponent.h"
#include "../../Components/Light.h"
#include "../../Core/SceneManager.h"
#include "../../MessageTypes/AudioMessages.h"
#include "../../Components/CameraComponent.h"

bool IsCtrlDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL)) { return true; }
	// both are up
	return false;
}

bool IsAltDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)) { return true; }
	// both are up
	return false;
}

bool IsShiftDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) { return true; }
	// both are up
	return false;
}

bool AreAllModifiersUp(GLFWwindow* window)
{
	if (IsShiftDown(window)) { return false; }
	if (IsCtrlDown(window)) { return false; }
	if (IsAltDown(window)) { return false; }
	// Yup, they are all UP
	return true;
}

int count = 0;
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (IsShiftDown(window))
	{
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Camera", "DebugInput", nullptr));
			return;
		}
		else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Model", "DebugInput", nullptr));
			return;
		}
		else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Light", "DebugInput", nullptr));
			return;
		}
		else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Adjust_Balance", "Audio", new AudioAdjustMessage(0.1f)));
		}
		else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Adjust_Balance", "Audio", new AudioAdjustMessage(-0.1f)));
		}
		else if (key == GLFW_KEY_R && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Play_Sound", "Audio", new AudioMessage("recording", "group1")));
		}
	}

	if (AreAllModifiersUp(window))
	{
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("echo")));
			mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("radio1")));
			return;
		}
		else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("flange")));
			mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("radio2")));
			return;
		}
		else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("distortion")));
			mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("radio3")));
			return;
		}
		else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("echo")));
			return;
		}
		else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("flange")));
			return;
		}
		else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("reverb")));
			return;
		}
		else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("highpass")));
			return;
		}
		else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("reverb")));
			return;
		}
		else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("ToggleDSP", "Audio", new ToggleMessage("oscillator")));
			return;
		}
		else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Adjust_Volume", "Audio", new AudioAdjustMessage(0.1f)));
		}
		else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Adjust_Volume", "Audio", new AudioAdjustMessage(-0.1f)));
		}
		else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		{
			float randomnum = ((rand() % 100) / 5) - 2.5;
			//mediator->SendMessage(Message("Ball", "Builder", new BuildBallData(("ball" + std::to_string(count)), 3, 1, glm::vec3(randomnum), glm::vec4(1.0f), glm::vec4(1.0f))));//this is very ugly... might see if it can be cleaned up somehow, or replace it with json, so I don't have to create a new messagedata type every time...
			++count;
			return;
		}
		else if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("NextEntity", "DebugInput", nullptr));
			return;
		}
		else if (key == GLFW_KEY_O && action == GLFW_PRESS)
		{
			sceneManager->SaveScene();
			return;
		}
	}
	else if (IsCtrlDown(window))
	{
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			
			mediator->SendMessage(Message("Play_Sound", "Audio", new AudioMessage("radio1", "group1")));
			return;
		}
		else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Play_Sound", "Audio", new AudioMessage("radio2", "group1")));
			
			return;
		}
		else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("Play_Sound", "Audio", new AudioMessage("radio3", "group1")));
			
			return;
		}
		else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("spearofjustice")));
			return;
		}
		else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("ghostfight")));
			return;
		}
		else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("megalovania")));
			return;
		}
		else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("savetheworld")));
			return;
		}
		else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("core")));
			return;
		}
		else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("TogglePause", "Audio", new ToggleMessage("maybesans")));
			return;
		}
		else if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("NextChannelGroup", "Audio", nullptr));
		}
		else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("Adjust_Pitch", "Audio", new AudioAdjustMessage(0.1f)));
		}
		else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			//mediator->SendMessage(Message("Adjust_Pitch", "Audio", new AudioAdjustMessage(-0.1f)));
		}
		else if (key == GLFW_KEY_R && action == GLFW_PRESS)
		{
			mediator->SendMessage(Message("ToggleRecording", "Audio", new ToggleMessage("recording")));
		}
	}


	
	
	
}

DebugInput::DebugInput()
{
	std::srand(std::time(nullptr));
	mode = InputMode::Camera;
	entitiesToControl[InputMode::Camera] = sceneManager->GetEntityByComponent("Camera");
	entitiesToControl[InputMode::Model] = sceneManager->GetEntityByComponent("MeshComponent");
	entitiesToControl[InputMode::Light] = sceneManager->GetEntityByComponent("Light");
	entitiesToControl[InputMode::Audio] = sceneManager->GetEntityByComponent("Audio");
	currentCamera = sceneManager->GetActiveCamera();
	speed = 0.3f;
	rotateModifier = 0.3f;
}

float cameraAdjustSpeed = 4;

void DebugInput::ProcessMessages()
{
	for (int i = 0; i < messages.size(); ++i)
	{
		Message message = messages.front();
		if (message.messageName == "Camera")
		{
			if (mode == InputMode::Model)
			{
				MeshComponent* meshComponent = static_cast<MeshComponent*>(entitiesToControl[mode]->at(index)->GetComponent("MeshComponent"));
				meshComponent->isWireFrame = false;
			}
			mode = InputMode::Camera;
			index = 0;
		}
		else if (message.messageName == "Model")
		{
			mode = InputMode::Model;
			MeshComponent* meshComponent = static_cast<MeshComponent*>(entitiesToControl[mode]->at(0)->GetComponent("MeshComponent"));
			meshComponent->isWireFrame = true;
			index = 0;
		}
		else if (message.messageName == "Light")
		{
			if (mode == InputMode::Model)
			{
				MeshComponent* meshComponent = static_cast<MeshComponent*>(entitiesToControl[mode]->at(index)->GetComponent("MeshComponent"));
				meshComponent->isWireFrame = false;
			}
			mode = InputMode::Light;
			index = 0;
		}
		else if (message.messageName == "NextEntity")
		{
			if (index < entitiesToControl[mode]->size() - 1)
			{
				if (mode == InputMode::Model)
				{
					MeshComponent* meshComponent = static_cast<MeshComponent*>(entitiesToControl[mode]->at(index)->GetComponent("MeshComponent"));
					meshComponent->isWireFrame = false;
					meshComponent = static_cast<MeshComponent*>(entitiesToControl[mode]->at(index + 1)->GetComponent("MeshComponent"));
					meshComponent->isWireFrame = true;
				}
				++index;
			}
			else if (index == entitiesToControl[mode]->size() - 1)
			{
				if (mode == InputMode::Model)
				{
					MeshComponent* meshComponent = static_cast<MeshComponent*>(entitiesToControl[mode]->at(index)->GetComponent("MeshComponent"));
					meshComponent->isWireFrame = false;
					meshComponent = static_cast<MeshComponent*>(entitiesToControl[mode]->at(0)->GetComponent("MeshComponent"));
					meshComponent->isWireFrame = true;
				}				
				index = 0;
			}
		}
		messages.pop();
	}
}

void DebugInput::SetWindow(GLFWwindow* _window) 
{
	window = _window;
	glfwSetKeyCallback(window, keyboardCallback);
}

void DebugInput::SetMsgSender(iMessageSender* _msgSender)
{
	msgSender = _msgSender;
}

void DebugInput::Process()
{
	ProcessMessages();
	Transform* transform = static_cast<Transform*>(entitiesToControl[mode]->at(index)->GetComponent("Transform"));
	CameraComponent* cameraComponent = static_cast<CameraComponent*>(currentCamera->GetComponent("Camera"));
	if (AreAllModifiersUp(window))
	{
		if (mode != InputMode::Camera)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				transform->position.z += speed;
			}
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				transform->position.z -= speed;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				transform->position.x -= speed;
			}
			else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				transform->position.x += speed;
			}

			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			{
				transform->position.y += speed;
			}
			else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			{
				transform->position.y -= speed;
			}
		}
		else
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				cameraComponent->AdjustZ(speed);
			}
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				cameraComponent->AdjustZ(-speed);
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				cameraComponent->AdjustX(speed);
			}
			else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				cameraComponent->AdjustX(-speed);
			}

			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			{
				cameraComponent->AdjustY(speed);
			}
			else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			{
				cameraComponent->AdjustY(-speed);
			}

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				cameraComponent->AdjustPitch(speed * cameraAdjustSpeed);
			}
			else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				cameraComponent->AdjustPitch(-speed * cameraAdjustSpeed);
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				cameraComponent->AdjustYaw(speed * cameraAdjustSpeed);
			}
			else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				cameraComponent->AdjustYaw(-speed * cameraAdjustSpeed);
			}

			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			{
				cameraComponent->AdjustRoll(speed * cameraAdjustSpeed);
			}
			else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			{
				cameraComponent->AdjustRoll(-speed * cameraAdjustSpeed);
			}
		}
	}		
	else if (IsShiftDown(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			transform->adjustOrientation(glm::vec3(rotateModifier, 0, 0), false);
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			transform->adjustOrientation(glm::vec3(-(rotateModifier), 0, 0), false);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			transform->adjustOrientation(glm::vec3(0, rotateModifier, 0), false);
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			transform->adjustOrientation(glm::vec3(0, -(rotateModifier), 0), false);
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			transform->adjustOrientation(glm::vec3(0, 0, rotateModifier), false);
		}
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			transform->adjustOrientation(glm::vec3(0, 0, -(rotateModifier)), false);
		}
	}
	else if (IsCtrlDown(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			transform->scale.z += speed;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			transform->scale.z -= speed;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			transform->scale.x += speed;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			transform->scale.x -= speed;
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			transform->scale.y += speed;
		}
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			transform->scale.y -= speed;
		}
	}
	
	
}