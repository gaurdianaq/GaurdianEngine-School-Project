#ifndef _DSP_HG
#define _DSP_HG

#include <fmod/fmod.hpp>
#include <string>

class DSP
{
public:
	DSP();
	~DSP();
	bool isBypassed;
	FMOD::DSP* dsp;
};

#endif