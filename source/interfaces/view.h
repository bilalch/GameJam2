/*
 *  view.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines interface for draw operations.
 ** Each drawable class should implement this interface
 */

#ifndef VIEW_INTERFACE
#define VIEW_INTERFACE

#include <string>
#include <iostream>
#include "structures.h"
#include "Iw2D.h"
#include "IwResManager.h"

using namespace std;

class View {
public:
	View(){
		zIndex = -1;
		visible = true;
		name = "";
	}

	~View(){
	
	}

	string getName();
	virtual void setName(string _name){ name= _name; }
	virtual bool isActive() { return active; }
	virtual void setActive(bool _active) { active = _active; }
	virtual int getZIndex() { return zIndex; }
	virtual void setZIndex(int z_index) { zIndex = z_index; }
	virtual bool isVisible() { return visible; }
	virtual void setIsVisible(bool _visible) { visible = _visible; }
	virtual void draw() = 0;
	virtual bool update(sliderStruct &_slider) = 0;
	virtual int click(float _x, float _y) = 0;

protected:
	int zIndex;
	bool visible;
	bool active;
	string name;
};

#endif