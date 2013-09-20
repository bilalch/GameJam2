#include "opponent_car.h"
#include "observer.h"

OpponentCar::OpponentCar(int _lanes, float _leftbound, float _rightbound, CIw2DImage* _image, float _max_speed)
{
	m_image = _image;		// shallow copy
	lanes = _lanes;
	left_bound = _leftbound;
	right_bound = _rightbound;
	lane_width = (right_bound - left_bound)/lanes;
	m_current_speed = _max_speed/2;
	m_maximum_speed = _max_speed;
	m_lane = 0;
}

OpponentCar::~OpponentCar()
{

}

void OpponentCar::Draw()
{
	Iw2DDrawImage(m_image,CIwSVec2(m_x1,m_y1));
}

bool OpponentCar::Update(PlayerCar* m_playerCar)
{
	if ( m_current_speed < m_maximum_speed ){
		
		m_current_speed++;
	} else if ( m_current_speed > m_maximum_speed ) {
		
		m_current_speed--;
	}
	float speed_difference = m_playerCar->getSpeed() - m_current_speed;

	m_y1 = m_y1 + speed_difference;
	m_y2 = m_y2 + speed_difference;

	if ( m_y2 >= m_playerCar->getY1() && m_y1 < m_playerCar->getY2() ) {
		
		if ( m_x1 >= m_playerCar->getX1() && m_x2 <= m_playerCar->getX2() ) {
			
			m_y1 = m_y1 - 50;
			m_y2 = m_y2 - 50;
			m_playerCar->setSpeed(m_playerCar->getSpeed() - 10);
			m_current_speed = m_current_speed + 10;
		}
	}

	if ( m_y2 < -OBSERVER->getDeviceHeight() ) {
		
		return false;
	} else if ( m_y1 > 3*OBSERVER->getDeviceHeight()/2 ) {
		
		return false;
	}
	return true;
}

void OpponentCar::setLane(int number)
{
	m_lane = number;
	switch (number)
	{
	case 1:
		m_x1 = left_bound + (lane_width - m_image->GetWidth())/2;
		m_y1 = 0;
		m_x2 = m_x1 + m_image->GetWidth();
		m_y2 = m_y1 + m_image->GetHeight();
		break;

	case 2:
		m_x1 = left_bound + lane_width + (lane_width - m_image->GetWidth())/2;
		m_y1 = 0;
		m_x2 = m_x1 + m_image->GetWidth();
		m_y2 = m_y1 + m_image->GetHeight();
		break;

	case 3:
		m_x1 = left_bound + 2*lane_width + (lane_width - m_image->GetWidth())/2;
		m_y1 = 0;
		m_x2 = m_x1 + m_image->GetWidth();
		m_y2 = m_y1 + m_image->GetHeight();
		break;

	default:
		m_x1 = left_bound + (lane_width - m_image->GetWidth())/2;
		m_y1 = 0;
		m_x2 = m_x1 + m_image->GetWidth();
		m_y2 = m_y1 + m_image->GetHeight();
		break;
	};
}