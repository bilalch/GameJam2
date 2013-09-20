#include "menu.h"
#include "observer.h"

Menu::Menu()
{
	
	loadMenuImages();
	buttons_top_limit_multiplier = 0.3;
	buttons_side_limit_multiplier = 0.05;
	initializeButtons();
	m_menuState = MENU_MAIN;
}

Menu::~Menu()
{
	if ( m_storyButton )
		delete m_storyButton;

	if ( m_raceButton )
		delete m_raceButton;

	if ( m_highscoreButton )
		delete m_highscoreButton;

	if ( m_howtoButton )
		delete m_howtoButton;

	if ( m_aboutUsButton )
		delete m_aboutUsButton;

	unloadMenuImages();
}

void Menu::initializeButtons()
{
	float total_height_for_buttons = OBSERVER->getDeviceHeight()*(1-buttons_top_limit_multiplier);
	float button_height = m_storyButtonImage->GetHeight();
	float button_difference = (total_height_for_buttons - 4*button_height)/5;

	float button_x = buttons_side_limit_multiplier*OBSERVER->getDeviceWidth();

	float current_button_y = buttons_top_limit_multiplier*OBSERVER->getDeviceHeight() + button_difference;

	m_storyButton = new AwmButton(button_x, current_button_y, m_storyButtonImage);

	current_button_y = current_button_y + button_height + button_difference;

	m_raceButton = new AwmButton(button_x, current_button_y, m_raceButtonImage);

	current_button_y = current_button_y + button_height + button_difference;

	m_highscoreButton = new AwmButton(button_x,current_button_y,m_highscoreButtonImage);

	current_button_y = current_button_y + button_height + button_difference;

	m_howtoButton = new AwmButton(button_x,current_button_y,m_howtoButtonImage);

	m_aboutUsButton = new AwmButton(OBSERVER->getDeviceWidth() - m_aboutUsButtonImage->GetWidth() - button_x, OBSERVER->getDeviceHeight() - m_aboutUsButtonImage->GetHeight() - button_x, m_aboutUsButtonImage);

	m_aboutUsButton -> Slide ( -200, 0, 20 );
}

void Menu::loadMenuImages()
{
	imagesGroup = IwGetResManager()->LoadGroup("320x480/Menu/_menu.group");

	m_storyButtonImage = Iw2DCreateImageResource("button_story");
	m_raceButtonImage = Iw2DCreateImageResource("button_race");
	m_highscoreButtonImage = Iw2DCreateImageResource("button_highscore");
	m_howtoButtonImage = Iw2DCreateImageResource("button_howto");
	m_aboutUsButtonImage = Iw2DCreateImageResource("button_aboutus");

	m_about_us = Iw2DCreateImageResource("aboutUs");
	m_how_to = Iw2DCreateImageResource("howTo");
	m_background = Iw2DCreateImageResource("menu");
}

void Menu::unloadMenuImages()
{
	if ( m_storyButtonImage )
		delete m_storyButtonImage;
	m_storyButtonImage = NULL;

	if ( m_raceButtonImage )
		delete m_raceButtonImage;
	m_raceButtonImage = NULL;

	if ( m_highscoreButtonImage )
		delete m_highscoreButtonImage;
	m_highscoreButtonImage = NULL;

	if ( m_howtoButtonImage )
		delete m_howtoButtonImage;
	m_howtoButtonImage = NULL;

	if ( m_aboutUsButtonImage )
		delete m_aboutUsButtonImage;
	m_aboutUsButtonImage = NULL;

	if ( m_background )
		delete m_background;
	m_background = NULL;	

	if ( m_about_us )
		delete m_about_us;
	m_about_us = NULL;	

	if ( m_how_to )
		delete m_how_to;
	m_how_to = NULL;	

	IwGetResManager()->DestroyGroup(imagesGroup);
}

