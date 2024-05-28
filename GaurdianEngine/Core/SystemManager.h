#ifndef _SYSTEM_MANAGER_HG
#define _SYSTEM_MANAGER_HG

#include "System.h"
#include <unordered_map>
#include "../Headers/Global.h"

//Creates a Unified way of processing systems, it will first call init all systems in the order of which they're added.
//and then call their process functions in order, at the end of execution, stop will be called in reverse order and shutdown everything.
class SystemManager
{
public:
	static SystemManager* Instance();
	void AddSystem(std::string systemType);
	void Process();
	void Stop();
	void SetWindow(GLFWwindow* _window);
	void ToggleSystem(std::string systemName);
private:
	SystemManager();
	GLFWwindow* window; //temporary measure;
	static SystemManager* instance;
	std::vector<System*> systems;
	std::unordered_map<std::string, System*> systemsByName;
};

#define systemManager SystemManager::Instance()

#endif // !_SYSTEM_MANAGER_HG
