#ifndef LEVEL_SELECTION_H
#define LEVEL_SELECTION_H

#include "observer.h"
#include "view.h"
#include "AwmButton.h"

class LevelSelection : public View
{
public:
	LevelSelection();
	~LevelSelection();

	int update(sliderStruct &m_slider);
	void draw();

	int click(float x, float y);

private:
	CIwResGroup* imagesGroup;

	CIw2DImage* m_background;
	CIw2DImage* m_button;

	AwmButton *m_level1;
	AwmButton *m_level2;
	AwmButton *m_level3;
	AwmButton *m_level4;
};

#endif //LEVEL_SELECTION_H