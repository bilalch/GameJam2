#include "chicken.h"
#include "observer.h"
#include "AwmSoundManager.h"

Chicken::Chicken(int number)
{
	initializeCar();
	
	m_chicken = new SpineChar();
	m_chicken->loadSpine("chicken.atlas","chicken-skeleton.json",NULL,NULL,"chicken-running.json",NULL,NULL,800,530,0.5);
}

Chicken::~Chicken()
{

}

void Chicken::draw()
{
	m_chicken->draw();
}

void Chicken::update(float speed)
{
	m_chicken->update(x,y);

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
			m_chicken -> land();
		}
	}
	else
	{
		//skeleton->getRootBone()->rotation = 0;
	}
}

void Chicken::jump(bool fromBoxTopCollision)
{
	if (!jumping || fromBoxTopCollision)
	{
		if (car_speed < 10) {
			
			jumpVelocity = -2.5f*car_speed;
		} else if ( car_speed > 10 ) {

			jumpVelocity = -2.5f*car_speed;
		} else {

			jumpVelocity = -2.5f*car_speed;
		}
		jumping = true;
		m_chicken -> jump();
		AWM_SOUND_MANAGER->PlaySoundEffect("chicken");
	}
}

void Chicken::initializeCar()
{
	x = 800;
	y = 530;
	initY = y;
	
	gravity = 2;
	jumping = false;
	jumpVelocity = -30;
	groundY = initY;
}

void Chicken::verifySpeedBounds()
{
	if ( car_speed < 0 ) {
		
		car_speed = 0;
	} else if ( car_speed > 40 ) {
		
		car_speed = 40;
	}
}