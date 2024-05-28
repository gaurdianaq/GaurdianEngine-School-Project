#ifndef _AUDIO_MANAGER_HG
#define _AUDIO_MANAGER_HG

#define MAX_CHANNELS 24 //add a define that comes after this to change it

#include "../iResourceManager.h"
#include "../../Serialization/Serializer.h"
#include <unordered_map>
#include "Audio.h"
#include "ChannelGroup.h"
#include "DSP.h"

//handles all fmod calls, fmod should never be directly called outside of this class
class AudioManager : public iResourceManager, public IDeserializeable
{
public:
	~AudioManager();
	static AudioManager* Instance();
	void Init();
	void Update();
	bool LoadResource(Resource* resource);
	void UnloadAudio(std::string audioName);
	void PlaySound(std::string soundName);
	void TogglePause(std::string soundName);
	void CreateChannelGroup(std::string channelGroupName);
	void AddChannelToChannelGroup(std::string soundName, std::string groupName);
	void ToggleDSP(std::string dspName);
	void CreateDSP(std::string dspName, FMOD_DSP_TYPE dspType, bool isActive);
	void AddDSPToChannelGroup(std::string dspName, std::string channelGroupName);
	void AdjustSoundVolume(std::string soundName, float volumeAdjust);
	void AdjustSoundPitch(std::string soundName, float pitchAdjust);
	void AdjustSoundBalance(std::string soundName, float balanceAdjust);
	void AdjustChannelGroupPitch(std::string channelGroupName, float pitchAdjust);
	void AdjustChannelGroupVolume(std::string channelGroupName, float volumeAdjust);
	void AdjustChannelGroupBalance(std::string channelGroupName, float balanceAdjust);
	void ToggleRecording(std::string soundName);
	void getFMODResult(FMOD_RESULT result);
	int* GetNativeRate();
	FMOD::System* getSystem();
protected:
	void Deserialize(Document& document);
private:
	AudioManager();
	FMOD_CREATESOUNDEXINFO exinfo;
	bool isRecording;
	int nativeChannels;
	int nativeRate;
	int numRecordingDevices;
	//int nativeChannels;
	//int nativeRate;
	static AudioManager* instance;
	Deserializer deserializer;
	unsigned int channelRegisterCount;
	std::unordered_map<std::string, ChannelGroup*> channelGroups;
	std::unordered_map<std::string, DSP*> dspsByName;
	FMOD::System* system;
};

#define audioManager AudioManager::Instance()

#endif