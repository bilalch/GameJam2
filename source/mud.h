#ifndef MUD_H
#define MUD_H

#include "collidable.h"

class Mud: public Collidable
{
public:
	Mud(float x, float y, float width, float height, CIw2DImage* image):Collidable(x,y,width,height,image)
	{}
	~Mud()
	{}

	virtual int update(PlayerCar *m_char, ScrollingBackground *m_scroll_bg);
	virtual void draw();

private:

};

#endif //MUD