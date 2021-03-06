/*
 * this class defines an object of spine character
 *
 */

#ifndef SPINE_CHAR_H
#define SPINE_CHAR_H

#include "Iw2D.h"
#include "IwResManager.h"
#include "Iw2DSprite.h"
#include <iostream>
#include <fstream>
#include <spine-marm/spine.h>

using namespace std;
using namespace spine;

class SpineChar
{
public:
	SpineChar();
	~SpineChar();

	void update(int _x, int _y);
	void update();
	void draw();
	void loadSpine(const char* _atlas, const char* _skeleton, 
		const char* _animation_walk, const char* _animation_jump, 
		const char* _animation_run, const char* _animation_wave, const char* _animation_slip,
		int _x, int _y, float _scale); // Pass null if animation does not exist
	
	void jump();
	void land();
	void run();
	void walk();
	void wave();

private:

	Atlas *atlas;
	SkeletonData *skeletonData;
	Skeleton *skeleton;
	Animation *animation_walk;
	Animation *animation_run;
	Animation *animation_jump;
	Animation *animation_wave;
	Animation *animation_slip;
	float animationTime;
	uint64 lastFrameTime;

	bool isWalking;
	bool isRunning;
	bool isJumping;
	bool isWaving;

	void setAngle(int angle_degrees);
};

#endif