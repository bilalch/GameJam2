#include "level_selection.h"

LevelSelection::LevelSelection()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/Story/_story.group");

	m_background = Iw2DCreateImageResource("background");
}

LevelSelection::~LevelSelection()
{

}

int LevelSelection::update()
{
	m_level1->Update();
	m_level2->Update();
	m_level3->Update();
	m_level4->Update();
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