bool Menu::update(sliderStruct &m_slider)
{
	m_storyButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
	//m_raceButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
	m_raceButton -> Update();
	m_highscoreButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
	m_howtoButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
	m_aboutUsButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);

	return true;
}

void Menu::drawSwipes()
{
	if ( AWM_INPUT -> getSwipe() ) {
		
		if ( AWM_INPUT -> getSwipeRight() ) {
			
			Iw2DDrawString("SWIPE RIGHT",CIwSVec2(0,0),CIwSVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
		} else if ( AWM_INPUT -> getSwipeLeft() ) {
			
			Iw2DDrawString("SWIPE LEFT",CIwSVec2(0,0),CIwSVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
		} else if ( AWM_INPUT -> getSwipeUp() ) {
		
			Iw2DDrawString("SWIPE UP",CIwSVec2(0,0),CIwSVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
		} else if ( AWM_INPUT -> getSwipeDown() ) {
		
			Iw2DDrawString("SWIPE DOWN",CIwSVec2(0,0),CIwSVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
		}
	}
}

void Menu::draw()
{
	drawBackgroundStretched();

	m_storyButton -> Draw();
	m_raceButton -> Draw();
	m_highscoreButton -> Draw();
	m_howtoButton -> Draw();
	m_aboutUsButton -> Draw();

	drawSwipes();

	switch ( m_menuState )
	{
	case MENU_MAIN:
		break;

	case MENU_ABOUT_US:

		drawScreenBelowLogo(m_about_us);
		break;

	case MENU_HOW_TO:

		drawScreenBelowLogo(m_how_to);
		break;

	default:
		break;
	};
}

void Menu::drawBackgroundStretched()
{
	Iw2DDrawImage(m_background,CIwSVec2(0,0),CIwSVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()));
}

void Menu::drawImageCentered(CIw2DImage* image)
{
	float drawX = (OBSERVER->getDeviceWidth() - image->GetWidth())/2;
	float drawY = (OBSERVER->getDeviceHeight() - image->GetHeight())/2;

	Iw2DDrawImage(image,CIwSVec2(drawX,drawY));
}

void Menu::drawScreenBelowLogo(CIw2DImage* image)
{
	float drawX = (OBSERVER->getDeviceWidth() - image->GetWidth())/2;
	float drawY = buttons_top_limit_multiplier*OBSERVER->getDeviceHeight() + ((1 - buttons_top_limit_multiplier)*OBSERVER->getDeviceHeight() - image->GetHeight())/2;

	Iw2DDrawImage(image,CIwSVec2(drawX,drawY));
}

int Menu::click(float x, float y)
{
	switch ( m_menuState )
	{
	case MENU_MAIN:

		m_storyButton -> Click (x,y);
		m_highscoreButton -> Click (x,y);

		if ( m_raceButton -> Click (x,y) ) {
		
			return -1;
		} else if ( m_howtoButton -> Click (x,y) ) {
		
			hideMainMenuButtons();
			m_menuState = MENU_HOW_TO;
		} else if ( m_aboutUsButton -> Click (x,y) ) {
		
			hideMainMenuButtons();
			m_menuState = MENU_ABOUT_US;
		}
		break;

	case MENU_ABOUT_US:

		showMainMenuButtons();
		m_menuState = MENU_MAIN;
		break;

	case MENU_HOW_TO:

		showMainMenuButtons();
		m_menuState = MENU_MAIN;
		break;

	default:
		break;
	};
	
	return 0;
}

void Menu::hideMainMenuButtons()
{
	m_storyButton -> hide();
	m_raceButton -> hide();
	m_highscoreButton -> hide();
	m_howtoButton -> hide();
	m_aboutUsButton -> hide();
}

void Menu::showMainMenuButtons()
{
	m_storyButton -> show();
	m_raceButton -> show();
	m_highscoreButton -> show();
	m_howtoButton -> show();
	m_aboutUsButton -> show();
}