#include "player_car.h"
#include "observer.h"

PlayerCar::PlayerCar(int number)
{
	initializeCar();
	
	m_boy = new SpineChar();
	m_boy->loadSpine("boy.atlas","boy.json","boy-run.json","boy-takeoff.json","boy-run.json","boy-wave.json","boy-slip.json",x,y);
	
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
		if (car_speed < 10) {
			
			jumpVelocity = -2.5f*car_speed;
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
	y = 530;
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