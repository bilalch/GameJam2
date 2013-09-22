/*
 * this class defines an object of player car
 * this will show the state of damage the car is in
 * keep track of car speed and position
 */

#ifndef PLAYER_CAR_H
#define PLAYER_CAR_H

#include "Iw2D.h"
#include "IwResManager.h"
#include "Iw2DSprite.h"
#include <iostream>
#include <fstream>
#include <spine-marm/spine.h>

using namespace std;
using namespace spine;

class PlayerCar
{
public:
	PlayerCar(int number);
	~PlayerCar();

	void update(float speed);
	void draw();

	void initializeCar();

	void loadRedCar();
	void loadYellowCar();
	void loadGreyCar();
	void unloadCar();

	float getX1() { return x-20; }//40
	float getX2() { return x+20; }
	float getY1() { return y-160; }//160
	float getY2() { return y; }

	float getSpeed() { return car_speed; }
	void setSpeed(float _value) { car_speed = _value; }
	void accelerate(float _value = 1) { car_speed = car_speed + _value; verifySpeedBounds(); }
	void decelerate(float _value = 1) { car_speed = car_speed - _value; verifySpeedBounds(); }
	void verifySpeedBounds();

	void goRight(float _value = 1) { m_x1 = m_x1 + _value; m_x2 = m_x2 + _value; }
	void goLeft(float _value = 1) { m_x1 = m_x1 - _value; m_x2 = m_x2 - _value; }

	void jump();

private:
	
	float car_speed;

	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
	float m_width;
	float m_height;

	CIwResGroup* imagesGroup;

	///Iw2DSprite* spriteSheet;

	int damage;
	float multiplier;

	//Jumping Variabes
	float x, y, initY;
	float gravity;
	bool jumping;
	float jumpVelocity;
	float groundY;
	//Jumping variables end


	void initializeSpine();
	void loadSpine();
	void updateSpine();

	Atlas *atlas;
	SkeletonData *skeletonData;
	Skeleton *skeleton;
	Animation *animation;
	float animationTime;
	uint64 lastFrameTime;

	Atlas *atlas1;
	SkeletonData *skeletonData1;
	Skeleton *skeleton1;
	Animation *animation1;
	float animationTime1;
	uint64 lastFrameTime1;
};

#endif