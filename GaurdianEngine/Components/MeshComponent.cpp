#include "MeshComponent.h"
#include "../ResourceManager/MeshManager/Mesh.h"
#include "../ResourceManager/TextureManager/Texture.h"
#include "../ResourceManager/ResourceManager.h"

const std::string MeshComponent::_componentType = "MeshComponent";

MeshComponent::MeshComponent()
{
	componentType = &_componentType;
	materialDiffuse = glm::vec4(1.0f);
	materialSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 0.2f);
	isWireFrame = false;
	useVertColour = false;
	useLighting = true;
}

MeshComponent::~MeshComponent()
{

}

void MeshComponent::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("meshName");
	writer->String(meshName.c_str());
	writer->Key("materialDiffuse");
	writer->StartObject();
	writer->Key("r");
	writer->Double(materialDiffuse.r);
	writer->Key("g");
	writer->Double(materialDiffuse.g);
	writer->Key("b");
	writer->Double(materialDiffuse.b);
	writer->Key("alpha");
	writer->Double(materialDiffuse.a);
	writer->EndObject();
	writer->Key("materialSpecular");
	writer->StartObject();
	writer->Key("r");
	writer->Double(materialSpecular.r);
	writer->Key("g");
	writer->Double(materialSpecular.g);
	writer->Key("b");
	writer->Double(materialSpecular.b);
	writer->Key("a");
	writer->Double(materialSpecular.a);
	writer->EndObject();
	writer->Key("useVertColour");
	writer->Bool(useVertColour);
	writer->Key("useLighting");
	writer->Bool(useLighting);
	writer->Key("textures");
	writer->StartArray();
	for (int i = 0; i < textureNames.size(); ++i)
	{
		writer->StartObject();
		writer->Key("texture");
		writer->String(textureNames[i].c_str());
		writer->EndObject();
	}
	writer->EndArray();
	writer->EndObject();
}

void MeshComponent::Deserialize(const Value& value)
{
	meshName = value["meshName"].GetString();
	materialDiffuse = glm::vec4(value["materialDiffuse"]["r"].GetDouble(),
		value["materialDiffuse"]["g"].GetDouble(),
		value["materialDiffuse"]["b"].GetDouble(),
		value["materialDiffuse"]["alpha"].GetDouble());
	materialSpecular = glm::vec4(value["materialSpecular"]["r"].GetDouble(),
		value["materialSpecular"]["g"].GetDouble(),
		value["materialSpecular"]["b"].GetDouble(),
		value["materialSpecular"]["a"].GetDouble());
	useVertColour = value["useVertColour"].GetBool();
	useLighting = value["useLighting"].GetBool();

	const Value& textures = value["textures"];

	for (Value::ConstValueIterator it = textures.Begin(); it != textures.End(); ++it)
	{
		textureNames.push_back((*it)["texture"].GetString());
		Texture* texture = static_cast<Texture*>(resourceManager->GetResource("Texture", textureNames.back()));
		texInfo info;
		info.texID = texture->imageID;
		info.texBlendStrength = (*it)["texStrength"].GetDouble();
		vecTexture.push_back(info);
	}

	Mesh* mesh = static_cast<Mesh*>(resourceManager->GetResource("Mesh", meshName));
	vao_id = mesh->vao_id;
	numIndices = mesh->indices.size();
}