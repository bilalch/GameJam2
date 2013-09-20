/*
uint32 dw = IwGxGetDeviceWidth(); // returns 176 
uint32 dh = IwGxGetDeviceHeight(); // returns 208 
uint32 sw = IwGxGetScreenWidth(); // returns 176 
uint32 sh = IwGxGetScreenHeight(); // returns 208

Rotate the screen into landscape orientation, and observe how these values change: 

IwGxSetScreenOrient(IW_GX_ORIENT_90); 
uint32 dw = IwGxGetDeviceWidth(); // returns 176 
uint32 dh = IwGxGetDeviceHeight(); // returns 208 
uint32 sw = IwGxGetScreenWidth(); // returns 208 
uint32 sh = IwGxGetScreenHeight(); // returns 176 
*/



#pragma once
#include "Iw2D.h"
#include "IwGx.h"

#define OBSERVER	Observer::getInstance()

struct ButtonCoordinates
{
	float x1, x2;
	float y1, y2;
	bool pressed;
};

struct gameData
{
	uint32 carsDestroyed[5];
	uint64 seconds[5];
	uint64 distances[5];
	uint64 scores[5];
	uint64 totalTimePlayed;
	int gunDamageIndex;
	int armourLevel;
	int coinCount;
};

enum GlobalDevice
{
GLOBAL_IPHONE4,
GLOBAL_IPHONE3,
GLOBAL_IPAD,
GLOBAL_ANDROID1,
GLOBAL_ANDROID2,
GLOBAL_ANDROID_TABLET,
GLOBAL_KINDLE,
};

class Observer
{
private:
    static Observer *sharedInstance;
	Observer(void);
	GlobalDevice currentDevice;

public:
	static Observer* getInstance();
	~Observer(void);
	GlobalDevice getGlobalDevice(){ return currentDevice; }
	float getDeviceWidth() { return deviceWidth; }
	float getDeviceHeight() { return deviceHeight; }


	float deviceWidth;
	float deviceHeight;
};

