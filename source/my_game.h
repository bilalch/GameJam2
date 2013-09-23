/*
 *	This class is the base class for my game
 *	It inherits from game.h which wraps the
 *	basic functionality needed by a game
 *
 */

#ifndef MY_GAME_H
#define MY_GAME_H

#include "game.h"
#include "menu.h"
#include "arcade.h"
#include "gameover.h"
#include "gamewinner.h"
#include "level_selection.h"
#include "story.h"

enum GameState
{
	GAME_MENU,
	GAME_ARCADE,
	GAME_LEVEL_1,
	GAME_OVER,
	GAME_WINNER,
	GAME_STORY,
	GAME_LEVEL_SELECTION,
};

class MyGame : public Game
{
public:
	MyGame();
	~MyGame();

	void Draw();
	void Update();

	void Clicker(s3ePointerTouchEvent* event);
	void Clicker(float x, float y);
private:
	void parseGameMenuClick(int number);
	void parseGameOverClick(int number);
	void parseGameWinnerClick(int number);
	void parseStoryClick(int number);
	void parseLevelSelectionClick(int number);

	Menu* m_menu;
	Arcade* m_arcade;
	GameOver* m_gameOver;
	GameWinner* m_gameWinner;
	Story* m_story;
	LevelSelection* m_level_selection;

//	touchStruct[S3E_POINTER_TOUCH_MAX];
	GameState m_gameState;
	
	int arcade_difficulty_level;
	int game_over_case;
};

#endif