#include "scrolling_background.h"
#include "observer.h"

ScrollingBackground::ScrollingBackground(CIw2DImage* image, int lanes)
{
	m_image = image;	// shallow copy
	m_lanes = lanes;

	m_tile1 = Iw2DCreateImageResource("tile1");
	m_tile2 = Iw2DCreateImageResource("tile2");
	m_tile3 = Iw2DCreateImageResource("tile3");

	m_bg = Iw2DCreateImageResource("menu");

	m_path = Iw2DCreateImageResource("path");

	multiplier = OBSERVER->getDeviceHeight()/image->GetHeight();

	path1.m_width = m_path->GetWidth();
	path1.m_height = m_path->GetHeight();
	path1.m_x1 = 0;
	path1.m_y1 = OBSERVER->getDeviceHeight() - path1.m_height;
	path1.m_x2 = path1.m_x1 + path1.m_width;
	path1.m_y2 = path1.m_y1 + path1.m_height;

	path2.m_width = m_path->GetWidth();
	path2.m_height = m_path->GetHeight();
	path2.m_x1 = path1.m_x2;
	path2.m_y1 = OBSERVER->getDeviceHeight() - path2.m_height;
	path2.m_x2 = path2.m_x1 + path2.m_width;
	path2.m_y2 = path2.m_y1 + path2.m_height;

	image1.m_width = m_image->GetWidth();
	image1.m_height = m_image->GetHeight();
	image1.m_x1 = 0;
	image1.m_y1 = OBSERVER->getDeviceHeight() - image1.m_height - path1.m_height;
	image1.m_x2 = image1.m_x1 + image1.m_width;
	image1.m_y2 = image1.m_y1 + image1.m_height;

	image2.m_width = m_image->GetWidth();
	image2.m_height = m_image->GetHeight();
	image2.m_x1 = image1.m_x2;
	image2.m_y1 = OBSERVER->getDeviceHeight() - image2.m_height - path1.m_height;
	image2.m_x2 = image2.m_x1 + image2.m_width;
	image2.m_y2 = image2.m_y1 + image2.m_height;

	initializeLaneBounds();

	m_speed = 11;
	m_worldAngle = 0;

	leftMostTile = 0;
	leftMostTile_x1 = 0;
	tileWidth = 48;

	centerTile = 10;
	centerTile_x1 = 9*tileWidth;

	m_levelGenerator = new LevelGenerator(1);
	m_levelGenerator->Generate();

	tileCount = 0;

	scale = 1;
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

void ScrollingBackground::Update()
{
	//ScrollTile();
	if ( OBSERVER->getAccelerometerX() > 30 ) {
		if ( m_speed < 15 )
			m_speed++;
		m_worldAngle = 45;
	} else if ( OBSERVER->getAccelerometerX() < -30 ) {
		if ( m_speed > 5 )
			m_speed--;
		m_worldAngle = -45;
	} else {
		//m_speed = 10;
	}

	path1.m_x1 = path1.m_x1 - m_speed*multiplier;
	path1.m_x2 = path1.m_x2 - m_speed*multiplier;

	path2.m_x1 = path2.m_x1 - m_speed*multiplier;
	path2.m_x2 = path2.m_x2 - m_speed*multiplier;

	//if ( image1.m_x1 < -(OBSERVER -> getDeviceWidth()) ) {
	if ( path1.m_x2 < 0 ) {

		path1.m_x1 = path2.m_x1 + path1.m_width;
		path1.m_x2 = path1.m_x1 + path1.m_width;
	//} else if ( image2.m_x1 < -(OBSERVER -> getDeviceWidth()) ) {
		} else if ( path2.m_x2 < 0 ) {
		
		path2.m_x1 = path1.m_x1 + path2.m_width;
		path2.m_x2 = path2.m_x1 + path2.m_width;
	}

	image1.m_x1 = image1.m_x1 - m_speed*multiplier;
	image1.m_x2 = image1.m_x2 - m_speed*multiplier;

	image2.m_x1 = image2.m_x1 - m_speed*multiplier;
	image2.m_x2 = image2.m_x2 - m_speed*multiplier;

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

void ScrollingBackground::ScrollTile()
{
	tileCount++;
	centerTile_x1-= tileWidth/4;
	if ( tileCount == 4 ) {
		tileCount = 0;
		centerTile++;
		centerTile_x1 = 9*tileWidth;
	}
}

float ScrollingBackground::getScrollSpeed()
{
	return m_speed*multiplier;
}

int ScrollingBackground::click(float x, float y)
{
	if (scale == 1)
		scale = 0.5;
	else
		scale = 1;
	return 0;
}

void ScrollingBackground::Draw()
{
	Iw2DDrawImage(m_bg,CIwFVec2(0,0),CIwFVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()));
	Iw2DDrawImage(m_path,CIwFVec2(path1.m_x1,path1.m_y1),CIwFVec2(path1.m_width,path1.m_height));
	Iw2DDrawImage(m_path,CIwFVec2(path2.m_x1,path2.m_y1),CIwFVec2(path2.m_width,path2.m_height));
	Iw2DDrawImage(m_image,CIwFVec2(image1.m_x1,image1.m_y1),CIwFVec2(image1.m_width,image1.m_height));
	Iw2DDrawImage(m_image,CIwFVec2(image2.m_x1,image2.m_y1),CIwFVec2(image2.m_width,image2.m_height));
/*	int m_x1 = centerTile_x1;

	for ( int i = centerTile; i > centerTile - 20; i--  ) {

		if ( m_levelGenerator->getTypeAtIndex(i) == 1 ) {
			Iw2DDrawImage(m_tile1,CIwFVec2(m_x1,592),CIwFVec2(tileWidth*scale,tileWidth*scale));
		} else if ( m_levelGenerator->getTypeAtIndex(i) == 2 ) {
			Iw2DDrawImage(m_tile2,CIwFVec2(m_x1,592),CIwFVec2(tileWidth*scale,tileWidth*scale));
		} else if ( m_levelGenerator->getTypeAtIndex(i) == 3 ) {
			Iw2DDrawImage(m_tile3,CIwFVec2(m_x1,592),CIwFVec2(tileWidth*scale,tileWidth*scale));
		}

		m_x1-=tileWidth*scale;
	}

	m_x1 = centerTile_x1;

	for ( int i = centerTile; i < centerTile + 20; i++  ) {

		if ( m_levelGenerator->getTypeAtIndex(i) == 1 ) {
			Iw2DDrawImage(m_tile1,CIwFVec2(m_x1,592),CIwFVec2(tileWidth*scale,tileWidth*scale));
		} else if ( m_levelGenerator->getTypeAtIndex(i) == 2 ) {
			Iw2DDrawImage(m_tile2,CIwFVec2(m_x1,592),CIwFVec2(tileWidth*scale,tileWidth*scale));
		} else if ( m_levelGenerator->getTypeAtIndex(i) == 3 ) {
			Iw2DDrawImage(m_tile3,CIwFVec2(m_x1,592),CIwFVec2(tileWidth*scale,tileWidth*scale));
		}

		m_x1+=tileWidth*scale;
	}*/
}

float ScrollingBackground::getSpeed()
{
	return m_speed;
}