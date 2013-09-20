/*
 * This class describes an object of Button
 * The button will be a generic class with the ablity to handle
 * events wherever instantiated
 * 
 * 
 * This should eventually become part of the Game Engine that is
 * being developed by FiveRivers internally on top of the Marmalade
 * cross-platform solution
 */

#ifndef AWM_BUTTON
#define AWM_BUTTON

#include "Iw2D.h"
#include "AwmInput.h"
#include "sstream"

#define AWM_DEBUG  true
/*
 * under this tag I can safely display debug info on-screen
 * safe in the knowledge that by making this false I can get
 * rid of all that info in a jiffy
 */

class AwmButton
{
private:
	int click_id;	// id of the active touch on this button

	void setColor(CIwColour m_color) { Iw2DSetColour(m_color); }
	void resetColor() { Iw2DSetColour(0xffffffff); }

	void DrawBounded(CIw2DImage* m_image);

	void DrawText();
	void DrawText(float x1, float y1);
	void DrawText(float x1, float y1, float width, float height);

	void DrawDisabled();
	void DrawDisabled(float x1, float y1);
	void DrawDisabled(float x1, float y1, float width, float height);

	void DrawPressed();
	void DrawPressed(float x1, float y1);
	void DrawPressed(float x1, float y1, float width, float height);

	void DrawNormal();
	void DrawNormal(float x1, float y1);
	void DrawNormal(float x1, float y1, float width, float height);

	void DrawSwitch();

	void SingleTouchUpdate();
	void MultiTouchUpdate();

protected:
	float m_x1;							// x1 coordinate of the button
	float m_y1;							// y1 coordinate of the button
	float m_x2;							// x2 coordinate of the button
	float m_y2;							// y2 coordinate of the button
	float m_width;						// width of the button
	float m_height;						// height of the button
	bool m_pressed;						// true if button is pressed
	bool m_disabled;					// true if button is disabled - will not detect click
	bool m_hidden;						// true if button is hidden - will not detect click
	bool m_switch;						// true if this is a switch button

	bool on;							// true if the button is ON

	float bound_x1;						// x1 of bound area 
	float bound_y1;						// y1 of bound area
	float bound_x2;						// x2 of bound area
	float bound_y2;						// y2 of bound area
	bool m_bounded;						// true if the button is to be shown within certain bounds

	CIw2DImage* m_image_normal;			// normal image for the button
	CIw2DImage* m_image_pressed;		// pressed image for the button
	CIw2DImage* m_image_disabled;		// disabled image for the button
	CIw2DImage* m_image_flipped;		// flipped image for the button

	bool flag_image_normal;				// true if image is not a shallow copy and needs to be deleted
	bool flag_image_pressed;
	bool flag_image_disabled;

	bool m_slide;							// the button is sliding do its not clickable
	float slide_move_x;					// the number of x pixels to move for each step
	float slide_move_y;					// the number of y pixels to move for each step
	float slide_x1;						// the x1 for the slide location of the button
	float slide_y1;						// the y1 for the slide location of the button
	const char* slide_sound;			// we can play a sound effect when the button gets into position
	int total_slide_steps;				// total number of slide steps
	int current_slide_step;				// cureent slide step

	const char* m_text;					// text to display on the button - optional

										// the color with which to draw the image 
	CIwColour m_color_disabled;			// if it is disabled and image exists
										// default is grey

										// the color with which to draw the overlying
	CIwColour m_color_disabled_alpha;	// rect if disabled image does not exist
										// default is grey

										// the color with which to draw the image 
	CIwColour m_color_pressed;			// if it is pressed and no pressed image exists
										// default is grey

										// the color with which to draw overlying rect 
	CIwColour m_color_pressed_alpha;	// if it is pressed and no pressed image exists
										// default is grey

public:
	AwmButton();
	AwmButton(float x1, float y1, float x2, float y2, bool disabled = false, bool hidden = false, const char* text = "");
	AwmButton(float x1, float y1, CIw2DImage* image_normal, bool _switch = false, bool disabled = false, bool hidden = false, const char* text = "");
	AwmButton(CIw2DImage* image_pressed, float x1, float y1, bool disabled = false, bool hidden = false, const char* text = "");
	AwmButton(float x1, float y1, CIw2DImage* image_normal, CIw2DImage* image_disabled, bool _switch = false, bool disabled = false, 
		bool hidden = false, const char* text = "");
	AwmButton(CIw2DImage* image_normal, CIw2DImage* image_pressed, float x1, float y1, bool disabled = false, 
		bool hidden = false, const char* text = "");
	AwmButton(float x1, float y1, CIw2DImage* image_normal, CIw2DImage* image_disabled, CIw2DImage* image_pressed, bool disabled = false, 
		bool hidden = false, const char* text = "");
	AwmButton(float x1, float y1, float b_x1, float b_y1, float b_x2, float b_y2, 
		CIw2DImage* image_normal, bool disabled = false, bool hidden = false, const char* = "");
	~AwmButton();

	void setOn(bool _flag) { on = _flag; }

	void setBounds(float x1, float y1, float x2, float y2);
	void setCoordinates(float x1, float y1, float x2, float y2);

	void setColorDisabled(CIwColour m_color)				{ m_color_disabled = m_color; }
	void setColorDisabled(int r, int g, int b, int a)		{ m_color_disabled.r = r; m_color_disabled.g = g; m_color_disabled.b = b; m_color_disabled.a =a; }
	void setColorDisabledAlpha(CIwColour m_color)			{ m_color_disabled_alpha = m_color; }
	void setColorDisabledAlpha(int r, int g, int b, int a)	{ m_color_disabled_alpha.r = r; m_color_disabled_alpha.g = g; m_color_disabled_alpha.b = b; m_color_disabled_alpha.a =a; }
	void setColorPressed(CIwColour m_color)					{ m_color_pressed = m_color; }
	void setColorPressed(int r, int g, int b, int a)		{ m_color_pressed.r = r; m_color_pressed.g = g; m_color_pressed.b = b; m_color_pressed.a =a; }
	void setColorPressedAlpha(CIwColour m_color)			{ m_color_pressed_alpha = m_color; }
	void setColorPressedAlpha(int r, int g, int b, int a)	{ m_color_pressed_alpha.r = r; m_color_pressed_alpha.g = g; m_color_pressed_alpha.b = b; m_color_pressed_alpha.a =a; }

	void hide()			{ m_hidden = true; }
	void disable()		{ m_disabled = true; }
	void show()			{ m_hidden = false; }
	void enable()		{ m_disabled = false; }

	bool isHidden()		{ return m_hidden; }
	bool isDisabled()	{ return m_disabled; }

	bool isOn()			{ return on; }

	bool isSliding()	{ return m_slide; }

	bool isPressed()	{ return m_pressed; }

	bool Click(float x, float y);

	float getX1()		{ return m_x1; }
	float getX2()		{ return m_x2; }
	float getY1()		{ return m_y1; }
	float getY2()		{ return m_y2; }


	bool Update(bool click, float x1, float y1);
	void Update();

	void Slide(float x, float y, int steps, const char* soundeffect = "");

	void Draw();
	void Draw(float x1, float y1);
	void Draw(float x1, float y1, float width, float height);
};

#endif