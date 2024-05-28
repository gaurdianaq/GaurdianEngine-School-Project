This was an ongoing project when I was at Fanshawe college to build a basic game engine, and while there are many things I'd do differently if I were to attempt this sort of project again, I do look back proudly on what I accomplished at the time.

# gaurdianengine

How to run my program...

Build it, copy the appropriate assimp and fmod dll's to the executable folder.

The dll's are in dll's folder.

Using the program

DSP's can be toggled on and off with 1-9
Holding ctrl and pressing 1-9 will toggle pause on each of the songs.

Songs 1-3 are part of group1, songs 4-6 are part of group2, songs 7-9 are part of group3.

Each group has 3 different DSP's attached to them, these can be changed by editing fmodconfig.json, though don't touch the friendly name as currently in my program is hardcoded to look for those friendly names.

Pressing ctrl+tab will select the next channelgroup.

Pressing up and down will adjust the volume of the selected channelgroup.

Pressing ctrl+up or ctrl+down will adjust the pitch of the selected channelgroup.

Pressing shift+up or shift+down will adjust the balance of the channelgroup.
