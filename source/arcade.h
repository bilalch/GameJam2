/*
 * this class defines an object of arcade mode
 * for HH
 */

#ifndef ARCADE_H
#define ARCADE_H

#include "view.h"
#include "scrolling_background.h"
#include "player_car.h"
#include "AwmButton.h"
#include "dynamicArray.h"
#include "opponent_car.h"
#include "cart.h"
#include "box.h"
#include "mud.h"
#include "collidable.h"
#include "spine_char.h"

class Arcade : public View
{
public:
	Arcade();
	~Arcade();

	void draw();
	bool update(sliderStruct&);
	int click(float x, float y);

	void loadImages();
	void unloadImages();

	void initializeButtons();
	void destroyButtons();

	void generateLevel();

private:
	ScrollingBackground* m_scrolling_background;

	PlayerCar* m_playerCar;

	CIw2DImage* m_scrolling_image;

	CIw2DImage* m_cart_image;
	CIw2DImage* m_box_image;
	CIw2DImage* m_mud_image;

	AwmButton* m_speed_button;
	AwmButton* m_right_button;
	AwmButton* m_left_button;

	CIwResGroup* imagesGroup;

	AeDynArray<Collidable*> m_opponents;

	SpineChar* m_boy;
};

#endif