/*
 * this class defines a singleton object of
 * AwmInput which will keep track of all active
 * touches on the surface
 *
 * Note to self and other hapless programmers who
 * stumble across this : the "click" will be passed
 * directly to classes since that is a completed
 * action. This class only tracks while touch is down
 */

#ifndef AWM_INPUT_H
#define AWM_INPUT_H

#include "s3e.h"
#include "structures.h"

#define MAX_TOUCHES 4

#define AWM_INPUT	AwmInput::getInstance()

class AwmInput
{
public:
	AwmInput();
	~AwmInput();

	static AwmInput* getInstance();
	void Clicker(s3ePointerTouchEvent* event, void* userData);
	void Clicker(s3ePointerEvent* event, void* userData);
	void Mover(s3ePointerTouchMotionEvent* event);
	void Mover(s3ePointerMotionEvent* event);

	sliderStruct m_sliders[MAX_TOUCHES];			// used if the application is multi touch
	sliderStruct m_singleTouch_slider;				// used if the application is single touch

	bool getMultitouch() { return m_multitouch; }
	void setMultitouch(bool _flag) { m_multitouch = _flag; }

	bool getSwipeLeft() { return m_singleTouch_slider.swipe_left; }
	bool getSwipeRight() { return m_singleTouch_slider.swipe_right; }
	bool getSwipeUp() { return m_singleTouch_slider.swipe_up; }
	bool getSwipeDown() { return m_singleTouch_slider.swipe_down; }
	bool getSwipe() { return m_singleTouch_slider.swipe; }
private:
	static AwmInput *sharedInstance;

	void initializeMoveAllowance();
	void initializeSliders();
	void initializeSlider(sliderStruct& m_slider);

	void calculateSwipe(float, float);

	sliderStruct* findTouch(s3ePointerTouchEvent* event);
	sliderStruct* findTouch(s3ePointerTouchMotionEvent* event);

	int moveAllowance;		/* 
							 * the distance in pixels where click remains true
							 * 0 works on iPhone but somehow Androids touch system
							 * requires a bit of variance to function correctly
							 */

	bool m_multitouch;		/*
							 * keeps track of what the user passed to the game object
							 * when the application was started for later referrence
							 */
};

#endif