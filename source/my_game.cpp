#include "my_game.h"

MyGame::MyGame()
{
	m_menu = NULL;
	m_arcade = NULL;
	m_gameOver = NULL;
	m_gameWinner = NULL;
	m_story = NULL;
	m_level_selection = NULL;

	m_menu = new Menu();
	m_gameState = GAME_MENU;
	
	s3eAccelerometerStart();
}

MyGame::~MyGame()
{
	if ( m_menu )
		delete m_menu;
	m_menu = NULL;

	if (m_gameOver)
		delete m_gameOver;
	m_gameOver = NULL;

	if (m_gameWinner)
		delete m_gameWinner;
	m_gameWinner = NULL;

	if (m_story)
		delete m_story;
	m_story = NULL;

	if (m_level_selection)
		delete m_level_selection;
	m_level_selection = NULL;
}

void MyGame::Update()
{
	OBSERVER->setAccelerometerX( s3eAccelerometerGetX() );
	OBSERVER->setAccelerometerY( s3eAccelerometerGetY() );
	OBSERVER->setAccelerometerZ( s3eAccelerometerGetZ() );
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
		{
			int ret = 0;
			if ( m_arcade ) {

				ret = m_arcade -> update(getSliderStruct());
			} else {

				m_arcade = new Arcade();
				ret = m_arcade -> update(getSliderStruct());
			}
			switch (ret)
			{
			case 1:
				if ( m_arcade )
					delete m_arcade;
				m_arcade = NULL;

				m_gameState = GAME_WINNER;
				m_gameWinner = new GameWinner();
				break;
			case 2:
				if ( m_arcade )
					delete m_arcade;
				m_arcade = NULL;

				m_gameState = GAME_OVER;
				m_gameOver = new GameOver();
				break;
			default:
				break;
			}
		}
		break;

	case GAME_OVER:
		if ( m_gameOver ) {

			m_gameOver -> update();
		} else {
			
			m_gameOver = new GameOver();
			m_gameOver -> update();
		}
		break;

	case GAME_WINNER:
		if ( m_gameWinner ) {

			m_gameWinner -> update();
		} else {
			
			m_gameWinner = new GameWinner();
			m_gameWinner -> update();
		}
		break;

	case GAME_STORY:
		if ( m_story ) {

			m_story -> update();
		} else {

			m_story = new Story();
			m_story -> update();
		}
		break;

	case GAME_LEVEL_SELECTION:
		if ( m_level_selection ) {

			m_level_selection -> update(getSliderStruct());
		} else {

			m_level_selection = new LevelSelection();
			m_level_selection -> update(getSliderStruct());
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

	case GAME_OVER:
		if ( m_gameOver )
			m_gameOver -> draw();
		else {
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE,"trying to draw game over when it does not exist");
			s3eDeviceExit();
		}
		break;

	case GAME_WINNER:
		if ( m_gameWinner )
			m_gameWinner -> draw();
		else {
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE,"trying to draw game winner when it does not exist");
			s3eDeviceExit();
		}
		break;

	case GAME_STORY:
		if ( m_story )
			m_story -> draw();
		else {
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE,"trying to draw story when it does not exist");
			s3eDeviceExit();
		}
		break;

	case GAME_LEVEL_SELECTION:
		if ( m_level_selection )
			m_level_selection -> draw();
		else {
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE,"trying to draw level selection when it does not exist");
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
		case GAME_ARCADE:
			m_arcade->click(event->m_x,event->m_y);
			break;

		case GAME_OVER:
			parseGameOverClick(m_gameOver->click(event->m_x,event->m_y));
			break;

		case GAME_WINNER:
			parseGameWinnerClick(m_gameWinner->click(event->m_x,event->m_y));
			break;

		case GAME_STORY:
			parseStoryClick(m_story->click(event->m_x,event->m_y));
			break;

		case GAME_LEVEL_SELECTION:
			parseLevelSelectionClick(m_level_selection->click(event->m_x,event->m_y));
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

	case GAME_ARCADE:
		m_arcade->click(x,y);
		break;

	case GAME_OVER:
		parseGameOverClick(m_gameOver->click(x,y));
		break;

	case GAME_WINNER:
		parseGameWinnerClick(m_gameWinner->click(x,y));
		break;

	case GAME_STORY:
		parseStoryClick(m_story->click(x,y));
		break;

	case GAME_LEVEL_SELECTION:
		parseLevelSelectionClick(m_level_selection->click(x,y));
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
		m_gameState = GAME_LEVEL_SELECTION;
		break;

	default:
		break;
	};
}

void MyGame::parseGameOverClick(int number)
{
	switch(number)
	{
	case -1:
		if ( m_gameOver )
			delete m_gameOver;
		m_gameOver = NULL;
		m_gameState = GAME_MENU;
		break;

	default:
		break;
	};
}

void MyGame::parseGameWinnerClick(int number)
{
	switch(number)
	{
	case -1:
		if ( m_gameWinner )
			delete m_gameWinner;
		m_gameWinner = NULL;
		m_gameState = GAME_MENU;
		break;

	default:
		break;
	};
}

void MyGame::parseStoryClick(int number)
{
	switch(number)
	{
	case -1:
		if ( m_story )
			delete m_story;
		m_story = NULL;
		m_gameState = GAME_ARCADE;
		break;

	default:
		break;
	};
}

void MyGame::parseLevelSelectionClick(int number)
{
	switch(number)
	{
	case -1:
		if ( m_level_selection )
			delete m_level_selection;
		m_level_selection = NULL;
		m_gameState = GAME_STORY;
		break;

	case -2:
		if ( m_level_selection )
			delete m_level_selection;
		m_level_selection = NULL;
		m_gameState = GAME_ARCADE;
		break;

	case -3:
		if ( m_level_selection )
			delete m_level_selection;
		m_level_selection = NULL;
		m_gameState = GAME_ARCADE;
		break;

	case -4:
		if ( m_level_selection )
			delete m_level_selection;
		m_level_selection = NULL;
		m_gameState = GAME_ARCADE;
		break;

	default:
		break;
	};
}