#include "Headers/Global.h"
#include <iostream>
#include <time.h>

#include "Core/SystemManager.h"
#include "ResourceManager/ResourceManager.h"
#include "Core/SceneManager.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char* argv[])
{
	std::string sceneFile = "defaultScene.json";

	if (argc == 2)
	{
		sceneFile = argv[1];
	}

	srand(time(NULL));
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(1366, 768, "Hello there", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	//create program

	resourceManager->Start();

	sceneManager->LoadScene(sceneFile.c_str());

	sceneManager->SetActiveCamera(sceneManager->GetEntityByName("mainCamera"));
	systemManager->SetWindow(window);
	systemManager->AddSystem("Motion"); //motion should be set before light/mesh so that motion is calculated before rendering
	//systemManager->AddSystem("Collision");
	//systemManager->AddSystem("CollisionResponse");
	systemManager->AddSystem("Camera");
	systemManager->AddSystem("DebugRender");
	systemManager->AddSystem("Light");
	systemManager->AddSystem("Mesh");
	systemManager->AddSystem("Builder");
	systemManager->AddSystem("DebugInput");
	systemManager->AddSystem("AudioMessage");
	systemManager->AddSystem("Audio");

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH);		// Enables the KEEPING of the depth information
		glEnable(GL_DEPTH_TEST);	// When drawing, checked the existing depth
		glEnable(GL_CULL_FACE);	// Discared "back facing" triangles

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(sceneManager->GetSceneColour().r, sceneManager->GetSceneColour().g, sceneManager->GetSceneColour().b, 1.0f);
		systemManager->Process();
		glfwSwapBuffers(window);
		glfwPollEvents();
		//debugInput.GetInput();
	}
	systemManager->Stop();
	//sceneManager->SaveScene("level.json");
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	_CrtDumpMemoryLeaks();//nee dto figure out how this works
	return 0;
}