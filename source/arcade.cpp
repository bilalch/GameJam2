#include "arcade.h"
#include "observer.h"
#include "AwmSoundManager.h"

#define LEVEL_PROGRESS_COUNTER 50

Arcade::Arcade(int difficulty_level)
{
	loadImages();
	m_scrolling_background = new ScrollingBackground(m_scrolling_image, 3);
	m_playerCar = new PlayerCar(1);
	m_chicken = new Chicken(1);
	initializeButtons();

	difficulty = difficulty_level;
	levelProgressCount = 0;

	AWM_SOUND_MANAGER -> PlaySound ("sounds2/Loops/morning.mp3");
}

Arcade::~Arcade()
{
	unloadImages();
}

void Arcade::loadImages()
{
	imagesGroup = IwGetResManager() -> LoadGroup ("640x960/Arcade/_arcade.group");
	
	m_scrolling_image = Iw2DCreateImageResource("bg");

	m_cart_image = Iw2DCreateImageResource("cart");
	m_box_image	 = Iw2DCreateImageResource("box");
	m_mud_image	 = Iw2DCreateImageResource("mud");

	m_pause_image = Iw2DCreateImageResource("pause-button-unpressed");
	m_enery_bar = Iw2DCreateImageResource("energy-bar");
	m_enery_bar_tray = Iw2DCreateImageResource("energy-bar-tray");
	m_enery_icon = Iw2DCreateImageResource("energy-icon");
}

void Arcade::unloadImages()
{
	if ( m_scrolling_image )
		delete m_scrolling_image;
	m_scrolling_image = NULL;

	if ( m_cart_image )
		delete m_cart_image;
	m_cart_image = NULL;

	if ( m_box_image )
		delete m_box_image;
	m_box_image = NULL;

	if (m_mud_image)
		delete m_mud_image;
	m_mud_image = NULL;

	if (m_pause_image)
		delete m_pause_image;
	m_pause_image = NULL;

	if (m_enery_bar)
		delete m_enery_bar;
	m_enery_bar = NULL;

	if (m_enery_bar_tray)
		delete m_enery_bar_tray;
	m_enery_bar_tray = NULL;

	if (m_enery_icon)
		delete m_enery_icon;
	m_enery_icon = NULL;

	IwGetResManager() -> DestroyGroup(imagesGroup);
}

void Arcade::initializeButtons()
{
	isPaused = false;
	generateLevel();
	
	/*m_speed_button = new AwmButton(m_speed_normal_image,m_speed_pressed_image,OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_speed_normal_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05);
	m_right_button  = new AwmButton(OBSERVER->getDeviceWidth() - m_right_image->GetWidth() - OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_right_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05,m_right_image);
	m_left_button  = new AwmButton(m_right_button->getX1() - m_left_image->GetWidth() - OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_left_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05,m_left_image);*/

	m_pause_button = new AwmButton(m_pause_image,m_pause_image,OBSERVER->getDeviceWidth() - 100,20);
}

void Arcade::destroyButtons()
{
	/*if (m_speed_button)
		delete m_speed_button;
	m_speed_button = NULL;

	if (m_left_button)
		delete m_left_button;
	m_left_button = NULL;

	if (m_right_button)
		delete m_right_button;
	m_right_button = NULL;*/

	if (m_pause_button)
		delete m_pause_button;
	m_pause_button = NULL;
}

void Arcade::draw()
{
	m_scrolling_background -> Draw();

	for (int i = 0; i < m_opponents.GetSize(); i++) {
		
		m_opponents[i]->draw();
	}

	m_playerCar -> draw();
	m_chicken -> draw();
	
	m_pause_button -> Draw();

	Iw2DDrawImage(m_enery_bar_tray, CIwFVec2(m_enery_icon->GetWidth()+10,m_enery_icon->GetHeight()/2));
	
	float width = (float)m_enery_bar_tray->GetWidth()*((float)m_scrolling_background->getSpeed()/(15*OBSERVER->getRatio()));
	Iw2DDrawImageRegion(m_enery_bar, CIwFVec2(m_enery_icon->GetWidth()+10,5+m_enery_icon->GetHeight()/2),CIwFVec2(width,m_enery_bar->GetHeight()),CIwFVec2(0,0),CIwFVec2(width,m_enery_bar->GetHeight()));

	Iw2DDrawImage(m_enery_icon, CIwFVec2(20,20));

	/*m_speed_button -> Draw();
	m_right_button -> Draw();
	m_left_button -> Draw();*/
}

