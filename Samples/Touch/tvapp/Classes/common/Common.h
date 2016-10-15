//
//  Common.h
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__Common__
#define __cardgame__Common__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

enum ORIENTATION_TYPE
{
    ORIENTATION_UNKNOWN = 0,
    ORIENTATION_PORTRAIT,
    ORIENTATION_PORTRAIT_UPSIDEDOWN,
    ORIENTATION_LANDSCAPE_LEFT,
    ORIENTATION_LANDSCAPE_RIGHT,
};

enum OPTION_TYPE
{
    TYPE_SOLITAIRE = 0,
    TYPE_FREECELL,
    TYPE_FORTY_THIEVES,
    TYPE_SPIDER,
};

enum MESSAGE_TYPE
{
    MSG_ORIENTATION = 0,
    MSG_SELECTFREECELL,
    MSG_TELL_A_FRIEND,
    MSG_FEEDBACK_EMAIL,
    MSG_SUBMIT_SCORE,
    MSG_SUBMIT_ACHIEVE,
    MSG_RANK_ACHIEVE,
    MSG_GAMECENTER,
    MSG_REMOVE_ADS,
    MSG_ADMOB_BANNER,
    MSG_SHOW_CHARTBOOST,
    MSG_SHOW_REWARDEDVIDEO,
    MSG_GOOGLE_ANALYTICS,
    MSG_ADCOLONY_VIDEO,
    MSG_APPIRATER,
    MSG_ASKINGPOINT,
    MSG_NATIVE_BACKGROUND,
    MSG_SHOW_FACEBOOK,
    MSG_SHOW_TWITTER,
    MSG_RESTORE_REQUEST,
    MSG_SMS,
    MSG_EMAIL,
    MSG_REMOVE_ALL_ADS

};

enum ADMOB_BANNER
{
    REMOVE_ADMOB = 0,
    SHOW_ADMOB
};

extern int g_nOrientation;
extern bool g_bTipDisplay;

std::string getNameWithDeviceJpg(std::string name);
std::string getNameWithDeviceIpad(std::string name);
std::string getNameWithDevice(std::string name);
std::string getNameWithResolution(std::string name);

std::string to_string(int num);

float getScaleWithDeviceAppleTV();
float getScaleWithDevice();
float getScaleWithDeviceiPad();
int getSizeWithDevice(int orgSize);
long long getCurrentTime();

#endif
