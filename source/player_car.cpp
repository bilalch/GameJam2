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
	/*switch(damage)
	{
	case 0:
		Iw2DDrawImage(image1,CIwSVec2(m_x1,m_y1),CIwSVec2(image1->GetWidth()*multiplier,image1->GetHeight()*multiplier));
		break;

	case 1:
		Iw2DDrawImage(image2,CIwSVec2(m_x1,m_y1),CIwSVec2(image2->GetWidth()*multiplier,image2->GetHeight()*multiplier));
		break;

	case 2:
		Iw2DDrawImage(image3,CIwSVec2(m_x1,m_y1),CIwSVec2(image3->GetWidth()*multiplier,image3->GetHeight()*multiplier));
		break;

	case 3:
		Iw2DDrawImage(image4,CIwSVec2(m_x1,m_y1),CIwSVec2(image4->GetWidth()*multiplier,image4->GetHeight()*multiplier));
		break;

	case 4:
		Iw2DDrawImage(image5,CIwSVec2(m_x1,m_y1),CIwSVec2(image5->GetWidth()*multiplier,image5->GetHeight()*multiplier));
		break;

	default:
		Iw2DDrawImage(image1,CIwSVec2(m_x1,m_y1),CIwSVec2(image1->GetWidth()*multiplier,image1->GetHeight()*multiplier));
		break;
	};*/

	spriteSheet->Render(CIwSVec2(OBSERVER->getDeviceWidth()/2,OBSERVER->getDeviceHeight()/2),1.0f,0.0f,0.0f);

}

void PlayerCar::update()
{
	spriteSheet->Step();
}

void PlayerCar::initializeCar()
{
	/*m_x1 = (OBSERVER->getDeviceWidth() - image1->GetWidth()*multiplier)/2;
	m_y1 = OBSERVER->getDeviceHeight() - image1->GetHeight()*multiplier;
	m_width = image1->GetWidth()*multiplier;
	m_height = image1->GetHeight()*multiplier;
	m_x2 = m_x1 + m_width;
	m_y2 = m_y1 + m_height;*/
}

void PlayerCar::verifySpeedBounds()
{
	if ( car_speed < 0 ) {
		
		car_speed = 0;
	} else if ( car_speed > 40 ) {
		
		car_speed = 40;
	}
}