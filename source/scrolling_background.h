/*
 * this class defines an object of a scrolling background
 *
 * the update of this object should be passed a speed variable from the player car
 * ** idea ** maybe we can pass an object of car as const so that it cannot be tampered with
 *
 * this should also be able to scroll whatever image is passed to it and draw it centered
 */

#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include "Iw2D.h"
#include "structures.h"
#include "level_generator.h"

#define THREE_LANE_RATIO 0.5
#define TWO_LANE_RATIO 1

class ScrollingBackground
{
public:
	ScrollingBackground(CIw2DImage* image, int lanes);
	~ScrollingBackground();
	void Update();
	void Draw();

	float getSpeed();
	float getScrollSpeed();

	float getMultiplier() { return multiplier; }
	float getRightBound() { return m_right_bound; }
	float getLeftBound() { return m_left_bound; }

	int click(float x, float y);

private:
	void initializeLaneBounds();

	basic_Coordinates image1;
	basic_Coordinates image2;

	CIw2DImage* m_image;
	float multiplier;

	CIw2DImage* m_tile1;
	CIw2DImage* m_tile2;
	CIw2DImage* m_tile3;

	CIw2DImage* m_path;

	basic_Coordinates path1;
	basic_Coordinates path2;

	CIw2DImage* m_bg;

	int m_lanes;
	float m_left_bound;
	float m_right_bound;

	float m_speed;

	int m_worldAngle;
	int leftMostTile;

	int centerTile;
	float centerTile_x1;

	int leftMostTile_x1;
	float tileWidth;

	int tileCount;

	LevelGenerator* m_levelGenerator;

	void ScrollTile();

	float scale;
};

#endif