#include "Collidable.h"

Collidable::Collidable(float x, float y, float width, float height, CIw2DImage* image)
{
	m_x1 = x;
	m_y1 = y;
	m_width = width;
	m_height = height;
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;
	m_image = image;
}

Collidable::~Collidable()
{

}
