#include "Audio.h"

std::string AudioTypeToString(AudioType type)
{
	switch (type)
	{
	case AudioType::Sample:
		return "Sample";
		break;
	case AudioType::Stream:
		return "Stream";
		break;
	case AudioType::NetStream:
		return "NetStream";
		break;
	case AudioType::Recording:
		return "Recording";
		break;
	}
	
}

AudioType StringToAudioType(std::string type)
{
	if (type == "Sample")
	{
		return AudioType::Sample;
	}
	else if (type == "Stream")
	{
		return AudioType::Stream;
	}
	else if (type == "NetStream")
	{
		return AudioType::NetStream;
	}
	else if (type == "Recording")
	{
		return AudioType::Recording;
	}
}

std::string fmodSoundTypeToString(FMOD_SOUND_TYPE type)
{
	switch (type)
	{
	case FMOD_SOUND_TYPE_AIFF:
		return "FMOD_SOUND_TYPE_AIFF";
		break;
	case FMOD_SOUND_TYPE_ASF:
		return "FMOD_SOUND_TYPE_ASF";
		break;
	case FMOD_SOUND_TYPE_DLS:
		return "FMOD_SOUND_TYPE_DLS";
		break;
	case FMOD_SOUND_TYPE_FLAC:
		return "FMOD_SOUND_TYPE_FLAC";
		break;
	case FMOD_SOUND_TYPE_FSB:
		return "FMOD_SOUND_TYPE_FSB";
		break;
	case FMOD_SOUND_TYPE_IT:
		return "FMOD_SOUND_TYPE_IT";
		break;
	case FMOD_SOUND_TYPE_MIDI:
		return "FMOD_SOUND_TYPE_MIDI";
		break;
	case FMOD_SOUND_TYPE_MOD:
		return "FMOD_SOUND_TYPE_MOD";
		break;
	case FMOD_SOUND_TYPE_MPEG:
		return "FMOD_SOUND_TYPE_MPEG";
		break;
	case FMOD_SOUND_TYPE_OGGVORBIS:
		return "FMOD_SOUND_TYPE_OGGVORBIS";
		break;
	case FMOD_SOUND_TYPE_PLAYLIST:
		return "FMOD_SOUND_TYPE_PLAYLIST";
		break;
	case FMOD_SOUND_TYPE_RAW:
		return "FMOD_SOUND_TYPE_RAW";
		break;
	case FMOD_SOUND_TYPE_S3M:
		return "FMOD_SOUND_TYPE_S3M";
		break;
	case FMOD_SOUND_TYPE_USER:
		return "FMOD_SOUND_TYPE_USER";
		break;
	case FMOD_SOUND_TYPE_WAV:
		return "FMOD_SOUND_TYPE_WAV";
		break;
	case FMOD_SOUND_TYPE_XM:
		return "FMOD_SOUND_TYPE_XM";
		break;
	case FMOD_SOUND_TYPE_XMA:
		return "FMOD_SOUND_TYPE_XMA";
		break;
	case FMOD_SOUND_TYPE_AUDIOQUEUE:
		return "FMOD_SOUND_TYPE_AUDIOQUEUE";
		break;
	case FMOD_SOUND_TYPE_AT9:
		return "FMOD_SOUND_TYPE_AT9";
		break;
	case FMOD_SOUND_TYPE_VORBIS:
		return "FMOD_SOUND_TYPE_VORBIS";
		break;
	case FMOD_SOUND_TYPE_MEDIA_FOUNDATION:
		return "FMOD_SOUND_TYPE_MEDIA_FOUNDATION";
		break;
	case FMOD_SOUND_TYPE_MEDIACODEC:
		return "FMOD_SOUND_TYPE_MEDIACODEC";
		break;
	case FMOD_SOUND_TYPE_FADPCM:
		return "FMOD_SOUND_TYPE_FADPCM";
		break;
	case FMOD_SOUND_TYPE_MAX:
		return "FMOD_SOUND_TYPE_MAX";
		break;
	case FMOD_SOUND_TYPE_UNKNOWN:
		return "FMOD_SOUND_TYPE_UNKNOWN";
		break;
	default:
		return "You broke an enum somehow, I hope you're proud...";
		break;
	}
}

std::string fmodSoundFormatToString(FMOD_SOUND_FORMAT format)
{
	switch (format)
	{
	case FMOD_SOUND_FORMAT_PCM8:
		return "FMOD_SOUND_FORMAT_PCM8";
		break;
	case FMOD_SOUND_FORMAT_PCM16:
		return "FMOD_SOUND_FORMAT_PCM16";
		break;
	case FMOD_SOUND_FORMAT_PCM24:
		return "FMOD_SOUND_FORMAT_PCM24";
		break;
	case FMOD_SOUND_FORMAT_PCM32:
		return "FMOD_SOUND_FORMAT_PCM32";
		break;
	case FMOD_SOUND_FORMAT_PCMFLOAT:
		return "FMOD_SOUND_FORMAT_PCMFLOAT";
		break;
	case FMOD_SOUND_FORMAT_BITSTREAM:
		return "FMOD_SOUND_FORMAT_BITSTREAM";
		break;
	case FMOD_SOUND_FORMAT_MAX:
		return "FMOD_SOUND_FORMAT_MAX";
		break;
	case FMOD_SOUND_FORMAT_NONE:
		return "FMOD_SOUND_FORMAT_NONE";
		break;
	default:
		return "You broke an enum somehow, I hope you're proud...";
		break;
	}
}

const std::string Audio::_resourceType = "Audio";

Audio::Audio()
{
	resourceType = &_resourceType;
	isPaused = true;
}

Audio::Audio(AudioType _type, FMOD_MODE _mode, std::string _filePath, std::string _friendlyName)
{
	resourceType = &_resourceType;
	mode = _mode;
	filePath = _filePath;
	friendlyName = _friendlyName;
	isPaused = true;
}

Audio::~Audio()
{

}

void Audio::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("friendlyName");
	writer->String(friendlyName.c_str());
	writer->Key("filePath");
	writer->String(filePath.c_str());
	writer->Key("channelGroupName");
	writer->String(channelGroupName.c_str());
	writer->Key("type");
	writer->String(AudioTypeToString(type).c_str());
	writer->Key("is3D");
	writer->Bool(is3D);
	writer->Key("loops");
	writer->Bool(loops);
	writer->EndObject();
}

void Audio::Deserialize(const Value& value)
{
	type = StringToAudioType(value["type"].GetString());
	friendlyName = value["friendlyName"].GetString();
	if (type != AudioType::NetStream)
	{
		filePath = "assets/sounds/" + (std::string)value["filePath"].GetString();
	}
	else if (type == AudioType::NetStream)
	{
		filePath = value["filePath"].GetString();
	}
	
	channelGroupName = value["channelGroupName"].GetString();
	
	is3D = value["is3D"].GetBool();
	loops = value["loops"].GetBool();
}