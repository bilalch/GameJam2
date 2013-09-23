#include "gameover.h"

GameOver::GameOver(int reason)
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/GameOver/_gameover.group");

	m_background = Iw2DCreateImageResource("background");
	m_gameOver = Iw2DCreateImageResource("game-over");

	case_game_over = reason;
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

	switch (case_game_over){

	case 1:
		Iw2DDrawString("Too slow for lift off",CIwFVec2(OBSERVER->getDeviceWidth()/2 - 100,100),CIwFVec2(200,50),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
		break;
	case 2:
		Iw2DDrawString("Mud Collision",CIwFVec2(OBSERVER->getDeviceWidth()/2 - 100,100),CIwFVec2(200,50),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
		break;
	case 3:
		Iw2DDrawString("Box Collision",CIwFVec2(OBSERVER->getDeviceWidth()/2 - 100,100),CIwFVec2(200,50),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
		break;

	default:
		break;
	};
}

int GameOver::click(float x, float y)
{
	return -1;
}