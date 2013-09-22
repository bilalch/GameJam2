/*
 * this class defines an object of player car
 * this will show the state of damage the car is in
 * keep track of car speed and position
 */

#ifndef CHICKEN_H
#define CHICKEN_H

#include "Iw2D.h"
#include "IwResManager.h"
#include "Iw2DSprite.h"
#include <iostream>
#include <fstream>
#include <spine-marm/spine.h>
#include "spine_char.h"

using namespace std;
using namespace spine;

class Chicken
{
public:
	Chicken(int number);
	~Chicken();

	void update(float speed);
	void draw();

	void initializeCar();

	float getX1() { return x-30; }//40
	float getX2() { return x+50; }
	float getY1() { return y-180; }//160
	float getY2() { return y; }

	bool isAtInitY() { if (y >= groundY) { return true; } else { return false; } }

	float getSpeed() { return car_speed; }
	void setSpeed(float _value) { car_speed = _value; }
	void accelerate(float _value = 1) { car_speed = car_speed + _value; verifySpeedBounds(); }
	void decelerate(float _value = 1) { car_speed = car_speed - _value; verifySpeedBounds(); }
	void verifySpeedBounds();

	void goRight(float _value = 1) { m_x1 = m_x1 + _value; m_x2 = m_x2 + _value; }
	void goLeft(float _value = 1) { m_x1 = m_x1 - _value; m_x2 = m_x2 - _value; }

	void jump(bool fromBoxTopCollision);

private:
	
	float car_speed;

	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
	float m_width;
	float m_height;

	CIwResGroup* imagesGroup;

	int damage;
	float multiplier;

	//Jumping Variabes
	float x, y, initY;
	float gravity;
	bool jumping;
	float jumpVelocity;
	float groundY;
	//Jumping variables end

	SpineChar* m_chicken;
};

#endif