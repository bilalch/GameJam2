#ifndef GAMEWINNER_H
#define GAMEWINNER_H

#include "observer.h"

class GameWinner {
public:
	GameWinner();
	~GameWinner();

	int update();
	void draw();

	int click(float x, float y);

private:

	CIwResGroup* imagesGroup;

	CIw2DImage* m_background;
	CIw2DImage* m_gameWinner;
	CIw2DImage* m_boyWithChicken;
};

#endif //GAMEWINNER