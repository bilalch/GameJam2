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

enum GameState
{
	GAME_MENU,
	GAME_ARCADE,
	GAME_LEVEL_1
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

	Menu* m_menu;
	Arcade* m_arcade;
//	touchStruct[S3E_POINTER_TOUCH_MAX];
	GameState m_gameState;

};

#endif