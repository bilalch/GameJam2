#include "AwmInput.h"
#include "game.h"

AwmInput* AwmInput::sharedInstance = NULL;

AwmInput* AwmInput::getInstance()
{
    if(!sharedInstance)
    {
        sharedInstance = new AwmInput();
        return sharedInstance;
    }
    else
    {
        return sharedInstance;
    }
}

AwmInput::AwmInput()
{
	// constructor
	initializeMoveAllowance();
	initializeSliders();
}

AwmInput::~AwmInput()
{
	// destructor
	if (sharedInstance)
		delete sharedInstance;
}

void AwmInput::initializeMoveAllowance()
{
	if ( s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_IPHONE ) {
		
		moveAllowance = 0;
	} else if ( s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_ANDROID ) {
		
		moveAllowance = 10;
	}
}

void AwmInput::initializeSliders()
{
	for ( int i = 0; i < MAX_TOUCHES; i++ ) {
		
		initializeSlider( m_sliders[i] );
	}
	initializeSlider( m_singleTouch_slider );
}

void AwmInput::initializeSlider(sliderStruct& m_slider)
{
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

	m_slider.id = -1;

	m_slider.swipe_down = false;
	m_slider.swipe_up = false;
	m_slider.swipe_right = false;
	m_slider.swipe_left = false;
	m_slider.swipe = false;
}


sliderStruct* AwmInput::findTouch(s3ePointerTouchEvent* event)
{
	for (int i = 0; i < MAX_TOUCHES; i++) {
		
		if ( m_sliders[i].id == event->m_TouchID ) {

			return &m_sliders[i];
		}

		if( !m_sliders[i].pressed ) {
			
			m_sliders[i].id = event->m_TouchID;
			return &m_sliders[i];
		}
	}
	return NULL;
}

sliderStruct* AwmInput::findTouch(s3ePointerTouchMotionEvent* event)
{
	for (int i = 0; i < MAX_TOUCHES; i++) {
		
		if ( m_sliders[i].id == event->m_TouchID ) {

			return &m_sliders[i];
		}

		if( !m_sliders[i].pressed ) {
			
			m_sliders[i].id = event->m_TouchID;
			return &m_sliders[i];
		}
	}
	return NULL;
}


void AwmInput::Mover(s3ePointerTouchMotionEvent* event)
{
	sliderStruct* m_slider = findTouch(event);
	int moveAllowance = 0;
	if(m_slider->pressed)
	{
		m_slider->moveX2 = event->m_x;
		m_slider->moveY2 = event->m_y;
		//s3eDebugOutputString(" Pressed and Moving ");
		if(m_slider->whichTouch)
		{
			//cout<<endl<<event->m_x<<endl;
			m_slider->prevX = event->m_x;
			if(event->m_x > m_slider->touchX + moveAllowance)
			{
				m_slider->left = true;
				m_slider->right = false;
				m_slider->click = false;
			}
			else if(event->m_x < m_slider->touchX - moveAllowance)
			{
				m_slider->left = false;
				m_slider->right = true;
				m_slider->click = false;
			}
			m_slider->whichTouch = !m_slider->whichTouch;
		}
		else
		{
			m_slider->touchX = event->m_x;
			if(event->m_x > m_slider->prevX + moveAllowance)
			{
				m_slider->left = true;
				m_slider->right = false;
				m_slider->click = false;
			}
			else if(event->m_x < m_slider->prevX - moveAllowance)
			{
				m_slider->left = false;
				m_slider->right = true;
				m_slider->click = false;
			}
			m_slider->whichTouch = !m_slider->whichTouch;
		}

		////////////////////////////////////////////////

		if(m_slider->whichTouch2)
		{
			m_slider->prevY = event->m_y;
			if(event->m_y > m_slider->touchY + moveAllowance)
			{
				m_slider->down = true;
				m_slider->up = false;
				m_slider->click = false;
			}
			else if(event->m_y < m_slider->touchY - moveAllowance)
			{
				m_slider->down = false;
				m_slider->up = true;
				m_slider->click = false;
			}
			m_slider->whichTouch = !m_slider->whichTouch;
		}
		else
		{
			m_slider->touchY = event->m_y;
			if(event->m_y > m_slider->prevY + moveAllowance)
			{
				m_slider->down = true;
				m_slider->up = false;
				m_slider->click = false;
				//m_slider.click = false;
			}
			else if(event->m_y < m_slider->prevY - moveAllowance)
			{
				m_slider->down = false;
				m_slider->up = true;
				m_slider->click = false;
			}
			m_slider->whichTouch2 = !m_slider->whichTouch2;
		}
	}
}

