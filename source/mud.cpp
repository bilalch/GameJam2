#include "mud.h"

int Mud::update(PlayerCar *m_char, ScrollingBackground *m_scroll_bg)
{
	m_x1-=m_scroll_bg->getScrollSpeed();
	m_x2-=m_scroll_bg->getScrollSpeed();

	//detect collision
	if (m_char->isAtInitY())
	{
		if ((m_char->getX1() > m_x1 && m_char->getX1() < m_x2) || 
			(m_char->getX2() > m_x1 && m_char->getX2() < m_x2) ||
			(m_x1 > m_char->getX1() && m_x2 < m_char->getX2()))
		{
			//collision occured
			return 2;
		}	
	}
}

int Mud::update(Chicken *m_char, ScrollingBackground *m_scroll_bg)
{
	m_x1-=m_scroll_bg->getScrollSpeed();
	m_x2-=m_scroll_bg->getScrollSpeed();

	//detect collision
	if (m_char->isAtInitY())
	{
		if ((m_char->getX1() > m_x1 && m_char->getX1() < m_x2) || 
			(m_char->getX2() > m_x1 && m_char->getX2() < m_x2) ||
			(m_x1 > m_char->getX1() && m_x2 < m_char->getX2()))
		{
			//collision occured
			return 2;
		}	
	}
}

void Mud::draw()
{
	if (m_x1 < OBSERVER->getDeviceWidth()) {
	
		Iw2DDrawImage(m_image,CIwFVec2(m_x1,m_y1),CIwFVec2(m_width, m_height));
	}
}