/*
 * The structures class holds all the structs
 * that may be used inside the game
 * 
 * It will basically help with removing redundant
 * structs
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include "string.h"
#include "iostream.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
struct slotCoordinates_center
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int m_x1_moving;
	int m_y1_moving;
	int m_width_moving;
	int m_height_moving;
	
	int m_x_center;
	int m_y_center;

	bool status;
};

////////////////////////////////////////////////////////////////////////////


struct menu_Coordinates
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int m_x1_moving;
	int m_width_moving;
	int m_height_moving;

	bool status;
};

struct basic_Coordinates
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;
};

struct slotCoordinates_movingY
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int m_y1_moving;

	bool status;
};

struct basicCoordinates_status
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	bool status;
};

struct basicButton
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	bool pressed;
};

enum PhoneType
{
	IPHONE3,
	IPHONE4,
	IPAD,
	ANDROID1,
	ANDROID_TABLET,
};

struct sliderStruct
{
	bool moveable;	// if the elements are more than the screen capacity
	bool pressed;	// if touch is down
	bool click;		// to test for touch down and release at same location
	bool left;		// moving left flag
	bool right;		// moving right flag

	int touchX;		//-----------------------// 
	int prevX;		//   to detect touch	 //
	bool whichTouch;//-----------------------//
	
	int time;		// time of flick
	int distance;	// distance of flick
	int distanceX1;	// initial X value to calculate distance
	int distanceY1;	// intital Y value to calculate distance
	int velocity;	// velocity of movement
	int timeX1;		// intial TIME value to calculate time

	int x1;
	int y1;
	int x2;
	int y2;

	int moveX1;		// for touch and move
	int moveX2;		// for touch and move
	
	int moveY1;
	int moveY2;
	int velocityX;
	int velocityY;
	bool up;
	bool down;

	int touchY;
	int prevY;
	bool whichTouch2;

	int id;			// touch id - only needed for multi-touch

	bool swipe_left;
	bool swipe_right;
	bool swipe_up;
	bool swipe_down;
	bool swipe;
};

enum LoginEnum
{
	LOGIN_PRE_MAIN,
	LOGIN_MAIN,
	LOGIN_LOGGING,
	LOGIN_SPYRA,
	LOGIN_SPYRA_B,
	LOGIN_SPYRA_ONE,
	AUTO
};

enum LoginSpyra
{
	SPYRA_NONE,
	SPYRA_LOGIN,
	SPYRA_LOGIN_EMAIL,
	SPYRA_LOGIN_PASS,
	SPYRA_NAME,
	SPYRA_PASS,
	SPYRA_CONFIRM_PASS,
	SPYRA_EMIAL,
	SPYRA_RETREIVE_PASS,
	SPYRA_QUICK_USERNAME
};

enum RegistrationEnum
{
	NONE,
	RERROR,
	SUCCESS,
};

enum ContinentEnum
{
	CONTINENT_MAIN,
	CONTINENT_CHOOSE_OPPONENT,
	CONTINENT_CHOOSE_OPPONENT_1,
	CONTINENT_LOADING,
	CONTINENT_LOADING_1,
	CONTINENT_BATTLE,
	CONTINENT_DEPLOY_ARMY,
	CONTINENT_DEPLOY_ARMY_1,
	CONTINENT_DEPLOY_ARMY_LOADING,
	CONTINENT_BATTLE_MENU,
	CONTINENT_RESULT_1,
	CONTINENT_RESULT_2,
	CONTINENT_RESULT_3,
	CONTINENT_RESULT_FINAL,
	CONTINENT_RESULT_LOADING,
};

enum AcceptBattleEnum
{
	AB_MAIN,
	AB_ACCEPT,
	AB_BATTLE_MENU,
	AB_RESULT_1,
	AB_RESULT_2,
	AB_RESULT_3,
	AB_RESULT_FINAL,
	AB_RESULT_LOADING,
	AB_RESULT_LOADING_1,
	AB_ANIMATION,
};

enum BarracksEnum
{
	BARRACKS_ICON,
	BARRACKS_MENU_BARRACKS,
	BARRACKS_MENU_LAND,
	BARRACKS_MENU_SEA,
	BARRACKS_MENU_AIR,
	BARRACKS_MENU_OPENING,
	BARRACKS_MENU_CLOSING,
	BARRACKS_DIALOGUE_HARD_COIN,
	BARRACKS_DIALOGUE_SOFT_COIN,
};

enum InAppEnum
{
	INAPP_MAIN,
	INAPP_LOADING,
	INAPP_INFO,
	INAPP_BUY,
	INAPP_PURCHASING,
	INAPP_HIGHLIGHT
};

enum TutorialState{
	TUTORIAL_1_1,
	TUTORIAL_1_2,
	TUTORIAL_1_3,
	TUTORIAL_1_4,
	TUTORIAL_1_5,
	TUTORIAL_1_6,
	TUTORIAL_1_7,
	TUTORIAL_1_8,
	TUTORIAL_2_1,
	TUTORIAL_2_2,
	TUTORIAL_2_3,
	TUTORIAL_2_4,
	TUTORIAL_2_5,
	TUTORIAL_2_6,
	TUTORIAL_2_7,
	TUTORIAL_2_8,
	TUTORIAL_2_8_1,
	TUTORIAL_2_9,
	TUTORIAL_2_10,
	TUTORIAL_2_11,
	TUTORIAL_2_12,
	TUTORIAL_2_13,
	TUTORIAL_2_14,
	TUTORIAL_2_15,
	TUTORIAL_2_16,
	TUTORIAL_2_17,
	TUTORIAL_2_17_1,
	TUTORIAL_2_18,
	TUTORIAL_2_18_1,
	TUTORIAL_2_19,
	TUTORIAL_3_1,
	TUTORIAL_3_2,
	TUTORIAL_3_3,
	TUTORIAL_3_4,
	TUTORIAL_3_4_1,
	TUTORIAL_3_4_2,
	TUTORIAL_3_4_3,
	TUTORIAL_3_5,
	TUTORIAL_3_6,
	TUTORIAL_3_7,
	TUTORIAL_3_8,
	TUTORIAL_3_9,
	TUTORIAL_3_10,
};

enum ProductionSlotStatus
{
	SLOT_EMPTY = 1,
	SLOT_FULL = 2,
	SLOT_READY = 3,
};

struct cloudStruct
{
	int x1;
	int x2;
	int y1;
	int y2;
	int width;
	int height;
	int speed;
	int type;
	bool status;
	bool speedType;
	int count;
	int cloudChange;
	int cloudType;

	int delayCount;
};

struct opponent_Coordinates
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int name_x1;
	int name_y1;
	int name_x2;
	int name_y2;
	int name_width;
	int name_height;

	int level_x1;
	int level_y1;
	int level_x2;
	int level_y2;
	int level_width;
	int level_height;

	int xp_x1;
	int xp_y1;
	int xp_x2;
	int xp_y2;
	int xp_width;
	int xp_height;

	int rank_x1;
	int rank_y1;
	int rank_x2;
	int rank_y2;
	int rank_width;
	int rank_height;

	int char_x1;
	int char_y1;
	int char_x2;
	int char_y2;
	int char_width;
	int char_height;

	int button_x1;
	int button_y1;
	int button_x2;
	int button_y2;
	int button_width;
	int button_height;
	bool button_pressed;

	int won_x1;
	int won_y1;
	int won_x2;
	int won_y2;
	int won_width;
	int won_height;
};

struct battlePullUp
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int name_x1;
	int name_y1;
	int name_x2;
	int name_y2;
	int name_width;
	int name_height;

	int level_x1;
	int level_y1;
	int level_x2;
	int level_y2;
	int level_width;
	int level_height;

	int xp_x1;
	int xp_y1;
	int xp_x2;
	int xp_y2;
	int xp_width;
	int xp_height;

	int rank_x1;
	int rank_y1;
	int rank_x2;
	int rank_y2;
	int rank_width;
	int rank_height;

	int char_x1;
	int char_y1;
	int char_x2;
	int char_y2;
	int char_width;
	int char_height;

	int status_x1;
	int status_y1;
	int status_x2;
	int status_y2;
	int status_width;
	int status_height;
	bool status_pressed;

	int close_x1;
	int close_y1;
	int close_x2;
	int close_y2;
	int close_width;
	int close_height;

	bool status;
	int whichOpponent;
};

struct battleStruct
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int count1_x1;
	int count1_y1;
	int count1_x2;
	int count1_y2;
	int count1_width;
	int count1_height;

	int count2_x1;
	int count2_y1;
	int count2_x2;
	int count2_y2;
	int count2_width;
	int count2_height;

	int attack1_x1;
	int attack1_y1;
	int attack1_x2;
	int attack1_y2;
	int attack1_width;
	int attack1_height;

	int attack2_x1;
	int attack2_y1;
	int attack2_x2;
	int attack2_y2;
	int attack2_width;
	int attack2_height;

	int unit1_x1;
	int unit1_y1;
	int unit1_x2;
	int unit1_y2;
	int unit1_width;
	int unit1_height;

	int unit2_x1;
	int unit2_y1;
	int unit2_x2;
	int unit2_y2;
	int unit2_width;
	int unit2_height;

	int rank1_x1;
	int rank1_y1;
	int rank1_x2;
	int rank1_y2;
	int rank1_width;
	int rank1_height;

	int rank2_x1;
	int rank2_y1;
	int rank2_x2;
	int rank2_y2;
	int rank2_width;
	int rank2_height;

	int continent1_x1;
	int continent1_y1;
	int continent1_x2;
	int continent1_y2;
	int continent1_width;
	int continent1_height;

	int continent2_x1;
	int continent2_y1;
	int continent2_x2;
	int continent2_y2;
	int continent2_width;
	int continent2_height;

	int chance1_x1;
	int chance1_y1;
	int chance1_x2;
	int chance1_y2;
	int chance1_width;
	int chance1_height;

	int chance2_x1;
	int chance2_y1;
	int chance2_x2;
	int chance2_y2;
	int chance2_width;
	int chance2_height;

	int battleVs_x1;
	int battleVs_y1;
	int battleVs_x2;
	int battleVs_y2;
	int battleVs_width;
	int battleVs_height;

	int round_x1;
	int round_y1;
	int round_x2;
	int round_y2;
	int round_width;
	int round_height;

	int result_x1;
	int result_y1;
	int result_x2;
	int result_y2;
	int result_width;
	int result_height;
};

struct moneyTab
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int count_x1;
	int count_y1;
	int count_x2;
	int count_y2;
	int count_width;
	int count_height;

	int price_x1;
	int price_y1;
	int price_x2;
	int price_y2;
	int price_width;
	int price_height;
};

struct productionSlotCoord
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	int light_x1;
	int light_y1;
	int light_x2;
	int light_y2;
	int light_width;
	int light_height;

	int base_x1;
	int base_y1;
	int base_x2;
	int base_y2;
	int base_width;
	int base_height;

	int time_x1;
	int time_y1;
	int time_x2;
	int time_y2;
	int time_width;
	int time_height;

	int time_base_x1;
	int time_base_y1;
	int time_base_x2;
	int time_base_y2;
	int time_base_width;
	int time_base_height;

	int production_time;
};

struct reward_Slot
{
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_width;
	int m_height;

	bool completed;
	bool highlighted;
	bool previousHighlighted;
	bool first;
	bool last;

	int numberOfrewards;

	int slot1_x1;
	int slot1_y1;
	int slot1_x2;
	int slot1_y2;
	int slot1_width;
	int slot1_height;

	int slot2_x1;
	int slot2_y1;
	int slot2_x2;
	int slot2_y2;
	int slot2_width;
	int slot2_height;

	int slot3_x1;
	int slot3_y1;
	int slot3_x2;
	int slot3_y2;
	int slot3_width;
	int slot3_height;

	int text1_x1;
	int text1_y1;
	int text1_x2;
	int text1_y2;
	int text1_width;
	int text1_height;

	int text2_x1;
	int text2_y1;
	int text2_x2;
	int text2_y2;
	int text2_width;
	int text2_height;

	int text3_x1;
	int text3_y1;
	int text3_x2;
	int text3_y2;
	int text3_width;
	int text3_height;

	int day_x1;
	int day_y1;
	int day_x2;
	int day_y2;
	int day_width;
	int day_height;

	string day_name;
};

struct touchStruct
{
	int32 id;
	bool pressed;
	int32 m_x;
	int32 m_y;
};
#endif //_STRUCTURES_H