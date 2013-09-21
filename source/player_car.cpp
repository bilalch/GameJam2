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
	initializeSpine();
	loadSpine();
}

void PlayerCar::initializeSpine()
{
	atlas = NULL;
	skeletonData = NULL;
	skeleton = NULL;
	animation = NULL;
	animationTime = 0;
	lastFrameTime = 0;
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
    skeleton->getRootBone()->x = 200;
    skeleton->getRootBone()->y = 500;
    skeleton->updateWorldTransform();
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

	spriteSheet = new Iw2DSprite(IwGetResManager()->GetCurrentGroup(), "blowfish", true);
}

void PlayerCar::loadYellowCar()
{

}


void PlayerCar::loadGreyCar()
{

}

void PlayerCar::unloadCar()
{
	if ( spriteSheet )
		delete spriteSheet;
	spriteSheet = NULL;
}

void PlayerCar::draw()
{
<<<<<<< HEAD
	spriteSheet->Render(CIwFVec2(x,y),1.0f,0.0f,0.0f);
	//skeleton->draw();
=======
	//spriteSheet->Render(CIwFVec2(x,y),1.0f,0.0f,0.0f);
	IwGxFlush();
	skeleton->draw();

>>>>>>> c440998b774ae36db3317371f4d993c1381d7292
}

void PlayerCar::updateSpine()
{
  float dt = (float)(s3eTimerGetMs() - lastFrameTime);
  lastFrameTime = s3eTimerGetMs();

  animationTime += dt / 500.f;        // ms to s

  animation->apply(skeleton, animationTime, true);
  skeleton->updateWorldTransform();
}

void PlayerCar::update()
{
	updateSpine();
	spriteSheet->Step();
	//jump();
	if (isJumping)
	{
		if (y > jumpMaxY && jumpingUp)
		{
			/*if (y > jumpMaxY + 3*((initY - jumpMaxY)/4))
			{
				drawImg = jumpImg2;
			}
			else if (y > jumpMaxY + 2*((initY - jumpMaxY)/4))
			{
				drawImg = jumpImg2;
			}
			else if (y > jumpMaxY + ((initY - jumpMaxY)/4))
			{
				drawImg = jumpImg3;
			}*/
			y -= (initY - jumpMaxY)/(jumpCount*3);
			if (jumpCount < 9)
				jumpCount++;
		}
		else if (y < initY)
		{
			/*if (y < jumpMaxY + ((initY - jumpMaxY)/4))
			{
				drawImg = jumpImg3;
			}
			else if (y < jumpMaxY + 2*((initY - jumpMaxY)/4))
			{
				drawImg = jumpImg3;
			}
			else if (y > jumpMaxY + 3*((initY - jumpMaxY)/4))
			{
				drawImg = jumpImg3;
			}*/
			y += (initY - jumpMaxY)/(jumpCount*3);
			if (jumpCount > 3)
			jumpCount--;
			jumpingUp = false;
		}
		else
		{
			y = initY;
			isJumping = false;
			jumpingUp = false;
			jumpCount = 3;
		}
	}

	if (jumping)
	{
		if (y + jumpVelocity < groundY)
		{
			y = y + jumpVelocity;
			jumpVelocity = jumpVelocity + gravity;
		}
		else
		{
			jumping = false;
		}
	}
	else
	{
		jumpVelocity = -30;
		jumping = true;
	}

}

void PlayerCar::initializeCar()
{
	/*m_x1 = (OBSERVER->getDeviceWidth() - image1->GetWidth()*multiplier)/2;
	m_y1 = OBSERVER->getDeviceHeight() - image1->GetHeight()*multiplier;
	m_width = image1->GetWidth()*multiplier;
	m_height = image1->GetHeight()*multiplier;
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;*/

	isJumping = false;
	jumpingUp = false;

	x = OBSERVER->getDeviceWidth()*0.25;
	y = OBSERVER->getDeviceHeight()*0.66;
	initY = y;
	jumpMaxY = initY - (200.0/640)*OBSERVER->getDeviceHeight();
	jumpCount = 3;

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

void PlayerCar::jump()
{
	if (!isJumping)
	{
		isJumping = true;
		jumpingUp = true;
	}
}