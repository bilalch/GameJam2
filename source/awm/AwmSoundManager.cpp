#include "AwmSoundManager.h"
#include "s3e.h"

AwmSoundManager * AwmSoundManager::_instance = 0;

void AwmSoundManager::SetSoundEffectsFlag(bool _flag){
	soundEffectsFlag = _flag;
	if(!soundEffectsFlag)
		StopSoundEffects();
}

void AwmSoundManager::SetSoundFlag(bool _flag){
	soundFlag = _flag;
	if(!soundFlag)
		s3eAudioPause();
	else
		s3eAudioResume();
}

bool AwmSoundManager::GetSoundEffectsFlag(){
	return soundEffectsFlag;
}

bool AwmSoundManager::GetSoundFlag(){
	return soundFlag;
}

AwmSoundManager::AwmSoundManager()
{
	// constructor
	delayedSound = -1;
	onceFlag = false;
}

AwmSoundManager::~AwmSoundManager()
{
	// destructor
}

AwmSoundManager * AwmSoundManager::getInstance(){
	return _instance;
}

void AwmSoundManager::Create(){
	if(_instance == NULL)
	{
		_instance = new AwmSoundManager();
	}
}

void AwmSoundManager::Destroy(){
	if(_instance != NULL)
	{
		delete _instance;
		_instance = NULL;
	}
}

void AwmSoundManager::Init(const char* groupPath, const char* groupName){

	#ifdef IW_BUILD_RESOURCES
		// Tell resource system how to convert WAV files
		IwGetResManager()->AddHandler(new CIwResHandlerWAV);
	#endif

	IwGetResManager()->LoadGroup(groupPath);
	SoundsGroup = IwGetResManager()->GetGroupNamed(groupName);

	soundFlag = true;
	soundEffectsFlag = true;
	soundChange = false;
	currentSound = "sounds/Loops/MainTheme.mp3";
	PlaySound(currentSound.c_str());
}

void AwmSoundManager::PlaySoundEffect(const char* whichSoundEffect){
	if(soundEffectsFlag){
		CIwSoundSpec* SoundSpec = (CIwSoundSpec*)SoundsGroup->GetResNamed(whichSoundEffect, IW_SOUND_RESTYPE_SPEC);
		CIwSoundInst* SoundInstance = SoundSpec->Play();
	}
}

void AwmSoundManager::StopSoundEffects(){
	IwGetSoundManager()->StopAll();
}

void AwmSoundManager::PlaySound(const char* soundPath){
	if(soundFlag){
		if (s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3))
			s3eAudioPlay(soundPath, 0);
	}
	else{
		//save the sound path in a variable - play it when audio is resumed
		soundChange = true;
		currentSound = soundPath;
	}
}

void AwmSoundManager::PlayDelayedSound(const char* soundPath, int _delay){
	if(soundFlag){
		//if (s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3))
			//s3eAudioPlay(soundPath, 0);
		delayedSound = _delay;
		delayedSoundStr = soundPath;
		//onceFlag = true;
	}
	else{
		//save the sound path in a variable - play it when audio is resumed
		soundChange = true;
		currentSound = soundPath;
	}
}

void AwmSoundManager::PlayDelayedSoundOnce(const char* soundPath, int _delay){
	if(soundFlag){
		delayedSound = _delay;
		delayedSoundStr = soundPath;
		onceFlag = true;
	}
}

void AwmSoundManager::update(){
	if(delayedSound > 0)
		delayedSound--;
	else if(delayedSound == 0){
		if(onceFlag){
			s3eAudioPlay(delayedSoundStr.c_str(), 1);
			onceFlag = false;
		}
		else
			s3eAudioPlay(delayedSoundStr.c_str(), 0);
		delayedSound--;
	}
}

void AwmSoundManager::StopSound(){
	s3eAudioStop();
}

void AwmSoundManager::PauseSound(){
	s3eAudioPause();
}

void AwmSoundManager::ResumeSound(){
	if(!soundChange){
		s3eAudioResume();
	}else{
		s3eAudioStop();
		s3eAudioPlay(currentSound.c_str(),0);
	}
}

//void AwmSoundManager::setSoundChange(bool abc)
//{
//	soundChange=abc;
//}