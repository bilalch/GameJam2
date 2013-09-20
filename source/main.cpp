#include "my_game.h"
#include "MessageBox.h"

int main ()
{
	MyGame* m_game = new MyGame();

	srand(0);
	
	if ( m_game -> IsMultitouch() ) {
		
		// multitouch is available
		m_game->InitializeTouch(true);
	} else {
		
		// multitouch is not available
		//MessageBox("Uh Oh!", "This game only works on mutitouch enabled devices");
		m_game->InitializeTouch();
	}

	//m_game -> InitializeSound ("sounds/sounds.group", "sounds");
	m_game -> InitializeFonts ("fonts/Iw2DStrings.group", "MrBubbleFont12");

	uint64 fpsSetter = 0;//for fps setting

	while  (!s3eDeviceCheckQuitRequest())
	{
		fpsSetter = s3eTimerGetMs();

		Iw2DSurfaceClear (0xff000000);

		m_game->Update();

		m_game->Draw();

//		if (m_game->getGameState() == GAME_PLAY)
//			AdTest_Show(false);
//		else
//			AdTest_Show(true);

//		AdTest_Update();
		Iw2DSetColour(0xffffffff);
		Iw2DSetTransformMatrix(CIwMat2D::g_Identity);

		Iw2DSurfaceShow();

		fpsSetter = s3eTimerGetMs() - fpsSetter;

		fpsSetter = 33333 - fpsSetter;
		
		if (fpsSetter >= 0)
			s3eDeviceYield(fpsSetter/1000);
		else
			s3eDeviceYield(0);
	}
}