#include "AwmButton.h"
#include "AwmSoundManager.h"

AwmButton::AwmButton()
{
	// base constructor
	m_x1 = 0;
	m_y1 = 0;
	m_x2 = 0;
	m_y2 = 0;
	m_width = 0;
	m_height = 0;
	m_pressed = false;
	m_disabled = false;
	m_hidden = false;
	m_switch = false;

	on = true;

	m_text = "";

	bound_x1 = 0;
	bound_y1 = 0;
	bound_x2 = 0;
	bound_y2 = 0;
	m_bounded = false;

	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	m_image_disabled = NULL;
	m_image_normal = NULL;
	m_image_pressed = NULL;
	m_image_flipped = NULL;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

AwmButton::AwmButton(float x1, float y1, float x2, float y2, bool disabled, bool hidden, const char* text)
{
	setCoordinates(x1,y1,x2,y2);

	m_pressed = false;
	m_disabled = disabled;
	m_hidden = hidden;
	m_bounded = false;
	m_switch = false;

	on = true;

	m_text = text;

	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	m_image_disabled = NULL;
	m_image_normal = NULL;
	m_image_pressed = NULL;
	m_image_flipped = NULL;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

AwmButton::AwmButton(float x1, float y1, CIw2DImage* image_normal, bool _switch, bool disabled, bool hidden, const char* text)
{
	m_x1 = x1;
	m_y1 = y1;
	m_width = image_normal->GetWidth();
	m_height = image_normal->GetHeight();
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;
	m_pressed = false;
	m_disabled = disabled;
	m_hidden = hidden;
	m_bounded = false;
	m_switch = _switch;

	on = true;

	m_text = text;
	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	if ( !m_switch ) {

		m_image_normal = image_normal;			// shallow copy
		m_image_flipped = NULL;
	} else {
		
		m_image_flipped = image_normal;			// shallow copy
		m_image_normal = NULL;
	}
	m_image_disabled = NULL;
	m_image_pressed = NULL;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

AwmButton::AwmButton(CIw2DImage* image_pressed, float x1, float y1, bool disabled, bool hidden, const char* text)
{
	m_x1 = x1;
	m_y1 = y1;
	m_width = image_pressed->GetWidth();
	m_height = image_pressed->GetHeight();
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;
	m_pressed = false;
	m_disabled = disabled;
	m_hidden = hidden;
	m_bounded = false;
	m_switch = false;

	on = true;

	m_text = text;
	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	m_image_normal = NULL;			// shallow copy
	m_image_disabled = NULL;
	m_image_pressed = image_pressed;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

AwmButton::AwmButton(float x1, float y1, CIw2DImage* image_normal, CIw2DImage* image_disabled, bool _switch, bool disabled, bool hidden, const char* text)
{
	m_x1 = x1;
	m_y1 = y1;
	m_width = image_normal->GetWidth();
	m_height = image_normal->GetHeight();
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;
	m_pressed = false;
	m_disabled = disabled;
	m_hidden = hidden;
	m_bounded = false;
	m_switch = _switch;

	on = true;

	m_text = text;
	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	m_image_normal = image_normal;			// shallow copy

	if ( !m_switch ) {

		m_image_disabled = image_disabled;
		m_image_flipped = NULL;
	} else {

		m_image_flipped = image_disabled;
		m_image_disabled = NULL;
	}
	m_image_pressed = NULL;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

AwmButton::AwmButton(CIw2DImage* image_normal, CIw2DImage* image_pressed, float x1, float y1, bool disabled, bool hidden, const char* text)
{
	m_x1 = x1;
	m_y1 = y1;
	m_width = image_normal->GetWidth();
	m_height = image_normal->GetHeight();
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;
	m_pressed = false;
	m_disabled = disabled;
	m_hidden = hidden;
	m_bounded = false;
	m_switch = false;


	m_text = text;
	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	m_image_normal = image_normal;			// shallow copy
	m_image_pressed = image_pressed;
	m_image_disabled = NULL;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

AwmButton::AwmButton(float x1, float y1, CIw2DImage* image_normal, CIw2DImage* image_disabled, CIw2DImage* image_pressed, bool disabled, bool hidden, const char* text)
{
	m_x1 = x1;
	m_y1 = y1;
	m_width = image_normal->GetWidth();
	m_height = image_normal->GetHeight();
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;
	m_pressed = false;
	m_disabled = disabled;
	m_hidden = hidden;
	m_bounded = false;
	m_switch = false;

	on = true;

	m_text = text;
	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	m_image_normal = image_normal;			// shallow copy
	m_image_disabled = image_disabled;		// shallow copy
	m_image_pressed = image_pressed;		// shallow copy
	m_image_flipped = NULL;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

AwmButton::AwmButton(float x1, float y1, float b_x1, float b_y1, float b_x2, float b_y2, CIw2DImage* image_normal, bool disabled, bool hidden, const char* text)
{
	m_x1 = x1;
	m_y1 = y1;
	m_width = image_normal->GetWidth();
	m_height = image_normal->GetHeight();
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;
	m_pressed = false;
	m_disabled = disabled;
	m_hidden = hidden;
	m_switch = false;

	on = true;

	m_text = text;
	setBounds(b_x1, b_y1, b_x2, b_y2);

	m_color_disabled.r = 132;
	m_color_disabled.g = 134;
	m_color_disabled.b = 136;
	m_color_disabled.a = 255;

	m_color_pressed = m_color_disabled;

	m_color_disabled_alpha.r = 132;
	m_color_disabled_alpha.g = 134;
	m_color_disabled_alpha.b = 136;
	m_color_disabled_alpha.a = 128;

	m_color_pressed_alpha = m_color_disabled_alpha;

	m_image_normal = image_normal;			// shallow copy
	m_image_disabled = NULL;
	m_image_pressed = NULL;
	m_image_flipped = NULL;

	flag_image_disabled = false;
	flag_image_normal = false;
	flag_image_pressed = false;

	m_slide = false;
	click_id = -1;
}

// Setters

void AwmButton::setBounds(float x1, float y1, float x2, float y2)
{
	bound_x1 = x1;
	bound_y1 = y1;
	bound_x2 = x2;
	bound_y2 = y2;
	m_bounded = true;
}

void AwmButton::setCoordinates(float x1, float y1, float x2, float y2)
{
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x2;
	m_y2 = y2;
	m_width = m_x2 - m_x1;
	m_height = m_y2 - m_y1;
}

// Getters
//

bool AwmButton::Click(float x, float y)
{
	if ( !m_hidden && !m_disabled && !m_slide ) {

		// if the button is not hidden or disabled or sliding
		if ( m_bounded ) {

			// check bounds first - then the click
			if ( x > bound_x1 && x < bound_x2 && y > bound_y1 && y < bound_y2 ) {

				// within bounds
				if ( x > m_x1 && x < m_x2 && y > m_y1 && y < m_y2 ) {

					// touch within coordinates
					if ( m_switch ) {
						
						// if the button is a switch - flip it
						on = !on;
					}
					return true;
				}
			}

		} else {

			// only check the click
			if ( x > m_x1 && x < m_x2 && y > m_y1 && y < m_y2 ) {

				// touch within coordinates
				if ( m_switch ) {

					// if the button is a switch - flip it
					on = !on;
				}
				return true;
			}
		}
	}

	return false;
}

void AwmButton::Update()
{
	if ( AWM_INPUT -> getMultitouch() ) {

		MultiTouchUpdate();
	} else {
		
		SingleTouchUpdate();
	}
}

void AwmButton::SingleTouchUpdate()
{
	const sliderStruct m_slider = AWM_INPUT -> m_singleTouch_slider;
	if ( m_pressed ) {

		// touch found
		if ( m_slider.pressed ) {

			// touch is still pressed - do nothing
		} else {

			// touch is no longer pressed
			m_pressed = false;
		}
	} else {

		// button is not pressed
		if ( Update ( m_slider.click, m_slider.distanceX1, m_slider.distanceY1 ) ) {

		}
	}
}

void AwmButton::MultiTouchUpdate()
{
	for ( int i = 0; i < MAX_TOUCHES; i++ ) {

		const sliderStruct m_slider = AWM_INPUT -> m_sliders[i];
		if ( m_pressed ) {
			
			// button is already pressed - update touch
			if ( m_slider.id == click_id ) {
				
				// touch found
				if ( m_slider.pressed ) {
					
					// touch is still pressed - do nothing
					break;
				} else {
					
					// touch is no longer pressed
					m_pressed = false;
					click_id = -1;
					break;
				}
			}
		} else {
			
			// button is not pressed
			if ( Update ( m_slider.click, m_slider.distanceX1, m_slider.distanceY1 ) ) {

				click_id = m_slider.id;
				break;
			}
		}
	}
}

bool AwmButton::Update(bool click, float x1, float y1)
{
	if ( !m_hidden && !m_disabled ) {

		if ( !m_slide ) {
			// only update click if button is neither disabled nor hidden and not sliding
			if ( click ) {

				// touch down
				if ( m_bounded ) {

					// bounded - check bounds first
					if ( x1 > bound_x1 && x1 < bound_x2 && y1 > bound_y1 && y1 < bound_y2 ) {

						// within bounds - check actual touch
						if ( x1 > m_x1 && x1 < m_x2 && y1 > m_y1 && y1 < m_y2 ) {

							// click is down within image - button is pressed
							m_pressed = true;
							return true;
						}
					}
				} else {

					// not bounded
					if ( x1 > m_x1 && x1 < m_x2 && y1 > m_y1 && y1 < m_y2 ) {

						// click is down within image - button is pressed
						m_pressed = true;
						return true;
					}
				}
			} else {

				// touch up
				m_pressed = false;
			}
		} else {

			slide_x1 = slide_x1 + slide_move_x;
			slide_y1 = slide_y1 + slide_move_y;

			current_slide_step++;
			if( current_slide_step > total_slide_steps ) {
				
				m_slide = false;
				if ( strcmp("",slide_sound ) ) {
					
					AWM_SOUND_MANAGER -> PlaySoundEffect ( slide_sound );
				}
			}
		}
	}
	return false;
}

void AwmButton::DrawBounded(CIw2DImage* m_image)
{
	if ( !m_slide ) {
		if ( m_bounded ) {

			if ( m_x2 <= bound_x1 ) {

				// draw nothing element is outside the list

			} else if ( m_x1 > bound_x2 ) {

				// draw nothing element is outside the list

			} else if ( m_y2 <= bound_y1 ) {

				// draw nothing element is outside the list

			} else if ( m_y1 > bound_y2 ) {

				// draw nothing element is outside the list

			} else if ( m_x1 >= bound_x1 && m_x2 <= bound_x2 && m_y1 >= bound_y1 && m_y2 <= bound_y2 ) {

				// everything is within bounds
				Iw2DDrawImage(m_image,CIwSVec2(m_x1,m_y1));

			} else if ( m_x1 >= bound_x1 && m_x2 > bound_x2 ) {

				// going out from the right
				Iw2DDrawImageRegion(m_image,CIwSVec2(m_x1,m_y1),CIwSVec2(bound_x2-m_x1,m_height),CIwSVec2(0,0),CIwSVec2(((bound_x2-m_x1)*m_image->GetWidth())/m_width,m_image->GetHeight()));

			} else if ( m_x1 < bound_x1 && m_x2 >= bound_x1 ) {

				// going out from the left
				Iw2DDrawImageRegion(m_image,CIwSVec2(bound_x1,m_y1),CIwSVec2(m_x2-bound_x1,m_height),CIwSVec2(((bound_x1-m_x1)*m_image->GetWidth())/m_width,0),CIwSVec2(((m_x2-bound_x1)*m_image->GetWidth())/m_width,m_image->GetHeight()));

			} else if( m_y1 >= bound_y1 && m_y2 > bound_y2 )	{

				// going out from the bottom
				Iw2DDrawImageRegion(m_image,CIwSVec2(m_x1,m_y1),CIwSVec2(m_width,bound_y2-m_y1),CIwSVec2(0,0),CIwSVec2((m_image->GetWidth()),((bound_y2-m_y1)*m_image->GetHeight())/m_height));

			} else if ( m_y1 < bound_y1 && m_y2 >= bound_y1 ) {

				// going out from the top
				Iw2DDrawImageRegion(m_image,CIwSVec2(m_x1,bound_y1),CIwSVec2(m_width,m_y2-bound_y1),CIwSVec2(0,((bound_y1-m_y1)*m_image->GetHeight())/m_height),CIwSVec2(m_image->GetWidth(),((m_y2-bound_y1)*m_image->GetHeight())/m_height));

			} 

		} else {

			// image is not bounded
			Iw2DDrawImage(m_image,CIwSVec2(m_x1,m_y1));

		}
	} else {

		Iw2DDrawImage(m_image,CIwSVec2(slide_x1,slide_y1));
	}
}

void AwmButton::DrawText()
{
	if ( !strcmp("",m_text) ) {
		
		// string is empty - nothing to draw

	} else {
		
		// string has text - draw if within bounds
		if ( m_bounded ) {

			if ( m_x1 >= bound_x1 && m_x2 <= bound_x2 && m_y1 >= bound_y1 && m_y2 <= bound_y2 ) {
			
				// within bounds draw text
				Iw2DDrawString(m_text,CIwSVec2(m_x1,m_y1),CIwSVec2(m_width,m_height),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);

			}
		} else {

			// not bounded
			Iw2DDrawString(m_text,CIwSVec2(m_x1,m_y1),CIwSVec2(m_width,m_height),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);

		}
	}
}

void AwmButton::Draw()
{
	if ( m_hidden ) {

		// Do Nothing - the button is hidden

	} else if ( m_disabled ) {

		// The Button is disabled
		DrawDisabled();

	} else if ( m_pressed ) {

		// The Button is pressed
		DrawPressed();
		DrawText();

	} else if ( m_switch ) {

		// this is a switch
		DrawSwitch();
		DrawText();

	} else {

		// The Button is in normal state
		DrawNormal();
		DrawText();
	}

	if ( AWM_DEBUG ) {
		stringstream ss;
		ss<<click_id;

		Iw2DDrawString(ss.str().c_str(),CIwSVec2(m_x1, m_y1),CIwSVec2(m_width,m_height),IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE);
	}
}

void AwmButton::DrawDisabled()
{
	if ( m_image_disabled ) {

		// the disabled image exists
		DrawBounded(m_image_disabled);

		setColor(m_color_disabled);
		DrawText();
		resetColor();

	} else {

		// the disabled image does not exist
		if ( m_image_normal ) {
		
			// draw the normal image greyed out
			setColor(m_color_disabled);
			DrawBounded(m_image_normal);
			DrawText();
			resetColor();

		} else {

			// normal image does not exist as well
			// draw a grey rect over the coordinates
			DrawText();
			setColor(m_color_disabled_alpha);
			Iw2DFillRect(CIwSVec2(m_x1, m_y1),CIwSVec2(m_width,m_height));
			resetColor();

		}
	}
}

void AwmButton::DrawPressed()
{
	if ( m_image_pressed ) {
	
		// the pressed image exists
		DrawBounded(m_image_pressed);

	} else {

		// the pressed image does not exist
		if ( m_image_normal ) {

			// the normal image exists
			setColor(m_color_pressed);
			DrawBounded(m_image_normal);
			resetColor();

		} else {

			// normal image does not exist as well
			// draw a grey rect over the coordinates
			setColor(m_color_pressed_alpha);
			Iw2DFillRect(CIwSVec2(m_x1, m_y1),CIwSVec2(m_width,m_height));
			resetColor();

		}
	}
}

void AwmButton::DrawNormal()
{
	if ( m_image_normal ) {
		
		// normal image exists
		DrawBounded(m_image_normal);

	} else {

		// normal image does not exist
		// do nothing

	}
}

void AwmButton::DrawSwitch()
{
	if ( on ) {
		
		// the switch in ON
		if ( m_image_normal ) {

			// normal image exists
			DrawBounded(m_image_normal);
		}
	} else {

		// the switch is OFF
		if ( m_image_flipped ) {
			
			// flipped image exists
			DrawBounded(m_image_flipped);
		}
	}
}

void AwmButton::Slide(float x, float y, int steps, const char* soundEffect)
{
	slide_x1 = x;
	slide_y1 = y;

	slide_move_x = (m_x1 - slide_x1)/steps;
	slide_move_y = (m_y1 - slide_y1)/steps;

	slide_sound = soundEffect;

	m_slide = true;

	total_slide_steps = steps;
	current_slide_step = 0;
}

AwmButton::~AwmButton()
{
	if(flag_image_disabled)
		delete m_image_disabled;

	if(flag_image_normal)
		delete m_image_normal;

	if(flag_image_pressed)
		delete m_image_pressed;

	m_image_disabled = NULL;
	m_image_normal = NULL;
	m_image_pressed = NULL;
}