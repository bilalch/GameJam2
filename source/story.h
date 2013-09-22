#ifndef STORY_SCREEN_H
#define STORY_SCREEN_H

#include "observer.h"
#include "spine_char.h"

class Story
{
public:
	Story();
	~Story();
	
	int update();
	void draw();

	int click(float x, float y);

private:

	CIwResGroup* imagesGroup;

	CIw2DImage* m_background;
	CIw2DImage* m_dialog;

	SpineChar* m_boy;
};

#endif //STORY_SCREEN_H