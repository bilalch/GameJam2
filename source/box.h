#ifndef BOX_H
#define BOX_H

#include "collidable.h"

class Box: public Collidable
{
public:
	Box(float x, float y, float width, float height, CIw2DImage* image):Collidable(x,y,width,height,image)
	{}
	~Box()
	{}

	virtual int update(PlayerCar *m_char, ScrollingBackground *m_scroll_bg);
	virtual void draw();

private:

};

#endif //BOX