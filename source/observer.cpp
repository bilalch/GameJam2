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
	uint32 y = IwGxGetDeviceHeight();
	if ( x > y ) {

		deviceWidth = x;
		deviceHeight = y;
	} else {

		deviceWidth = y;
		deviceHeight = x;
	}

	float ratio1 = deviceWidth / 960;
	float ratio2 = deviceHeight / 640;
	ratio = 1;

	if ( ratio1 > ratio2 )
		ratio = ratio2;
	else
		ratio = ratio1;
}

float Observer::getRatio()
{
	return ratio;
}

Observer::~Observer(void)
{
	delete sharedInstance;
}