#include "player_car.h"
#include "observer.h"
#include "AwmSoundManager.h"

PlayerCar::PlayerCar(int number)
{
	initializeCar();
	
	m_boy = new SpineChar();
	m_boy->loadSpine("boy.atlas","boy.json","boy-run.json","boy-takeoff.json","boy-run.json","boy-wave.json","boy-slip.json",x,y,0.5);
	
	//initializeSpine();
	//loadSpine();
}

PlayerCar::~PlayerCar()
{

}

void PlayerCar::draw()
{
	m_boy->draw();
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
			y = groundY;
			jumping = false;
			m_boy->land();
			AWM_SOUND_MANAGER->PlaySoundEffect("running");
		}
	}
	else
	{
		//skeleton->getRootBone()->rotation = 0;
	}
}

void PlayerCar::jump(bool fromBoxTopCollision)
{
	if (!jumping || fromBoxTopCollision)
	{
		if (car_speed < 10*OBSERVER->getRatio()) {
			
			jumpVelocity = -2.5f*car_speed*OBSERVER->getRatio();
		} else if ( car_speed > 10*OBSERVER->getRatio() ) {

			jumpVelocity = -2.5f*car_speed*OBSERVER->getRatio();
		} else {

			jumpVelocity = -2.5f*car_speed*OBSERVER->getRatio();
		}
		jumping = true;
		m_boy->jump();
		AWM_SOUND_MANAGER->PlaySoundEffect("thud");
	}
}

void PlayerCar::initializeCar()
{
	x = 200*OBSERVER->getRatio();
	y = 530*OBSERVER->getHeightRatio();
	initY = y;
	
	gravity = 2*OBSERVER->getRatio();
	jumping = false;
	jumpVelocity = -30*OBSERVER->getRatio();
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