/*
 *
 */

#ifndef MENU_H
#define MENU_H

#include "view.h"
#include "AwmButton.h"

enum MenuState
{
	MENU_MAIN,
	MENU_ABOUT_US,
};

class Menu : public View
{
public:
	Menu();
	~Menu();
	int update(sliderStruct &m_slider);
	void draw();
	int click(float x, float y);

	void drawBackgroundStretched();
	void drawImageCentered(CIw2DImage* image);
	
	void loadMenuImages();
	void unloadMenuImages();

	void initializeButtons();
private:

	CIwResGroup* imagesGroup;

	CIw2DImage* m_background;
	CIw2DImage* m_title;
	CIw2DImage* m_run_pressed, *m_run_unpressed;
	CIw2DImage* m_credits_pressed, *m_credits_unpressed;
	CIw2DImage* m_sound_on, *m_sound_off;
	CIw2DImage* m_names;
	CIw2DImage* m_back_pressed, *m_back_unpressed;

	AwmButton* m_runButton;
	AwmButton* m_soundButton;
	AwmButton* m_creditsButton;
	AwmButton* m_backButton;
	
	MenuState m_menuState;
};

#endif