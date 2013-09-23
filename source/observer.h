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

	int accelerometer_x;
	int accelerometer_y;
	int accelerometer_z;

	float deviceWidth;
	float deviceHeight;

	float ratio;
	float heightRatio;

public:
	static Observer* getInstance();
	~Observer(void);
	GlobalDevice getGlobalDevice(){ return currentDevice; }
	float getDeviceWidth() { return deviceWidth; }
	float getDeviceHeight() { return deviceHeight; }

	int getAccelerometerX() { return accelerometer_x; }
	int getAccelerometerY() { return accelerometer_y; }
	int getAccelerometerZ() { return accelerometer_z; }

	void setAccelerometerX(int _x) { accelerometer_x = _x; }
	void setAccelerometerY(int _y) { accelerometer_y = _y; }
	void setAccelerometerZ(int _z) { accelerometer_z = _z; }

	float getRatio();
	float getHeightRatio();
};

