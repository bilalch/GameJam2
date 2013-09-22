#ifndef CART_H
#define CART_H

#include "collidable.h"
#include "chicken.h"

class Cart: public Collidable
{
public:
	Cart(float x, float y, float width, float height, CIw2DImage* image):Collidable(x,y,width,height,image)
	{}
	~Cart()
	{}

	virtual int update(PlayerCar *m_char, ScrollingBackground *m_scroll_bg);
	virtual int update(Chicken *m_char, ScrollingBackground *m_scroll_bg);
	virtual void draw();

private:

};

#endif //CART