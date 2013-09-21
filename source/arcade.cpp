#include "arcade.h"
#include "observer.h"

Arcade::Arcade()
{
	maximum_cars = 5;
	loadImages();
	m_scrolling_background = new ScrollingBackground(m_scrolling_image, 3);
	m_playerCar = new PlayerCar(1);
	initializeButtons();
}

Arcade::~Arcade()
{
	unloadImages();
}

void Arcade::loadImages()
{
	imagesGroup = IwGetResManager() -> LoadGroup ("640x960/Arcade/_arcade.group");
	
	m_scrolling_image = Iw2DCreateImageResource("bg");

	m_speed_normal_image = Iw2DCreateImageResource("speed_normal");
	m_speed_pressed_image = Iw2DCreateImageResource("speed_pressed");

	m_left_image = Iw2DCreateImageResource("left");
	m_right_image = Iw2DCreateImageResource("right");

	m_car1_image = Iw2DCreateImageResource("black");
	m_car2_image = Iw2DCreateImageResource("blue");
	m_car3_image = Iw2DCreateImageResource("green");
}

void Arcade::unloadImages()
{
	if ( m_scrolling_image )
		delete m_scrolling_image;
	m_scrolling_image = NULL;

	if ( m_speed_normal_image )
		delete m_speed_normal_image;
	m_speed_normal_image = NULL;

	if ( m_speed_pressed_image )
		delete m_speed_pressed_image;
	m_speed_pressed_image = NULL;

	if ( m_left_image )
		delete m_left_image;
	m_left_image = NULL;

	if ( m_right_image )
		delete m_right_image;
	m_right_image = NULL;

	IwGetResManager() -> DestroyGroup(imagesGroup);
}

void Arcade::initializeButtons()
{
	m_speed_button = new AwmButton(m_speed_normal_image,m_speed_pressed_image,OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_speed_normal_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05);
	m_right_button  = new AwmButton(OBSERVER->getDeviceWidth() - m_right_image->GetWidth() - OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_right_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05,m_right_image);
	m_left_button  = new AwmButton(m_right_button->getX1() - m_left_image->GetWidth() - OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_left_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05,m_left_image);
}

void Arcade::destroyButtons()
{
	if (m_speed_button)
		delete m_speed_button;
	m_speed_button = NULL;

	if (m_left_button)
		delete m_left_button;
	m_left_button = NULL;

	if (m_right_button)
		delete m_right_button;
	m_right_button = NULL;
}

void Arcade::draw()
{
	m_scrolling_background -> Draw();

	/*for (int i = 0; i < m_opponents.GetSize(); i++) {
		
		OpponentCar* temp = (OpponentCar*)m_opponents[i];
		temp->Draw();
	}*/

	m_playerCar -> draw();
	/*m_speed_button -> Draw();
	m_right_button -> Draw();
	m_left_button -> Draw();*/
}

bool Arcade::update(sliderStruct& m_slider)
{
	//spawnOpponents();

	m_speed_button -> Update();
	m_right_button -> Update();
	m_left_button -> Update();
	m_playerCar -> update();
	if ( m_speed_button -> isPressed() ) {
		
		m_playerCar -> accelerate() ;
	} else {

		m_playerCar -> decelerate() ;
	}

	if ( m_right_button -> isPressed() && m_playerCar -> getX2() < m_scrolling_background -> getRightBound() ) {
		
		m_playerCar -> goRight();
	} else if ( m_left_button -> isPressed() && m_playerCar -> getX1() > m_scrolling_background -> getLeftBound() ) {
		
		m_playerCar -> goLeft();
	}

	m_scrolling_background -> Update(m_playerCar->getSpeed());

	for ( int i = 0; i < m_opponents.GetSize(); i++ ) {
		
		OpponentCar* temp = (OpponentCar*)m_opponents[i];
		if ( !temp->Update(m_playerCar) ) {
			
			m_opponents.Delete(i);
		}
	}

	opponentsCollisionHandling();

	return true;
}

int Arcade::click(float x, float y)
{
	m_scrolling_background->click(x,y);
	return 0;
}

void Arcade::spawnOpponents()
{
	if ( m_opponents.GetSize() < maximum_cars ) {
		
		// new car can be added
		int _lane = rand()%3 + 1;
		int _speed = rand()%10 + 10;
		
		if ( laneIsOpen(_lane) ) {

			CIw2DImage* tempImage = randomizeCarImage();
			OpponentCar* temp = new OpponentCar(3,m_scrolling_background->getLeftBound(),m_scrolling_background->getRightBound(),tempImage,_speed);
			temp->setLane(_lane);
			m_opponents.Add(temp);
		}
		
	}
}

CIw2DImage* Arcade::randomizeCarImage()
{
	int number = rand()%3 + 1;
	if ( number == 1 ) {
		
		return m_car1_image;
	} else if ( number == 2 ) {
		
		return m_car2_image;
	} else {
		
		return m_car3_image;
	}
}

bool Arcade::laneIsOpen(int number) 
{
	for (int i = 0; i < m_opponents.GetSize(); i++) {
		
		OpponentCar* temp = (OpponentCar*)m_opponents[i];
		if ( temp->getLane() == number ) {

			if ( temp->getY1() < m_car1_image->GetHeight()*2 ) {
				
				return false;
			}
		}
	}
	return true;
}

void Arcade::opponentsCollisionHandling()
{
	for ( int i = 0; i < m_opponents.GetSize(); i++ ) {
		
		OpponentCar* car1 = (OpponentCar*)m_opponents[i];
		for ( int j = 0; j < m_opponents.GetSize(); j++ ) {
		
			OpponentCar* car2 = (OpponentCar*)m_opponents[j];
			if ( i != j ) {
				
				if ( car1->getLane() == car2->getLane() ) {
					
					if ( car1->getY2() >= car2->getY1() && car1->getY1() < car2->getY2() ) {
					
						// BOOM GOES THE DYNAMITE
						car1->collision();
						car1->setCurrentSpeed(car2->getCurrentSpeed() + 10);
						car2->setCurrentSpeed(car1->getCurrentSpeed() - 10);

					}
				}
			}
		}
	}
}