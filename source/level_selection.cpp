#include "level_selection.h"

LevelSelection::LevelSelection()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/Story/_story.group");

	m_background = Iw2DCreateImageResource("background");
}

LevelSelection::~LevelSelection()
{

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
}

int LevelSelection::click(float x, float y)
{
	return -1;
}