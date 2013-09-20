/*
 * This class describes an object of Sound Manager - it is basically
 * an encapsulation around the CIwSound Engine provided by Marmalade
 * 
 * This class will be a global singleton so that classes can initiate sounds
 * The classes will only have the abililty to play sounds and will not get access
 * to loading or changing them
 * 
 *
 * 
 * 
 * 
 * 
 */

#ifndef _AWMSOUNDMANAGER_H
#define _AWMSOUNDMANAGER_H

#include "IwSound.h"
#include <string>
#include <iostream>

#define AWM_SOUND_MANAGER	AwmSoundManager::getInstance()

using namespace std;

class AwmSoundManager
{
public:
	AwmSoundManager();
	~AwmSoundManager();
	static AwmSoundManager * getInstance();
	void Create();
	void Destroy();
	void Init(const char*, const char*);
	void PlaySoundEffect(const char*);
	void PlaySound(const char*);
	void PlayDelayedSound(const char*, int _delay);
	void PlayDelayedSoundOnce(const char*, int _delay);
	void StopSound();
	void PauseSound();
	void ResumeSound();
	void StopSoundEffects();
	void update();
	
	void SetSoundEffectsFlag(bool);
	void SetSoundFlag(bool);
	bool GetSoundEffectsFlag();
	bool GetSoundFlag();
	//void setSoundChange(bool); -- dont need it now..

private:
	CIwResGroup* SoundsGroup;
	bool soundFlag;
	bool soundEffectsFlag;
	bool soundChange;
	static AwmSoundManager *_instance;
	string currentSound;
	int delayedSound;
	string delayedSoundStr;
	bool onceFlag;
};

#endif //_AWMSOUNDMANAGER_H