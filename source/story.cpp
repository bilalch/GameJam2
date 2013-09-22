#include "story.h"

Story::Story()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/Story/_winner.group");

	m_background = Iw2DCreateImageResource("background");
	m_gameWinner = Iw2DCreateImageResource("winning-text");
	m_boyWithChicken = Iw2DCreateImageResource("boy-with-chicken");
}

Story::~Story()
{

}
	
int Story::update()
{

}

void Story::draw()
{

}