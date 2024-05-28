#ifndef _BUILDER_HG
#define _BUILDER_HG

#include "Message.h"

class Builder
{
public:
	virtual void Build(iMessageData* data) = 0;
};

#endif // !_BUILDER_HG
