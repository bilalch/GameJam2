/*
 *  game.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines interface for game operations.
 ** Game class should implement this interface
 **
 ** If sound manager is not working correctly chances are you forgot
 ** to call IwGetSoundManager()->Update(); when you over wrote the 
 ** game Update function
 */

#ifndef GAME_INTERFACE
#define GAME_INTERFACE

#include <string>
#include <iostream>
#include <hash_map>
#include "dynamicArray.h"
//#include "view.h"
#include "structures.h"
#include "Iw2D.h"
#include "IwResManager.h"
#include "AwmSoundManager.h"



using namespace std;

class Game {
public:
	Game();

	~Game();

/*	virtual View * getView(string _name){
		return activeViews[_name];
	}

	virtual View * getView(int index){
		return activeViews[activeViewKeys[index]];
	}

	virtual void addView(string _name, View *_view){
		activeViews[_name] = _view;
		activeViewKeys.Add(_name);
		SortViews();
	}

	virtual void removeView(string _name){
		activeViews.erase(_name);
		int indexToDelete = activeViewKeys.Search(_name);
		
		if(indexToDelete > -1)
			activeViewKeys.Delete(indexToDelete);
	}

	virtual int activeViewsCount(){
		activeViewKeys.GetSize();
	}
	*/

	/*
	 *	InitializeTouch() should be called right
	 *	after a new game object has been created
	 */
	virtual void InitializeTouch(bool multitouch = false);

	/*
	 *	InitializeSound() should be called to get linked
	 *	to the AwmSoundManager. Once sound is initialized
	 *	sound manager may be accessed using the singleton
	 *	AWM_SOUND_MANAGER
	 */
	virtual void InitializeSound(const char* groupPath, const char* groupName);

	virtual void InitializeFonts(const char* groupPath, const char* fontName);

	virtual void Draw() = 0;
	virtual void Update() = 0;

	virtual void Clicker(float x, float y);
	//virtual void Clicker(float x, float y);

	bool IsMultitouch() { return m_multitouch_available; }

	sliderStruct getSliderStruct() { return m_slider; }

	bool getSound() { 
		
		if ( m_soundManager )
			return true;
		return false;
	}

protected:
//	hash_map<string, View *> activeViews;
//	AeDynArray<string> activeViewKeys;

	sliderStruct m_slider;

	bool m_multitouch_available;

	AwmSoundManager* m_soundManager;

	CIw2DFont* m_font;

private:
//	void SortViews();
	void InitializeSlider();
};

#endif