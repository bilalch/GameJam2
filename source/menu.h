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
	MENU_HOW_TO,
};

class Menu : public View
{
public:
	Menu();
	~Menu();
	bool update(sliderStruct &m_slider);
	void draw();
	int click(float x, float y);

	void drawBackgroundStretched();
	void drawImageCentered(CIw2DImage* image);
	void drawScreenBelowLogo(CIw2DImage* image);

	void loadMenuImages();
	void unloadMenuImages();

	void initializeButtons();

	void hideMainMenuButtons();
	void showMainMenuButtons();

	void drawSwipes();

private:
	float multiplier;
	float buttons_top_limit_multiplier;			// multiply this with screen height to get
												// where the buttons should start from

	float buttons_side_limit_multiplier;		// multiply this with screen width to get the
												// spacing of buttons from horizontal boundaries

	CIwResGroup* imagesGroup;

	CIw2DImage* m_background;
	CIw2DImage* m_about_us;
	CIw2DImage* m_how_to;


	CIw2DImage* m_storyButtonImage;
	CIw2DImage* m_raceButtonImage;
	CIw2DImage* m_highscoreButtonImage;
	CIw2DImage* m_howtoButtonImage;
	CIw2DImage* m_aboutUsButtonImage;

	AwmButton* m_storyButton;
	AwmButton* m_raceButton;
	AwmButton* m_highscoreButton;
	AwmButton* m_howtoButton;
	AwmButton* m_aboutUsButton;

	MenuState m_menuState;

};

#endif