#include "ComponentFactory.h"
#include "../Headers/ComponentTypes.h"

ComponentFactory* ComponentFactory::instance;

ComponentFactory* ComponentFactory::Instance()
{
	if (instance == nullptr)
	{
		instance = new ComponentFactory();
	}

	return instance;
}

ComponentFactory::ComponentFactory()
{

}

Component* ComponentFactory::createComponent(std::string componentType)
{
	if (componentType == "Transform")
	{
		return new Transform();
	}
	else if (componentType == "MeshComponent")
	{
		return new MeshComponent();
	}
	else if (componentType == "Camera")
	{
		return new CameraComponent();
	}
	else if (componentType == "SphereCollider")
	{
		return new SphereCollider();
	}
	else if (componentType == "BoxCollider")
	{
		return new BoxCollider();
	}
	else if (componentType == "Acceleration")
	{
		return new Acceleration();
	}
	else if (componentType == "Velocity")
	{
		return new Velocity();
	}
	else if (componentType == "RigidBody")
	{
		return new RigidBody();
	}
	else if (componentType == "Light")
	{
		return new Light();
	}
	else if (componentType == "AudioComponent")
	{
		return new AudioComponent();
	}
	else if (componentType == "DebugRender")
	{
		return new DebugRenderComponent();
	}
}