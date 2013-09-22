#include "cart.h"

int Cart::update(PlayerCar *m_char, ScrollingBackground *m_scroll_bg)
{
	//detect collision
	if (m_char->getY2() > m_y1)
	{
		if ((m_char->getX1() > m_x1 && m_char->getX1() < m_x2) || 
			(m_char->getX2() > m_x1 && m_char->getX2() < m_x2) ||
			(m_x1 > m_char->getX1() && m_x2 < m_char->getX2()))
		{
			//collision occured
			return 1;
		}	
	}

	m_x1-=m_scroll_bg->getScrollSpeed();
	m_x2-=m_scroll_bg->getScrollSpeed();
}

void Cart::draw()
{
	Iw2DDrawImage(m_image,CIwFVec2(m_x1,m_y1),CIwFVec2(m_width, m_height));
}