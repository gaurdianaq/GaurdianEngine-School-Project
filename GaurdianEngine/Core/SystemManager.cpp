#include "SystemManager.h"
#include "MessageMediator.h"
#include "../Headers/SystemTypes.h"

SystemManager* SystemManager::instance;

SystemManager::SystemManager()
{
}


void SystemManager::SetWindow(GLFWwindow* _window)
{
	window = _window;
}

SystemManager* SystemManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new SystemManager();
	}
	return instance;
}

//MessageProcessor should be registered before this is ever called as some systems are registered with the messaging system
void SystemManager::AddSystem(std::string systemType)
{
	if (systemType == "Mesh")
	{
		MeshRenderSystem* meshRenderSystem = new MeshRenderSystem();
		systemsByName[systemType] = meshRenderSystem;
		systems.push_back(meshRenderSystem);
	}
	else if (systemType == "Light")
	{
		systems.push_back(new LightSystem());
	}
	else if (systemType == "Builder")
	{
		BuilderSystem* builderSystem = new BuilderSystem();
		mediator->RegisterReceiver("Builder", builderSystem);
		systemsByName[systemType] = builderSystem;
		systems.push_back(builderSystem);
	}
	else if (systemType == "DebugInput")
	{
		DebugInput* input = new DebugInput();
		input->SetMsgSender(mediator);
		input->SetWindow(window);
		mediator->RegisterReceiver("DebugInput", input);
		systemsByName[systemType] = input;
		systems.push_back(input);
	}
	else if (systemType == "Motion")
	{
		MotionSystem* motion = new MotionSystem();
		systemsByName[systemType] = motion;
		systems.push_back(motion);
	}
	else if (systemType == "Collision")
	{
		CollisionSystem* collisionSystem = new CollisionSystem();
		collisionSystem->SetMsgSender(mediator);
		systemsByName[systemType] = collisionSystem;
		systems.push_back(collisionSystem);
	}
	else if (systemType == "CollisionResponse")
	{
		CollisionResponseSystem* collisionResponseSystem = new CollisionResponseSystem();
		collisionResponseSystem->SetMsgSender(mediator);
		mediator->RegisterReceiver("CollisionResponse", collisionResponseSystem);
		systemsByName[systemType] = collisionResponseSystem;
		systems.push_back(collisionResponseSystem);
	}
	else if (systemType == "AudioMessage")
	{
		AudioMessageSystem* audioMessageSystem = new AudioMessageSystem();
		mediator->RegisterReceiver("Audio", audioMessageSystem);
		systemsByName[systemType] = audioMessageSystem;
		systems.push_back(audioMessageSystem);
	}
	else if (systemType == "Audio")
	{
		AudioSystem* audioSystem = new AudioSystem();
		systemsByName[systemType] = audioSystem;
		systems.push_back(audioSystem);
	}
	else if (systemType == "Camera")
	{
		CameraSystem* cameraSystem = new CameraSystem();
		systemsByName[systemType] = cameraSystem;
		systems.push_back(cameraSystem);
	}
	else if (systemType == "DebugRender")
	{
		DebugRenderSystem* debugRenderSystem = new DebugRenderSystem();
		systemsByName[systemType] = debugRenderSystem;
		systems.push_back(debugRenderSystem);
	}
	else
	{
		std::cout << "Unknown system type..." << std::endl;
		return;
	}
}

void SystemManager::Process()
{
	mediator->ProcessMessages();
	for (unsigned int i = 0; i < systems.size(); ++i)
	{
		if (systems[i]->isEnabled) //if it's not enabled skip this system
		{
			systems[i]->Process();
		}
	}
}

//might keep this... undecided
void SystemManager::Stop()
{
	for (int i = (systems.size()-1); i >= 0; --i)
	{
		if (systems[i]->Stop != nullptr)
		{
			systems[i]->Stop(systems[i]);
		}
	}
}