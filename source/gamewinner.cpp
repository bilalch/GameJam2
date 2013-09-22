#include "gamewinner.h"

GameWinner::GameWinner()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/Winner/_winner.group");

	m_background = Iw2DCreateImageResource("background");
	m_gameWinner = Iw2DCreateImageResource("winning-text");
	m_boyWithChicken = Iw2DCreateImageResource("boy-with-chicken");
}

GameWinner::~GameWinner()
{
	if ( m_background )
		delete m_background;
	m_background = NULL;

	if ( m_gameWinner )
		delete m_gameWinner;
	m_gameWinner = NULL;

	if ( m_boyWithChicken )
		delete m_boyWithChicken;
	m_boyWithChicken = NULL;

	IwGetResManager()->DestroyGroup(imagesGroup);
}

int GameWinner::update()
{
	return 1;
}

void GameWinner::draw()
{
	Iw2DDrawImage(m_background,CIwFVec2(0,0),CIwFVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()));
	Iw2DDrawImage(m_gameWinner,CIwFVec2((OBSERVER->getDeviceWidth()-m_gameWinner->GetWidth())/2 + 130,(OBSERVER->getDeviceHeight()-m_gameWinner->GetHeight())/2));
	Iw2DDrawImage(m_boyWithChicken,CIwFVec2((OBSERVER->getDeviceWidth()-m_boyWithChicken->GetWidth())/2 - 200,(OBSERVER->getDeviceHeight()-m_boyWithChicken->GetHeight())/2));

}

int GameWinner::click(float x, float y)
{
	return -1;
}