void AwmInput::Mover(s3ePointerMotionEvent* event)
{
	int moveAllowance = 10;
	if(m_singleTouch_slider.pressed)
	{
		m_singleTouch_slider.moveX2 = event->m_x;
		m_singleTouch_slider.moveY2 = event->m_y;
		//s3eDebugOutputString(" Pressed and Moving ");
		if(m_singleTouch_slider.whichTouch)
		{
			//cout<<endl<<event->m_x<<endl;
			m_singleTouch_slider.prevX = event->m_x;
			if(event->m_x > m_singleTouch_slider.touchX + moveAllowance)
			{
				m_singleTouch_slider.left = true;
				m_singleTouch_slider.right = false;
				m_singleTouch_slider.click = false;
			}
			else if(event->m_x < m_singleTouch_slider.touchX - moveAllowance)
			{
				m_singleTouch_slider.left = false;
				m_singleTouch_slider.right = true;
				m_singleTouch_slider.click = false;
			}
			m_singleTouch_slider.whichTouch = !m_singleTouch_slider.whichTouch;
		}
		else
		{
			m_singleTouch_slider.touchX = event->m_x;
			if(event->m_x > m_singleTouch_slider.prevX + moveAllowance)
			{
				m_singleTouch_slider.left = true;
				m_singleTouch_slider.right = false;
				m_singleTouch_slider.click = false;
			}
			else if(event->m_x < m_singleTouch_slider.prevX - moveAllowance)
			{
				m_singleTouch_slider.left = false;
				m_singleTouch_slider.right = true;
				m_singleTouch_slider.click = false;
			}
			m_singleTouch_slider.whichTouch = !m_singleTouch_slider.whichTouch;
		}

		////////////////////////////////////////////////

		if(m_singleTouch_slider.whichTouch2)
		{
			m_singleTouch_slider.prevY = event->m_y;
			if(event->m_y > m_singleTouch_slider.touchY + moveAllowance)
			{
				m_singleTouch_slider.down = true;
				m_singleTouch_slider.up = false;
				m_singleTouch_slider.click = false;
			}
			else if(event->m_y < m_singleTouch_slider.touchY - moveAllowance)
			{
				m_singleTouch_slider.down = false;
				m_singleTouch_slider.up = true;
				m_singleTouch_slider.click = false;
			}
			m_singleTouch_slider.whichTouch = !m_singleTouch_slider.whichTouch;
		}
		else
		{
			m_singleTouch_slider.touchY = event->m_y;
			if(event->m_y > m_singleTouch_slider.prevY + moveAllowance)
			{
				m_singleTouch_slider.down = true;
				m_singleTouch_slider.up = false;
				m_singleTouch_slider.click = false;
				//m_slider.click = false;
			}
			else if(event->m_y < m_singleTouch_slider.prevY - moveAllowance)
			{
				m_singleTouch_slider.down = false;
				m_singleTouch_slider.up = true;
				m_singleTouch_slider.click = false;
			}
			m_singleTouch_slider.whichTouch2 = !m_singleTouch_slider.whichTouch2;
		}

		float xVariance = event->m_x - m_singleTouch_slider.distanceX1;
		float yVariance = event->m_y - m_singleTouch_slider.distanceY1;

		calculateSwipe(xVariance, yVariance);
	}
}

void AwmInput::Clicker(s3ePointerTouchEvent* event, void* userData)
{
	Game* temp = (Game*) userData;
	if(event->m_Pressed)
	{
		sliderStruct* m_slider = findTouch(event);
		if(m_slider != NULL) {

			m_slider->click = true;
			m_slider->pressed = true;
			m_slider->distanceX1 = event->m_x;
			m_slider->distanceY1 = event->m_y;
			m_slider->moveX1 = event->m_x;
			m_slider->timeX1 = s3eTimerGetMs();
			m_slider->moveY1  = event->m_y;
		}
	}
	else
	{
		sliderStruct* m_slider = findTouch(event);
		temp -> Clicker(event->m_x, event->m_y);
		if ( m_slider != NULL ) {
		
			m_slider->click = false;
			m_slider->pressed = false;
			m_slider->right = false;
			m_slider->left = false;
			m_slider->down = false;
			m_slider->up = false;
		}
	}
}

