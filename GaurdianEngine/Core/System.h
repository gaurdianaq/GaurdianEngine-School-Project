#ifndef _SERVICE_HG
#define _SERVICE_HG
#include <vector>
#include <iostream>

class System
{
	friend class SystemManager;
public:
	System();
protected:
	bool isEnabled;
	virtual void Process() = 0;
	void (*Stop)(System*);
};

#endif // !_SERVICE_HG
