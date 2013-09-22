#include "level_selection.h"

LevelSelection::LevelSelection()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/Story/_story.group");

	m_background = Iw2DCreateImageResource("background");
	m_button = Iw2DCreateImageResource("button");

	m_level1 = new AwmButton(m_button,m_button,(OBSERVER->getDeviceWidth() - m_button->GetWidth())/2, 100);
	m_level2 = new AwmButton(m_button,m_button,(OBSERVER->getDeviceWidth() - m_button->GetWidth())/2, 200);
	m_level3 = new AwmButton(m_button,m_button,(OBSERVER->getDeviceWidth() - m_button->GetWidth())/2, 300);
	m_level4 = new AwmButton(m_button,m_button,(OBSERVER->getDeviceWidth() - m_button->GetWidth())/2, 400);
}

LevelSelection::~LevelSelection()
{
	if ( m_level1 )
		delete m_level1;
	if ( m_level2 )
		delete m_level2;
	if ( m_level3 )
		delete m_level3;
	if ( m_level4 )
		delete m_level4;

	if ( m_button )
		delete m_button ;
	m_button = NULL;

	if ( m_background )
		delete m_background ;
	m_background = NULL;

	IwGetResManager()->DestroyGroup(imagesGroup);
}

int LevelSelection::update(sliderStruct &m_slider)
{
	m_level1->Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
	m_level2->Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
	m_level3->Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
	m_level4->Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);

	return 1;
}

void LevelSelection::draw()
{
	Iw2DDrawImage(m_background,CIwFVec2(0,0),CIwFVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()));

	m_level1->Draw();
	m_level2->Draw();
	m_level3->Draw();
	m_level4->Draw();

	Iw2DDrawString("Level 1",CIwFVec2((OBSERVER->getDeviceWidth() - m_button->GetWidth())/2,100),CIwFVec2(m_button->GetWidth(),m_button->GetHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
	Iw2DDrawString("Level 2",CIwFVec2((OBSERVER->getDeviceWidth() - m_button->GetWidth())/2,200),CIwFVec2(m_button->GetWidth(),m_button->GetHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
	Iw2DDrawString("Level 3",CIwFVec2((OBSERVER->getDeviceWidth() - m_button->GetWidth())/2,300),CIwFVec2(m_button->GetWidth(),m_button->GetHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
	Iw2DDrawString("Level 4",CIwFVec2((OBSERVER->getDeviceWidth() - m_button->GetWidth())/2,400),CIwFVec2(m_button->GetWidth(),m_button->GetHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
}

int LevelSelection::click(float x, float y)
{

	if ( m_level1 -> Click (x,y) ) {

		return -1;
	}
	if ( m_level2 -> Click (x,y) ) {

		return -2;
	}
	if ( m_level3 -> Click (x,y) ) {

		return -3;
	}
	if ( m_level4 -> Click (x,y) ) {

		return -4;
	}
	return 0;
}