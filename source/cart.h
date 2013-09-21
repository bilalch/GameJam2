#ifndef CART_H
#define CART_H

#include "collidable.h"

class Cart: public Collidable
{
public:
	Cart(float x, float y, float width, float height, CIw2DImage* image):Collidable(x,y,width,height,image)
	{}
	~Cart()
	{}

	virtual int update(PlayerCar *m_char);
	virtual void draw();

private:

};

#endif //CART