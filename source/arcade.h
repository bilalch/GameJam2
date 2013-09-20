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

	void spawnOpponents();
	bool laneIsOpen(int);

	void opponentsCollisionHandling();

	CIw2DImage* randomizeCarImage();

private:
	ScrollingBackground* m_scrolling_background;

	PlayerCar* m_playerCar;

	CIw2DImage* m_scrolling_image;
	CIw2DImage* m_speed_normal_image;
	CIw2DImage* m_speed_pressed_image;
	CIw2DImage* m_left_image;
	CIw2DImage* m_right_image;

	CIw2DImage* m_car1_image;
	CIw2DImage* m_car2_image;
	CIw2DImage* m_car3_image;

	AwmButton* m_speed_button;
	AwmButton* m_right_button;
	AwmButton* m_left_button;

	CIwResGroup* imagesGroup;

	AeDynArray<OpponentCar*> m_opponents;

	int maximum_cars;
};

#endif