int Arcade::update(sliderStruct& m_slider)
{
	if (!isPaused) {

	/*m_speed_button -> Update();
	m_right_button -> Update();
	m_left_button -> Update();*/
	m_pause_button->Update();

	s3eDeviceBacklightOn();
	m_scrolling_background -> Update();

	m_playerCar -> update(m_scrolling_background->getSpeed());
	m_chicken -> update(m_scrolling_background->getSpeed());
	
	for ( int i = 0; i < m_opponents.GetSize(); i++ ) {
		
		switch (m_opponents[i]->update(m_playerCar, m_scrolling_background))
		{
		case 1:
			//collision with cart
			if (m_playerCar->getSpeed() < 10)
			{
				return 2;//gameover
			}
			else
			{
				m_playerCar->jump(true);
			}
			break;
		case 2:
			//collision with mud
			//GAME OVER
			cout<<"MUD COLLISION"<<endl;
			return 2;//gameover
			break;
		case 3:
			//collision with box from top
			//GAME OVER
			cout<<"BOX COLLISION TOP"<<endl;
			m_playerCar->jump(true);
			break;

		case 4:
			//collision with box from side
			//GAME OVER
			cout<<"BOX COLLISION SIDE"<<endl;
			return 2;//gameover
			break;
		default:
			break;
		};

		switch (m_opponents[i]->update(m_chicken, m_scrolling_background))
		{
		case 1:
			//collision with cart
			m_chicken->jump(true);
			break;
		case 2:
			//collision with mud
			//GAME OVER
			cout<<"MUD COLLISION"<<endl;
			//return 2;//gameover
			break;
		case 3:
			//collision with box from top
			//GAME OVER
			cout<<"BOX COLLISION TOP"<<endl;
			//m_chicken->jump(true);
			break;

		case 4:
			//collision with box from side
			//GAME OVER
			cout<<"BOX COLLISION SIDE"<<endl;
			//return 2;//gameover
			break;
		default:
			break;
		};
	}

	int m_i = 0;
	while (m_i < m_opponents.GetSize()) {
		if (m_opponents[m_i]->getX2() < 0)
		{
			m_opponents.Delete(m_i);
			m_i--;
		}

		m_i++;

		if(m_opponents.GetSize() == 0)
			generateLevel();
	}

	if (levelProgressCount >= LEVEL_PROGRESS_COUNTER)
	{
		return 1;//level complete .. WINNER SCREEN
	}

	}

	return -100;
}

int Arcade::click(float x, float y)
{
	if (!isPaused)
	{
		if (m_pause_button->Click(x,y))
		{
			isPaused = true;
		}
		m_scrolling_background->click(x,y);
		return 0;
	}
	else
	{
		isPaused = false;
	}
}

void Arcade::generateLevel()
{
	int _number = 0;

	if ( difficulty == 4 )
		_number = rand()%10;
	else if ( difficulty == 3 )
		_number = rand()%8;
	else if ( difficulty == 2 )
		_number = rand()%6;
	else
		_number = rand()%4;

	switch(_number)
	{
	case 0:
		generateCase0();
		break;

	case 1:
		generateCase1();
		break;

	case 2:
		generateCase2();
		break;

	case 3:
		generateCase3();
		break;

	case 4:
		generateCase4();
		break;

	case 5:
		generateCase5();
		break;

	case 6:
		generateCase6();
		break;

	case 7:
		generateCase7();
		break;

	case 8:
		generateCase8();
		break;

	case 9:
		generateCase9();
		break;
	};
	
	//generateCase0();
	//generateCase1();
	//generateCase2();
	//generateCase3();
	//generateCase4();
	//generateCase5();
	//generateCase6();
	//generateCase7();
	//generateCase8();
	//generateCase9();

	levelProgressCount++;
}

