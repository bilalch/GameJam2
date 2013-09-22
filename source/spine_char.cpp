#include "spine_char.h"

SpineChar::SpineChar()
{
	atlas = NULL;
	skeletonData = NULL;
	skeleton = NULL;
	animation = NULL;
	animationTime = 0;
	lastFrameTime = 0;
}

SpineChar::~SpineChar()
{
  delete skeleton;
  delete skeletonData;
  delete animation;
  delete atlas;
}

void SpineChar::loadSpine(const char* _atlas, const char* _skeleton, const char* _animation, int _x, int _y)
{
	try {
		ifstream atlasFile(_atlas);
		atlas = new Atlas(atlasFile);

		SkeletonJson skeletonJson(atlas);
		skeletonJson.scale = 0.5;

		ifstream skeletonFile(_skeleton);
		skeletonData = skeletonJson.readSkeletonData(skeletonFile);

		ifstream animationFile(_animation);
		animation = skeletonJson.readAnimation(animationFile, skeletonData);

		skeleton = new Skeleton(skeletonData);
		skeleton->flipX = false;
		skeleton->flipY = false;
		skeleton->setToBindPose();
		skeleton->getRootBone()->x = _x;
		skeleton->getRootBone()->y = _y;

		skeleton->updateWorldTransform();
	} catch (exception &ex) {
		cout << ex.what() << endl << flush;
	}
}

void SpineChar::draw()
{
	IwGxFlush();
	skeleton->draw();
}

void SpineChar::update(int _x, int _y)
{
  float dt = (float)(s3eTimerGetMs() - lastFrameTime);
  lastFrameTime = s3eTimerGetMs();

  skeleton->getRootBone()->x = _x;
  skeleton->getRootBone()->y = _y;
  
  animation->apply(skeleton, animationTime, true);
  skeleton->updateWorldTransform();
}

void SpineChar::update()
{
  float dt = (float)(s3eTimerGetMs() - lastFrameTime);
  lastFrameTime = s3eTimerGetMs();
  
  animation->apply(skeleton, animationTime, true);
  skeleton->updateWorldTransform();
}