void AwmInput::Clicker(s3ePointerEvent* event, void* userData)
{
	int variance = 10;
	Game* temp = (Game*) userData;
	if(event->m_Pressed)
	{
		m_singleTouch_slider.click = true;
		m_singleTouch_slider.pressed = true;
		m_singleTouch_slider.distanceX1 = event->m_x;
		m_singleTouch_slider.distanceY1 = event->m_y;
		m_singleTouch_slider.moveX1 = event->m_x;
		m_singleTouch_slider.timeX1 = s3eTimerGetMs();
		m_singleTouch_slider.moveY1  = event->m_y;
	}
	else
	{
		if(event->m_x < (m_singleTouch_slider.distanceX1 + variance) && event->m_x > (m_singleTouch_slider.distanceX1 - variance) && event->m_y < (m_singleTouch_slider.distanceY1 + variance) && event->m_y >(m_singleTouch_slider.distanceY1 - variance))
		{
			temp -> Clicker(event->m_x, event->m_y);
		}
		else
		{
			m_singleTouch_slider.distance = event->m_x - m_singleTouch_slider.distanceX1;
			m_singleTouch_slider.time = s3eTimerGetMs() - m_singleTouch_slider.timeX1;
			if(time != 0)
			{
				float temp = m_singleTouch_slider.time/50;
				m_singleTouch_slider.velocity = (float)m_singleTouch_slider.distance/temp;
				m_singleTouch_slider.velocityX = m_singleTouch_slider.velocity;
				m_singleTouch_slider.velocityY = (float)(event->m_y - m_singleTouch_slider.distanceY1)/temp;

				//float xVariance = event->m_x - m_singleTouch_slider.distanceX1;
				//float yVariance = event->m_y - m_singleTouch_slider.distanceY1;

				//calculateSwipe(xVariance, yVariance);
				
			}
			else
			{
				m_singleTouch_slider.velocity = 1;
				m_singleTouch_slider.velocityX = 1;
				m_singleTouch_slider.velocityY = 1;
			}
			m_singleTouch_slider.time  = 0;
			m_singleTouch_slider.left = false;
			m_singleTouch_slider.right = false;
			m_singleTouch_slider.up = false;
			m_singleTouch_slider.down = false;
		}

		m_singleTouch_slider.click = false;
		m_singleTouch_slider.pressed = false;
		m_singleTouch_slider.right = false;
		m_singleTouch_slider.left = false;
		m_singleTouch_slider.down = false;
		m_singleTouch_slider.up = false;
		m_singleTouch_slider.swipe = false;
		m_singleTouch_slider.swipe_down = false;
		m_singleTouch_slider.swipe_up = false;
		m_singleTouch_slider.swipe_right = false;
		m_singleTouch_slider.swipe_left = false;
	}
}

void AwmInput::calculateSwipe(float xVariance, float yVariance)
{
	if ( !m_singleTouch_slider.swipe ) {

		// only create a swipe if a swipe is not already active
		if ( ( yVariance > 0 && yVariance < 10 ) || ( yVariance < 0 && yVariance > -10 ) ) {

			// y movement can be ignored - too small
			if ( xVariance > 10 ) {

				// positive x movement is sufficient
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_right = true;
			} else if ( xVariance < -10 ) {

				// negative x movement is sufficient
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_left = true;
			}
		} else if ( ( xVariance > 0 && xVariance < 10 ) || ( xVariance < 0 && xVariance > -10 ) ) {

			// x movement can be ignored - too small
			if ( yVariance > 10 ) {

				// positive x movement is sufficient
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_down = true;
			} else if ( yVariance < -10 ) {

				// negative x movement is sufficient
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_up = true;
			}
		} else if ( xVariance > 0 && yVariance > 0 ) {

			// both x and y are positive
			if ( xVariance > yVariance ) {

				// x is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_right = true;
			} else {

				// y is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_down = true;
			}
		} else if ( xVariance < 0 && yVariance < 0 ) {

			// both x and y are negative
			if ( xVariance < yVariance ) {

				// x is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_left = true;
			} else {

				// y is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_up = true;
			}
		} else if ( xVariance > 0 && yVariance < 0 ) {

			// x is positive - y is negative
			yVariance = -yVariance;
			if ( xVariance > yVariance ) {

				// x is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_right = true;
			} else {

				// y is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_up = true;
			}
		} else if ( xVariance < 0 && yVariance > 0 ) {

			// x is negative - y is positive
			xVariance = -xVariance;
			if ( xVariance > yVariance ) {

				// x is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_left = true;
			} else {

				// y is superior
				m_singleTouch_slider.swipe = true;
				m_singleTouch_slider.swipe_down = true;
			}
		}
	}
}

