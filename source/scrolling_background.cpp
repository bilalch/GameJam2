#include "scrolling_background.h"
#include "observer.h"

ScrollingBackground::ScrollingBackground(CIw2DImage* image, int lanes)
{
	m_image = image;	// shallow copy
	m_lanes = lanes;

	multiplier = OBSERVER->getDeviceHeight()/image->GetHeight();

	image1.m_width = image->GetWidth()*multiplier;
	image1.m_height = image->GetHeight()*multiplier;
	image1.m_x1 = 0;
	image1.m_y1 = 0;
	image1.m_x2 = image1.m_x1 + image1.m_width;
	image1.m_y2 = image1.m_y1 + image1.m_height;

	image2.m_width = image->GetWidth()*multiplier;
	image2.m_height = image->GetHeight()*multiplier;
	image2.m_x1 = image1.m_x2;
	image2.m_y1 = 0;
	image2.m_x2 = image2.m_x1 + image2.m_width;
	image2.m_y2 = image2.m_y1 + image2.m_height;

	initializeLaneBounds();

	m_speed = 10;
	m_worldAngle = 0;
}

ScrollingBackground::~ScrollingBackground()
{

}

void ScrollingBackground::initializeLaneBounds()
{
	if ( m_lanes == 3 ) {
		
		m_left_bound = image1.m_x1 + (image1.m_width - image1.m_width*THREE_LANE_RATIO)/2;
		m_right_bound = m_left_bound + image1.m_width*THREE_LANE_RATIO;
	}
}

void ScrollingBackground::Update(float speed)
{
	if ( OBSERVER->getAccelerometerX() > 30 ) {
		if ( m_speed < 15 )
			m_speed++;
		m_worldAngle = 45;
	} else if ( OBSERVER->getAccelerometerX() < 30 ) {
		if ( m_speed > 5 )
			m_speed--;
		m_worldAngle = -45;
	}
	speed = m_speed;

	image1.m_x1 = image1.m_x1 - speed*multiplier;
	image1.m_x2 = image1.m_x2 - speed*multiplier;

	image2.m_x1 = image2.m_x1 - speed*multiplier;
	image2.m_x2 = image2.m_x2 - speed*multiplier;

	//if ( image1.m_x1 < -(OBSERVER -> getDeviceWidth()) ) {
	if ( image1.m_x2 < 0 ) {

		image1.m_x1 = image2.m_x1 + image1.m_width;
		image1.m_x2 = image1.m_x1 + image1.m_width;
	//} else if ( image2.m_x1 < -(OBSERVER -> getDeviceWidth()) ) {
		} else if ( image2.m_x2 < 0 ) {
		
		image2.m_x1 = image1.m_x1 + image2.m_width;
		image2.m_x2 = image2.m_x1 + image2.m_width;
	}
}

void ScrollingBackground::Draw()
{
	Iw2DDrawImage(m_image,CIwSVec2(image1.m_x1,image1.m_y1),CIwSVec2(image1.m_width,image1.m_height));
	Iw2DDrawImage(m_image,CIwSVec2(image2.m_x1,image2.m_y1),CIwSVec2(image2.m_width,image2.m_height));
}