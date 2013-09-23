#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "observer.h"

class GameOver {
public:
	GameOver(int);
	~GameOver();

	int update();
	void draw();

	int click(float x, float y);

private:

	CIwResGroup* imagesGroup;

	CIw2DImage* m_background;
	CIw2DImage* m_gameOver;

	int case_game_over;
};

#endif //GAMEOVER