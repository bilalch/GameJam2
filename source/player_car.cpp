#include "player_car.h"
#include "observer.h"

PlayerCar::PlayerCar(int number)
{
	multiplier = 0.5;
	damage = 0;
	switch(number)
	{
	case 1:
		// red car
		loadRedCar();
		break;

	case 2:
		// yellow car
		loadYellowCar();
		break;

	case 3:
		// grey car
		loadGreyCar();
		break;

	default:
		// default is red car as well
		loadRedCar();
		break;
	};

	initializeCar();
	
	m_boy = new SpineChar();
	m_boy->loadSpine("boy.atlas","boy.json","boy-walk.json","boy-grab.json","boy-run.json",x,y);
	
	//initializeSpine();
	//loadSpine();
}

void PlayerCar::initializeSpine()
{
	atlas = NULL;
	skeletonData = NULL;
	skeleton = NULL;
	animation = NULL;
	animationTime = 0;
	lastFrameTime = 0;

	atlas1 = NULL;
	skeletonData1 = NULL;
	skeleton1 = NULL;
	animation1 = NULL;
	animationTime1 = 0;
	lastFrameTime1 = 0;
}

void PlayerCar::loadSpine()
{
  try {
    ifstream atlasFile("spineboy.atlas");
    atlas = new Atlas(atlasFile);

    SkeletonJson skeletonJson(atlas);
	skeletonJson.scale = 0.5;

    ifstream skeletonFile("spineboy-skeleton.json");
    skeletonData = skeletonJson.readSkeletonData(skeletonFile);

    ifstream animationFile("spineboy-walk.json");
    animation = skeletonJson.readAnimation(animationFile, skeletonData);

    skeleton = new Skeleton(skeletonData);
    skeleton->flipX = false;
    skeleton->flipY = false;
    skeleton->setToBindPose();
	skeleton->getRootBone()->x = x;
    skeleton->getRootBone()->y = y;
	
    skeleton->updateWorldTransform();
  } catch (exception &ex) {
    cout << ex.what() << endl << flush;
  }

    try {
    ifstream atlasFile1("chicken.atlas");
    atlas1 = new Atlas(atlasFile1);

    SkeletonJson skeletonJson1(atlas1);
	skeletonJson1.scale = 0.5;

    ifstream skeletonFile1("chicken-skeleton.json");
    skeletonData1 = skeletonJson1.readSkeletonData(skeletonFile1);

    ifstream animationFile1("chicken-running.json");
    animation1 = skeletonJson1.readAnimation(animationFile1, skeletonData1);

    skeleton1 = new Skeleton(skeletonData1);
    skeleton1->flipX = false;
    skeleton1->flipY = false;
    skeleton1->setToBindPose();
	skeleton1->getRootBone()->x = 100;
    skeleton1->getRootBone()->y = 300;
    skeleton1->updateWorldTransform();
  } catch (exception &ex) {
    cout << ex.what() << endl << flush;
  }
}

PlayerCar::~PlayerCar()
{
	unloadCar();
}

void PlayerCar::loadRedCar()
{
	//imagesGroup = IwGetResManager() -> LoadGroup ("640x960/Arcade/_arcade.group");

	//spriteSheet = new Iw2DSprite(IwGetResManager()->GetCurrentGroup(), "blowfish", true);
}

void PlayerCar::loadYellowCar()
{

}


void PlayerCar::loadGreyCar()
{

}

void PlayerCar::unloadCar()
{
	/*if ( spriteSheet )
		delete spriteSheet;
	spriteSheet = NULL;*/
}

void PlayerCar::draw()
{
	//spriteSheet->Render(CIwFVec2(x,y),1.0f,0.0f,0.0f);
	//IwGxFlush();
	//skeleton->draw();
	//skeleton1->draw();
	m_boy->draw();
}

void PlayerCar::updateSpine()
{
  float dt = (float)(s3eTimerGetMs() - lastFrameTime);
  lastFrameTime = s3eTimerGetMs();
  
  if (jumping){
	animationTime += 0;        // ms to s
  } else {
	animationTime += dt / 500.f;        // ms to s
  }
  animationTime1 += dt / 1000.f;
  skeleton->getRootBone()->x = x;
  skeleton->getRootBone()->y = y;
  
  animation->apply(skeleton, animationTime, true);
  skeleton->updateWorldTransform();

  animation1->apply(skeleton1, animationTime1, true);
  skeleton1->updateWorldTransform();
}

void PlayerCar::update(float speed)
{
	m_boy->update(x,y);
	//updateSpine();
	//spriteSheet->Step();
	car_speed = speed;
	if (jumping)
	{
		//skeleton->getRootBone()->rotation = -30;
		if (y + jumpVelocity < groundY)
		{
			y = y + jumpVelocity;
			jumpVelocity = jumpVelocity + gravity;
		}
		else
		{
			jumping = false;
			m_boy->land();
		}
	}
	else
	{
		//skeleton->getRootBone()->rotation = 0;
	}
}

void PlayerCar::jump()
{
	if (!jumping)
	{
		if (car_speed < 10) {
			
			jumpVelocity = -2.5f*10;
		} else if ( car_speed > 10 ) {

			jumpVelocity = -2.5f*car_speed;
		} else {

			jumpVelocity = -2.5f*car_speed;
		}
		jumping = true;
		m_boy->jump();
	}
}

void PlayerCar::initializeCar()
{
	x = 200;
	y = 500;
	initY = y;
	
	gravity = 2;
	jumping = false;
	jumpVelocity = -30;
	groundY = initY;
}

void PlayerCar::verifySpeedBounds()
{
	if ( car_speed < 0 ) {
		
		car_speed = 0;
	} else if ( car_speed > 40 ) {
		
		car_speed = 40;
	}
}