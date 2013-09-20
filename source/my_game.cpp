#include "my_game.h"

MyGame::MyGame()
{
	m_menu = new Menu();
	m_gameState = GAME_MENU;

	m_arcade = NULL;
}

MyGame::~MyGame()
{
	if ( m_menu )
		delete m_menu;
	m_menu = NULL;
}

void MyGame::Update()
{
	if ( getSound() )
		IwGetSoundManager() -> Update();

	switch (m_gameState)
	{
	case GAME_MENU:
		if ( m_menu ) {

			m_menu -> update(getSliderStruct());
		} else {
			
			m_menu = new Menu();
			m_menu -> update(getSliderStruct());
		}
		break;

	case GAME_ARCADE:
		if ( m_arcade ) {

			m_arcade -> update(getSliderStruct());
		} else {
			
			m_arcade = new Arcade();
			m_arcade -> update(getSliderStruct());
		}
		break;

	default:
		break;
	};
}

void MyGame::Draw()
{
	switch (m_gameState)
	{
	case GAME_MENU:
		if ( m_menu )
			m_menu -> draw();
		else {
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE,"trying to draw menu when it does not exist");
			s3eDeviceExit();
		}
		break;

	case GAME_ARCADE:
		if ( m_arcade )
			m_arcade -> draw();
		else {
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE,"trying to draw arcade when it does not exist");
			s3eDeviceExit();
		}
		break;
	};
}

void MyGame::Clicker(s3ePointerTouchEvent* event)
{
	int variance = 30;
	if(event->m_Pressed)
	{
		m_slider.click = true;
		m_slider.pressed = true;
		m_slider.distanceX1 = event->m_x;
		m_slider.distanceY1 = event->m_y;
		m_slider.moveX1 = event->m_x;
		m_slider.timeX1 = s3eTimerGetMs();
		m_slider.moveY1  = event->m_y;
	}
	else
	{
		switch(m_gameState)
		{
		case GAME_MENU:
			parseGameMenuClick(m_menu->click(event->m_x,event->m_y));
//			m_menu -> click (event -> m_x, event -> m_y);
			break;


		default:
			break;
		};
		m_slider.click = false;
		m_slider.pressed = false;
		m_slider.right = false;
		m_slider.left = false;
		m_slider.down = false;
		m_slider.up = false;
	}
}

void MyGame::Clicker(float x, float y)
{
	switch(m_gameState)
	{
	case GAME_MENU:
		parseGameMenuClick(m_menu->click(x,y));
		break;

	default:
		break;
	};
}

void MyGame::parseGameMenuClick(int number)
{
	switch(number)
	{
	case -1:
		if ( m_menu )
			delete m_menu;
		m_menu = NULL;
		m_gameState = GAME_ARCADE;
		break;

	default:
		break;
	};
}