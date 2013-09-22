#include "gameover.h"

GameOver::GameOver()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/GameOver/_gameover.group");

	m_background = Iw2DCreateImageResource("background");
	m_gameOver = Iw2DCreateImageResource("game-over");
}

GameOver::~GameOver()
{
	if ( m_background )
		delete m_background;
	m_background = NULL;

	if ( m_gameOver )
		delete m_gameOver;
	m_gameOver = NULL;

	IwGetResManager()->DestroyGroup(imagesGroup);
}

int GameOver::update()
{
	return 1;
}

void GameOver::draw()
{
	Iw2DDrawImage(m_background,CIwFVec2(0,0),CIwFVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()));
	Iw2DDrawImage(m_gameOver,CIwFVec2((OBSERVER->getDeviceWidth()-m_gameOver->GetWidth())/2,(OBSERVER->getDeviceWidth()-m_gameOver->GetWidth())/2));
}

int GameOver::click(float x, float y)
{
	return -1;
}