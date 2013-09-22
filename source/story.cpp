#include "story.h"

Story::Story()
{
	imagesGroup = IwGetResManager()->LoadGroup("640x960/Story/_story.group");

	m_background = Iw2DCreateImageResource("background");
	m_dialog = Iw2DCreateImageResource("dailgue-box");
}

Story::~Story()
{
	if ( m_background )
		delete m_background;
	m_background = NULL;

	if ( m_dialog )
		delete m_dialog;
	m_dialog = NULL;

	IwGetResManager()->DestroyGroup(imagesGroup);
}
	
int Story::update()
{
	return 1;
}

void Story::draw()
{
	Iw2DDrawImage(m_background,CIwFVec2(0,0),CIwFVec2(OBSERVER->getDeviceWidth(),OBSERVER->getDeviceHeight()));
	Iw2DDrawImage(m_dialog,CIwFVec2((OBSERVER->getDeviceWidth()-m_dialog->GetWidth())/2 + 130,(OBSERVER->getDeviceHeight()-m_dialog->GetHeight())/2));	
}

int Story::click(float x, float y)
{
	return -1;
}