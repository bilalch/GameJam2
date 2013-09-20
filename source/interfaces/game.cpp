#include "game.h"
#include "AwmInput.h"

void MultiTouchButtonCB(s3ePointerTouchEvent* event, void* userData)
{
	Game* temp = (Game*) userData;
	//temp->Clicker(event);
	AWM_INPUT -> Clicker(event, userData);
}

void MultiTouchMoveCB(s3ePointerTouchMotionEvent* event, void* userData)
{
	Game* temp = (Game*) userData;
	//temp->Clicker(event);
	AWM_INPUT -> Mover(event);
}

void SingleTouchButtonCB(s3ePointerEvent* event, void* userData)
{
	Game* temp = (Game*) userData;
	//temp->Clicker(event);
	AWM_INPUT -> Clicker(event, userData);
}

void SingleTouchMoveCB(s3ePointerMotionEvent* event, void* userData)
{
	Game* temp = (Game*) userData;
	//temp->Clicker(event);
	AWM_INPUT -> Mover(event);
}

Game::Game()
{
	s3eDebugOutputString("Game Model Constructor");
	
	Iw2DInit();

	IwResManagerInit();
	
	InitializeSlider();
	
	m_multitouch_available = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;

	m_soundManager = NULL;

	m_font = NULL;
}

Game::~Game()
{
	s3eDebugOutputString("Game Model Destructor");

	s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT,(s3eCallback)SingleTouchButtonCB);
	s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT,(s3eCallback)MultiTouchButtonCB);

	if ( m_soundManager ) {
		
		m_soundManager->Destroy();
		delete m_soundManager;

		IwSoundTerminate();
	}

	if ( m_font ) {
		
		delete m_font;
	}

	IwResManagerTerminate();

	Iw2DTerminate();
}

// virtual methods

void Game::Clicker(float x, float y)
{
	s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "You forgot to overwrite the click method !!!");
	s3eDeviceExit();
}

/*
void Game::Clicker(s3ePointerTouchEvent* event)
{
	s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "You forgot to overwrite the click method !!!");
	s3eDeviceExit();
}
*/

void Game::InitializeTouch(bool multitouch)
{
	if ( multitouch ) {

		// Initialize multi touch
		if ( !m_multitouch_available ) {
							
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "Trying to initialize multitouch while it is not available. Check if multitouch is available before initializing");
			s3eDeviceExit();
		} else {
			
			s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, this);
			s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMoveCB, this);
			AWM_INPUT -> setMultitouch(true);
		}
	} else {
		
		// Initialize single touch
		s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, this);
		s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMoveCB, this);
		AWM_INPUT -> setMultitouch(false);
	}
}

void Game::InitializeSound(const char* groupPath, const char* groupName)
{
	IwSoundInit();

	m_soundManager = new AwmSoundManager();
	m_soundManager->Create();
	AWM_SOUND_MANAGER->Init(groupPath,groupName);
}

void Game::InitializeFonts(const char* groupPath, const char* fontName)
{
	IwGetResManager()->LoadGroup(groupPath);
	m_font = Iw2DCreateFontResource(fontName);
}

// private methods

/*
void Game::SortViews()
{
	string max = "";
	hash_map<string, View *> temp;

	for(hash_map<string, View *>::iterator it = activeViews.begin(); it != activeViews.end(); it++){
		temp[it->first] = it->second;
	}

	for(int i = 0; i < activeViewKeys.GetSize(); i++){
		max = "";
		for(hash_map<string, View *>::iterator it = temp.begin(); it != temp.end(); it++){
			if((it->second->getZIndex() > activeViews[max]->getZIndex()) || max == "")
				max = it->first;
		}
		activeViewKeys[i] = max;
		temp.erase(max);
	}
}
*/

void Game::InitializeSlider()
{
	s3eDebugOutputString("Game Model - Initialize Slider");

	m_slider.click = false;
	m_slider.distance = 0;
	m_slider.distanceX1 = 0;
	m_slider.distanceY1 = 0;
	m_slider.left = false;
	m_slider.moveable = false;
	m_slider.pressed = false;
	m_slider.prevX = 0;
	m_slider.right = false;
	m_slider.time = 0;
	m_slider.timeX1 = 0;
	m_slider.touchX = 0;
	m_slider.velocity = 0;
	m_slider.whichTouch = false;

	m_slider.moveX1 = 0;
	m_slider.moveX2 = 0;

	m_slider.moveY1 = 0;
	m_slider.moveY2 = 0;
	m_slider.velocityX = 0;
	m_slider.velocityY = 0;

	m_slider.touchY = 0;
	m_slider.prevY = 0;
	m_slider.whichTouch2 = false;
	m_slider.up = false;
	m_slider.down = false;
}