#include "DebugRenderComponent.h"
#include "../ResourceManager/MeshManager/Mesh.h"
#include "../ResourceManager/ResourceManager.h"

const std::string DebugRenderComponent::_componentType = "DebugRender";

std::string ShapeTypeToString(DebugShape shape)
{
	switch (shape)
	{
	case DebugShape::Box:
		return "Cube";
		break;
	case DebugShape::Sphere:
		return "Sphere";
		break;
	case DebugShape::Unknown:
		return "Unknown";
		break;
	default:
		return "You broke an enum, I hope you're proud...";
		break;
	}
}

DebugShape StringToShape(std::string shapeName)
{
	if (shapeName == "Cube")
	{
		return DebugShape::Box;
	}
	else if (shapeName == "Sphere")
	{
		return DebugShape::Sphere;
	}
	else
	{
		return DebugShape::Unknown;
	}
}

DebugRenderComponent::DebugRenderComponent()
{
	shape = DebugShape::Sphere; //defaults to sphere
	size = glm::vec3(1.0f);
	componentType = &_componentType;
	offset = glm::vec3(0.0f);
	colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	Mesh* mesh = static_cast<Mesh*>(resourceManager->GetResource("Mesh", "Sphere"));
}

DebugRenderComponent::DebugRenderComponent(DebugShape _shape, glm::vec3 _size, glm::vec3 _offset, glm::vec4 _colour)
{
	shape = _shape;
	size = _size;
	offset = _offset;
	colour = _colour;
	componentType = &_componentType;
	Mesh* mesh = nullptr;
	if (shape == DebugShape::Sphere)
	{
		mesh = static_cast<Mesh*>(resourceManager->GetResource("Mesh", "Sphere"));
	}
	else if (shape == DebugShape::Box)
	{
		mesh = static_cast<Mesh*>(resourceManager->GetResource("Mesh", "Cube"));
	}
	vao_id = mesh->vao_id;
	numIndices = mesh->indices.size();
}

DebugRenderComponent::~DebugRenderComponent()
{
	
}

void DebugRenderComponent::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("shape");
	writer->String(ShapeTypeToString(shape).c_str());
	writer->Key("size");
	writer->StartObject();
	writer->Key("x");
	writer->Double(size.x);
	writer->Key("y");
	writer->Double(size.y);
	writer->Key("z");
	writer->Double(size.z);
	writer->EndObject();
	writer->Key("colour");
	writer->StartObject();
	writer->Key("r");
	writer->Double(colour.r);
	writer->Key("g");
	writer->Double(colour.g);
	writer->Key("b");
	writer->Double(colour.b);
	writer->Key("a");
	writer->Double(colour.a);
	writer->EndObject();
	writer->Key("offset");
	writer->StartObject();
	writer->Key("x");
	writer->Double(offset.x);
	writer->Key("y");
	writer->Double(offset.y);
	writer->Key("z");
	writer->Double(offset.z);
	writer->EndObject();
	writer->EndObject();
}

void DebugRenderComponent::Deserialize(const Value& value)
{
	shape = StringToShape(value["shape"].GetString());
	size = glm::vec3(value["size"]["x"].GetDouble(),
		value["size"]["y"].GetDouble(),
		value["size"]["z"].GetDouble());
	offset = glm::vec3(value["offset"]["x"].GetDouble(),
		value["offset"]["y"].GetDouble(),
		value["offset"]["z"].GetDouble());
	colour = glm::vec4(value["colour"]["r"].GetDouble(),
		value["colour"]["g"].GetDouble(),
		value["colour"]["b"].GetDouble(),
		value["colour"]["a"].GetDouble());

	Mesh* mesh = nullptr;
	if (shape == DebugShape::Sphere)
	{
		mesh = static_cast<Mesh*>(resourceManager->GetResource("Mesh", "Sphere"));
	}
	else if (shape == DebugShape::Box)
	{
		mesh = static_cast<Mesh*>(resourceManager->GetResource("Mesh", "Cube"));
	}
	if (mesh != nullptr)
	{
		vao_id = mesh->vao_id;
		numIndices = mesh->indices.size();
	}
}