#include "AudioComponent.h"

const std::string AudioComponent::_componentType = "AudioComponent";

AudioComponent::AudioComponent()
{
	componentType = &_componentType;
}

AudioComponent::~AudioComponent()
{

}

void AudioComponent::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("soundName");
	writer->String(soundName.c_str());
	writer->EndObject();
}

void AudioComponent::Deserialize(const Value& value)
{
	soundName = value["soundName"].GetString();
}