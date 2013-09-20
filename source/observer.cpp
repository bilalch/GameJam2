#include "Observer.h"
#ifndef NULL
#define NULL 0
#endif 

Observer* Observer::sharedInstance = NULL;

Observer* Observer::getInstance()
{
    if(!sharedInstance)
    {
        sharedInstance = new Observer();
        return sharedInstance;
    }
    else
    {
        return sharedInstance;
    }
}

Observer::Observer(void)
{	

	uint32 x = IwGxGetDeviceWidth();
	deviceWidth = x;
	uint32 y = IwGxGetDeviceHeight();
	deviceHeight = y;
	if ((x==320 && y==480) || (x==480 && y==320)) {
		
		currentDevice = GLOBAL_IPHONE3;
		//deviceWidth = 320;
		//deviceHeight = 480;

	} else if ((x==640 && y==960) || (x==960 && y==640)) {
		
		currentDevice = GLOBAL_IPHONE4;
		//deviceWidth = 640;
		//deviceHeight = 960;

	} else if ((x==480 && y==800) || (x==800 && y==480)) {

		currentDevice = GLOBAL_ANDROID1;
		//deviceWidth = 480;
		//deviceHeight = 800;

	} else if ((x==480 && y==854) || (x==854 && y==480)) {

		currentDevice = GLOBAL_ANDROID2;
		//deviceWidth = 480;
		//deviceHeight = 854;
	}
}

Observer::~Observer(void)
{
	delete sharedInstance;
}