void Arcade::generateCase0()
{
	// easy
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	cart->setOptimumVelocity(11);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud);
}

void Arcade::generateCase1()
{
	// easy
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	cart->setOptimumVelocity(12);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud1 = new Mud(mud->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud1);
}

void Arcade::generateCase2()
{
	// easy
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	cart->setOptimumVelocity(11);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* box = new Box(mud->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box);
}

void Arcade::generateCase3()
{
	// easy
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	cart->setOptimumVelocity(10);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box);

	Collidable* box2 = new Box(box->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box2);
}

void Arcade::generateCase4()
{
	// medium
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	cart->setOptimumVelocity(12);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud1 = new Mud(mud->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud1);

	Collidable* box = new Box(mud1->getX2() + 70*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box);

	Collidable* mud2 = new Mud(box->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud2);
}

void Arcade::generateCase5()
{
	// medium
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	cart->setOptimumVelocity(11);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box);

	Collidable* mud1 = new Mud(box->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud1);

	Collidable* box1 = new Box(mud1->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	box1->setOptimumVelocity(11);
	m_opponents.Add(box1);

	Collidable* mud2 = new Mud(box1->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud2);

	Collidable* mud3 = new Mud(mud2->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud3);
}

void Arcade::generateCase6()
{
	// hard
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	cart->setOptimumVelocity(15);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud1 = new Mud(mud->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud1);

	Collidable* mud2 = new Mud(mud1->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud2);

	Collidable* mud3 = new Mud(mud2->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud3);

	Collidable* box = new Box(mud3->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	box->setOptimumVelocity(12);
	m_opponents.Add(box);

	Collidable* mud4 = new Mud(box->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud4);

	Collidable* mud5 = new Mud(mud4->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud5);

	Collidable* mud6 = new Mud(mud5->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud6);
}

void Arcade::generateCase7()
{
	// hard
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	cart->setOptimumVelocity(15);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10*OBSERVER->getRatio() + 4*m_mud_image->GetWidth()*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box);

	Collidable* mud4 = new Mud(box->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud4);

	Collidable* mud5 = new Mud(mud4->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud5);

	Collidable* mud6 = new Mud(mud5->getX2() + 10*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud6);
}

void Arcade::generateCase8()
{
	// harder
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10*OBSERVER->getRatio() + 4*m_box_image->GetWidth()*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box);

	Collidable* box2 = new Box(box->getX2() + 10*OBSERVER->getRatio() + 4*m_box_image->GetWidth()*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box2);

	Collidable* box3 = new Box(box2->getX2() + 10*OBSERVER->getRatio() + 4*m_box_image->GetWidth()*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 33*OBSERVER->getHeightRatio(),m_box_image->GetWidth()*OBSERVER->getRatio(),m_box_image->GetHeight()*OBSERVER->getRatio(),m_box_image);
	m_opponents.Add(box3);

}

void Arcade::generateCase9()
{
	// harder
	Collidable* cart = new Cart(960*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio(),m_cart_image->GetWidth()*OBSERVER->getRatio(),m_cart_image->GetHeight()*OBSERVER->getRatio(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10*OBSERVER->getRatio() + 4*m_mud_image->GetWidth()*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud2 = new Box(mud->getX2() + 10*OBSERVER->getRatio() + 4*m_mud_image->GetWidth()*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud2);

	Collidable* mud3 = new Box(mud2->getX2() + 10*OBSERVER->getRatio() + 4*m_mud_image->GetWidth()*OBSERVER->getRatio(),400*OBSERVER->getHeightRatio() + 77*OBSERVER->getHeightRatio(),m_mud_image->GetWidth()*OBSERVER->getRatio(),m_mud_image->GetHeight()*OBSERVER->getRatio(),m_mud_image);
	m_opponents.Add(mud3);
}