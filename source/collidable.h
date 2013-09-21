#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Iw2D.h"
#include "player_car.h"

class Collidable 
{
public:
	Collidable(float x, float y, float width, float height, CIw2DImage* image);
	~Collidable();

	virtual int update(PlayerCar *m_char) = 0;
	virtual void draw() = 0;

protected:
	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
	float m_width;
	float m_height;

	CIw2DImage* m_image;
};

#endif //COLLIDABLE_H