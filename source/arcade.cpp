#include "arcade.h"
#include "observer.h"

Arcade::Arcade()
{
	loadImages();
	m_scrolling_background = new ScrollingBackground(m_scrolling_image, 3);
	m_playerCar = new PlayerCar(1);
	initializeButtons();

	difficulty = 1;
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
}

void Arcade::unloadImages()
{
	if ( m_scrolling_image )
		delete m_scrolling_image;
	m_scrolling_image = NULL;

	if ( m_cart_image )
		delete m_cart_image;
	m_cart_image = NULL;

	IwGetResManager() -> DestroyGroup(imagesGroup);
}

void Arcade::initializeButtons()
{
	generateLevel();
	/*m_speed_button = new AwmButton(m_speed_normal_image,m_speed_pressed_image,OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_speed_normal_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05);
	m_right_button  = new AwmButton(OBSERVER->getDeviceWidth() - m_right_image->GetWidth() - OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_right_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05,m_right_image);
	m_left_button  = new AwmButton(m_right_button->getX1() - m_left_image->GetWidth() - OBSERVER->getDeviceWidth()*0.05,OBSERVER->getDeviceHeight() - m_left_image->GetHeight() - OBSERVER->getDeviceWidth()*0.05,m_left_image);*/
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
}

void Arcade::draw()
{
	m_scrolling_background -> Draw();

	for (int i = 0; i < m_opponents.GetSize(); i++) {
		
		m_opponents[i]->draw();
	}

	m_playerCar -> draw();
	
	/*m_speed_button -> Draw();
	m_right_button -> Draw();
	m_left_button -> Draw();*/
}

int Arcade::update(sliderStruct& m_slider)
{
	/*m_speed_button -> Update();
	m_right_button -> Update();
	m_left_button -> Update();*/
	s3eDeviceBacklightOn();
	m_scrolling_background -> Update();

	m_playerCar -> update(m_scrolling_background->getSpeed());
	
	for ( int i = 0; i < m_opponents.GetSize(); i++ ) {
		
		switch (m_opponents[i]->update(m_playerCar, m_scrolling_background))
		{
		case 1:
			//collision with cart
			m_playerCar->jump(false);
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
	return -100;
}

int Arcade::click(float x, float y)
{
	m_scrolling_background->click(x,y);
	return 0;
}

void Arcade::generateLevel()
{
/*	int _number = 0;

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
	*/
	//generateCase0();
	//generateCase1();
	//generateCase2();
	//generateCase3();
	generateCase4();
	//generateCase5();
	//generateCase6();
	//generateCase7();
	//generateCase8();
	//generateCase9();
}

void Arcade::generateCase0()
{
	// easy
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	cart->setOptimumVelocity(11);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud);
}

void Arcade::generateCase1()
{
	// easy
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	cart->setOptimumVelocity(12);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud1 = new Mud(mud->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud1);
}

void Arcade::generateCase2()
{
	// easy
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	cart->setOptimumVelocity(11);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* box = new Box(mud->getX2() + 10,400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box);
}

void Arcade::generateCase3()
{
	// easy
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	cart->setOptimumVelocity(10);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10,400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box);

	Collidable* box2 = new Box(box->getX2() + 10,400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box2);
}

void Arcade::generateCase4()
{
	// medium
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud1 = new Mud(mud->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud1);

	Collidable* box = new Box(mud1->getX2() + 70,400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box);

	Collidable* mud2 = new Mud(box->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud2);
}

void Arcade::generateCase5()
{
	// medium
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10,400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box);

	Collidable* mud1 = new Mud(box->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud1);

	Collidable* box1 = new Box(mud1->getX2() + 10,400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box1);

	Collidable* mud2 = new Mud(box1->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud2);

	Collidable* mud3 = new Mud(mud2->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud3);
}

void Arcade::generateCase6()
{
	// hard
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud1 = new Mud(mud->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud1);

	Collidable* mud2 = new Mud(mud1->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud2);

	Collidable* mud3 = new Mud(mud2->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud3);

	Collidable* box = new Box(mud3->getX2() + 10,400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box);

	Collidable* mud4 = new Mud(box->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud4);

	Collidable* mud5 = new Mud(mud4->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud5);

	Collidable* mud6 = new Mud(mud5->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud6);
}

void Arcade::generateCase7()
{
	// hard
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10 + 4*m_mud_image->GetWidth(),400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box);

	Collidable* mud4 = new Mud(box->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud4);

	Collidable* mud5 = new Mud(mud4->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud5);

	Collidable* mud6 = new Mud(mud5->getX2() + 10,400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud6);
}

void Arcade::generateCase8()
{
	// harder
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* box = new Box(cart->getX2() + 10 + 4*m_box_image->GetWidth(),400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box);

	Collidable* box2 = new Box(box->getX2() + 10 + 4*m_box_image->GetWidth(),400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box2);

	Collidable* box3 = new Box(box2->getX2() + 10 + 4*m_box_image->GetWidth(),400 + 33,m_box_image->GetWidth(),m_box_image->GetHeight(),m_box_image);
	m_opponents.Add(box3);

}

void Arcade::generateCase9()
{
	// harder
	Collidable* cart = new Cart(960,400,m_cart_image->GetWidth(),m_cart_image->GetHeight(),m_cart_image);
	m_opponents.Add(cart);

	Collidable* mud = new Mud(cart->getX2() + 10 + 4*m_mud_image->GetWidth(),400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud);

	Collidable* mud2 = new Box(mud->getX2() + 10 + 4*m_mud_image->GetWidth(),400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud2);

	Collidable* mud3 = new Box(mud2->getX2() + 10 + 4*m_mud_image->GetWidth(),400 + 77,m_mud_image->GetWidth(),m_mud_image->GetHeight(),m_mud_image);
	m_opponents.Add(mud3);
}