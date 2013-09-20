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

class PlayerCar
{
public:
	PlayerCar(int number);
	~PlayerCar();

	void update();
	void draw();

	void initializeCar();

	void loadRedCar();
	void loadYellowCar();
	void loadGreyCar();
	void unloadCar();

	float getX1() { return m_x1; }
	float getX2() { return m_x2; }
	float getY1() { return m_y1; }
	float getY2() { return m_y2; }

	float getSpeed() { return car_speed; }
	void setSpeed(float _value) { car_speed = _value; }
	void accelerate(float _value = 1) { car_speed = car_speed + _value; verifySpeedBounds(); }
	void decelerate(float _value = 1) { car_speed = car_speed - _value; verifySpeedBounds(); }
	void verifySpeedBounds();

	void goRight(float _value = 1) { m_x1 = m_x1 + _value; m_x2 = m_x2 + _value; }
	void goLeft(float _value = 1) { m_x1 = m_x1 - _value; m_x2 = m_x2 - _value; }

private:
	
	float car_speed;

	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
	float m_width;
	float m_height;

	CIwResGroup* imagesGroup;

	Iw2DSprite* spriteSheet;

	int damage;
	float multiplier;
};

#endif