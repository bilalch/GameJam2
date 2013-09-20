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
	spriteSheet->Render(CIwSVec2(x,y),1.0f,0.0f,0.0f);
}

void PlayerCar::update()
{
	spriteSheet->Step();
	jump();
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