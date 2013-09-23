#include "spine_char.h"
#include "observer.h"

SpineChar::SpineChar()
{
	atlas = NULL;
	skeletonData = NULL;
	skeleton = NULL;
	animation_walk = NULL;
	animation_run = NULL;
	animation_jump = NULL;
	animationTime = 0;
	lastFrameTime = 0;

	isJumping = false;
	isWalking = true;
	isRunning = false;
	isWaving = false;
}

SpineChar::~SpineChar()
{
  delete skeleton;
  delete skeletonData;
  delete animation_walk;
  delete animation_run;
  delete animation_jump;
  delete atlas;
}

void SpineChar::loadSpine(const char* _atlas, const char* _skeleton, const char* _animation_walk, const char* _animation_jump,
	const char* _animation_run, const char* _animation_wave, const char* _animation_slip, int _x, int _y, float _scale)
{
	try {
		ifstream atlasFile(_atlas);
		atlas = new Atlas(atlasFile);

		SkeletonJson skeletonJson(atlas);
		skeletonJson.scale = _scale*OBSERVER->getRatio();

		ifstream skeletonFile(_skeleton);
		skeletonData = skeletonJson.readSkeletonData(skeletonFile);

		if ( _animation_walk ) {

			ifstream animationFile(_animation_walk);
			animation_walk = skeletonJson.readAnimation(animationFile, skeletonData);
		}

		if ( _animation_jump ) {

			ifstream animationFile2(_animation_jump);
			animation_jump = skeletonJson.readAnimation(animationFile2, skeletonData);
		}

		if ( _animation_run ) {
			
			ifstream animationFile3(_animation_run);
			animation_run = skeletonJson.readAnimation(animationFile3, skeletonData);
		}

		if ( _animation_wave ) {
			
			ifstream animationFile4(_animation_wave);
			animation_wave = skeletonJson.readAnimation(animationFile4, skeletonData);
		}

		if ( _animation_slip ) {
			
			ifstream animationFile5(_animation_slip);
			animation_slip = skeletonJson.readAnimation(animationFile5, skeletonData);
		}

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

void SpineChar::jump()
{
	isJumping = true;
	setAngle(-10);
}

void SpineChar::land()
{
	isJumping = false;
	setAngle(0);
}

void SpineChar::run()
{
	isRunning = true;
	isWalking = false;
}

void SpineChar::walk()
{
	isRunning = false;
	isWalking = true;
}

void SpineChar::wave()
{
	isWaving = true;
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

  if (isJumping)
	animationTime += dt / 10000.f;
  else
	animationTime += dt / 1000.f;
  
  skeleton->getRootBone()->x = _x;
  skeleton->getRootBone()->y = _y;

  if ( isWaving )
	  animation_wave->apply(skeleton, animationTime, true);
  else
	  animation_run->apply(skeleton, animationTime, true);
  
/*  if (isJumping)
	animation_jump->apply(skeleton, animationTime, true);
  else if (isRunning)
	animation_run->apply(skeleton, animationTime, true);
  else if (isWalking)
	animation_walk->apply(skeleton, animationTime, true);
*/
  skeleton->updateWorldTransform();
}

void SpineChar::setAngle(int angle_degrees)
{
	skeleton->getRootBone()->rotation = angle_degrees;
}

void SpineChar::update()
{
  float dt = (float)(s3eTimerGetMs() - lastFrameTime);
  lastFrameTime = s3eTimerGetMs();

  if (isJumping)
	animationTime += dt / 10000.f;
  else
	animationTime += dt / 1000.f;

  if ( isWaving )
	  animation_wave->apply(skeleton, animationTime, true);
  else
	  animation_run->apply(skeleton, animationTime, true);
  
/*  if (isJumping)
	animation_jump->apply(skeleton, animationTime, false);
  else if (isRunning)
	animation_run->apply(skeleton, animationTime, true);
  else if (isWalking)
	animation_walk->apply(skeleton, animationTime, true);
*/
  skeleton->updateWorldTransform();
}