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
	void loadSpine(const char* _atlas, const char* _skeleton, const char* _animation, int _x, int _y);

private:

	Atlas *atlas;
	SkeletonData *skeletonData;
	Skeleton *skeleton;
	Animation *animation;
	float animationTime;
	uint64 lastFrameTime;
};

#endif