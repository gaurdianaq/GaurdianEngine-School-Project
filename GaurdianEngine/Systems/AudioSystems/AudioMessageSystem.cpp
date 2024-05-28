#include "AudioMessageSystem.h"
#include "../../MessageTypes/AudioMessages.h"
#include "../../ResourceManager/AudioManager/AudioManager.h"

AudioMessageSystem::AudioMessageSystem()
{
	selectedChannelGroup = "group1";
}

AudioMessageSystem::~AudioMessageSystem()
{

}

void AudioMessageSystem::ProcessMessages()
{
	for (int i = 0; i < messages.size(); ++i)
	{
		Message message = messages.front();
		AudioMessage* audioMessageData = dynamic_cast<AudioMessage*>(message.messageData);
		AudioAdjustMessage* audioAdjustMessageData = dynamic_cast<AudioAdjustMessage*>(message.messageData);
		ToggleMessage* toggleMessageData = dynamic_cast<ToggleMessage*>(message.messageData);
		if(audioMessageData != nullptr)
		{
			if (message.messageName == "Play_Sound")
			{
				audioManager->PlaySound(audioMessageData->soundName);
			}
			else if (message.messageName == "Create_Channel_Group")
			{
				audioManager->CreateChannelGroup(audioMessageData->channelGroupName);
			}
			else if (message.messageName == "Register_Channel_To_Group")
			{
				audioManager->AddChannelToChannelGroup(audioMessageData->soundName, audioMessageData->channelGroupName);
			}
		}	
		else if (toggleMessageData != nullptr)
		{
			if (message.messageName == "ToggleDSP")
			{
				audioManager->ToggleDSP(toggleMessageData->Name);
			}
			else if (message.messageName == "TogglePause")
			{
				audioManager->TogglePause(toggleMessageData->Name);
			}
			else if (message.messageName == "ToggleRecording")
			{
				audioManager->ToggleRecording("recording");
			}
			
		}
		else if (audioAdjustMessageData != nullptr)
		{
			if (message.messageName == "Adjust_Volume")
			{
				if (selectedChannelGroup != "")
				{
					audioManager->AdjustChannelGroupVolume(selectedChannelGroup, audioAdjustMessageData->adjustValue);
				}
			}
			else if (message.messageName == "Adjust_Pitch")
			{
				if (selectedChannelGroup != "")
				{
					audioManager->AdjustChannelGroupPitch(selectedChannelGroup, audioAdjustMessageData->adjustValue);
				}
			}
			else if (message.messageName == "Adjust_Balance")
			{
				if (selectedChannelGroup != "")
				{
					audioManager->AdjustChannelGroupBalance(selectedChannelGroup, audioAdjustMessageData->adjustValue);
				}
			}
		}
		else
		{
			if (message.messageName == "NextChannelGroup")
			{
				if (selectedChannelGroup == "group1")
				{
					selectedChannelGroup = "group2";
				}
				else if (selectedChannelGroup == "group2")
				{
					selectedChannelGroup = "group3";
				}
				else if (selectedChannelGroup == "group3")
				{
					selectedChannelGroup = "group1";
				}
			}
		}
		delete message.messageData;
		messages.pop();
	}
}