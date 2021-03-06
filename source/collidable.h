#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Iw2D.h"
#include "player_car.h"
#include "scrolling_background.h"
#include "chicken.h"

class Collidable 
{
public:
	Collidable(float x, float y, float width, float height, CIw2DImage* image);
	~Collidable();

	virtual int update(PlayerCar *m_char, ScrollingBackground *m_scroll_bg) = 0;
	virtual int update(Chicken *m_char, ScrollingBackground *m_scroll_bg) = 0;
	virtual void draw() = 0;

	float getX1() { return m_x1; }
	float getX2() { return m_x2; }
	float getY1() { return m_y1; }
	float getY2() { return m_y2; }

	void setOptimumVelocity(float _value) { m_collide_optimum_velocity = _value; }
	float getOptimumVelocity() { return m_collide_optimum_velocity; }

protected:
	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
	float m_width;
	float m_height;

	CIw2DImage* m_image;

	float m_collide_optimum_velocity;
};

#endif //COLLIDABLE_H