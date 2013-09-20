/*
 * this class defines an object of an
 * opponent car
 */

#ifndef OPPONENT_CAR_H
#define OPPONENT_CAR_H

#include "Iw2D.h"
#include "player_car.h"

class OpponentCar
{

public:
	OpponentCar(int,float,float,CIw2DImage*,float);
	~OpponentCar();
	void Draw();
	bool Update(PlayerCar*);

	void setLane(int number);
	int getLane() { return m_lane; }
	float getY1() { return m_y1; }
	float getY2() { return m_y2; }

	float getCurrentSpeed() { return m_current_speed; }
	void setCurrentSpeed(float _value) { m_current_speed = _value; }

	void collision() { m_y1-=50; m_y2-=50; }

private:
	CIw2DImage* m_image;	// shallow copy planned for now

	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
	float m_width;
	float m_height;

	float m_maximum_speed;
	float m_current_speed;

	int lanes;
	float left_bound;
	float right_bound;
	float lane_width;
	int m_lane;

};

#endif