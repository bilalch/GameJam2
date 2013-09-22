#ifndef STORY_SCREEN_H
#define STORY_SCREEN_H

#include "observer.h"

class Story
{
public:
	Story();
	~Story();
	
	int update();
	void draw();

private:

	CIwResGroup* imagesGroup;

	CIw2DImage* m_background;
	CIw2DImage* m_dialog;
	CIw2DImage* m_chotu;
};

#endif //STORY_SCREEN_H