#include "menu.h"
#include "observer.h"

Menu::Menu()
{
	
	loadMenuImages();
	initializeButtons();
	m_menuState = MENU_MAIN;
}

Menu::~Menu()
{
	if ( m_runButton )
		delete m_runButton;

	if ( m_creditsButton )
		delete m_creditsButton;

	if ( m_soundButton )
		delete m_soundButton;

	if ( m_backButton )
		delete m_backButton;

	unloadMenuImages();
}

void Menu::initializeButtons()
{
	m_runButton = new AwmButton(m_run_unpressed,m_run_pressed,(OBSERVER->getDeviceWidth() - m_run_pressed->GetWidth())/2,((OBSERVER->getDeviceHeight() - m_run_pressed->GetHeight())/2)+50);
	m_creditsButton = new AwmButton(m_credits_unpressed,m_credits_pressed, (OBSERVER->getDeviceWidth()*0.5 + 200), 500 );
	m_soundButton = new AwmButton (m_sound_off,m_sound_on,(OBSERVER->getDeviceWidth()*0.5 - 350), 500);
	m_backButton = new AwmButton (m_back_unpressed,m_back_pressed,(OBSERVER->getDeviceWidth()*0.5 - 350), 500);
}

void Menu::loadMenuImages()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/Menu/_menu.group");

	m_background = Iw2DCreateImageResource("background");
	m_title = Iw2DCreateImageResource("game-name");
	m_run_pressed = Iw2DCreateImageResource("run-pressed");
	m_run_unpressed = Iw2DCreateImageResource("run-unpressed");
	m_credits_pressed = Iw2DCreateImageResource("credit-pressed");
	m_credits_unpressed = Iw2DCreateImageResource("credit-unpressed");
	m_sound_on = Iw2DCreateImageResource("sound-on");
	m_sound_off = Iw2DCreateImageResource("sound-off");
	m_names = Iw2DCreateImageResource("names");
	m_back_pressed = Iw2DCreateImageResource("back-button-pressed");
	m_back_unpressed = Iw2DCreateImageResource("back-button-unpressed");

}

void Menu::unloadMenuImages()
{
	if ( m_background )
		delete m_background;
	m_background = NULL;

	if ( m_title )
		delete m_title;
	m_title = NULL;

	if ( m_run_unpressed)
		delete m_run_unpressed;
	m_run_unpressed = NULL;

	if ( m_run_pressed )
		delete m_run_pressed;
	m_run_pressed = NULL;

	if ( m_credits_pressed )
		delete m_credits_pressed;
	m_credits_pressed = NULL;

	if ( m_credits_unpressed )
		delete m_credits_unpressed;
	m_credits_unpressed = NULL;	

	if ( m_sound_on )
		delete m_sound_on;
	m_sound_on = NULL;	

	if ( m_sound_off )
		delete m_sound_off;
	m_sound_off = NULL;

	if ( m_names )
		delete m_names;
	m_names = NULL;

	if ( m_back_pressed )
		delete m_back_pressed;
	m_back_pressed = NULL;

	if ( m_back_unpressed )
		delete m_back_unpressed ;
	m_back_unpressed  = NULL;

	IwGetResManager()->DestroyGroup(imagesGroup);
}

int Menu::update(sliderStruct &m_slider)
{
	switch ( m_menuState )
	{
	case MENU_MAIN:
		m_runButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
		m_creditsButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
		m_soundButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
		break;

	case MENU_ABOUT_US:
		m_backButton -> Update(m_slider.click,m_slider.distanceX1,m_slider.distanceY1);
		break;

	default:
		break;
	};

	return true;
}

void Menu::draw()
{
	drawBackgroundStretched();

	switch ( m_menuState )
	{
	case MENU_MAIN:
		Iw2DDrawImage(m_title,CIwFVec2((OBSERVER->getDeviceWidth() - m_title->GetWidth())/2,20));
		m_runButton->Draw();
		m_creditsButton->Draw();
		m_soundButton->Draw();
		break;

	case MENU_ABOUT_US:
		drawImageCentered(m_names);
		m_backButton->Draw();
		break;

	default:
		break;
	};
}

void Menu::drawBackgroundStretched()
{
	Iw2DDrawImage(m_background,CIwFVec2(0,0),CIwFVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()));
}

void Menu::drawImageCentered(CIw2DImage* image)
{
	float drawX = (OBSERVER->getDeviceWidth() - image->GetWidth())/2;
	float drawY = (OBSERVER->getDeviceHeight() - image->GetHeight())/2;

	Iw2DDrawImage(image,CIwFVec2(drawX,drawY));
}

int Menu::click(float x, float y)
{
	switch ( m_menuState )
	{
	case MENU_MAIN:

		if ( m_runButton -> Click (x,y) ) {
			
			cout<<"Run Button Clicked!!!"<<endl;
			return -1;
		}
		if ( m_creditsButton -> Click (x,y) ) {

			m_menuState = MENU_ABOUT_US;
		}
		break;

	case MENU_ABOUT_US:

		if ( m_backButton -> Click (x,y) ) { 
			
			m_menuState = MENU_MAIN;
		}
		break;

	default:
		break;
	};
	
	return 0;
}