//
//  Common.cpp
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Common.h"

int g_nOrientation;

std::string getNameWithDeviceIpad(std::string name)
{
    std::string newName;
    
//#ifdef _MAC_OS_
    newName = name + "_ipadhd.jpg";
//#else
//    newName = "";
//#endif
    return newName;
}

std::string getNameWithDeviceJpg(std::string name)
{
    std::string newName;
    
#ifdef _MAC_OS_
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(winSize.height == 480 || winSize.height == 568 ||
       winSize.width == 480 || winSize.width == 568)
        newName = name + "_iphone.jpg";
    else if(winSize.height == 960 || winSize.height == 1136 ||
            winSize.width == 960 || winSize.width == 1136)
        newName = name + "_iphonehd.jpg";
    else if(winSize.height == 1024 || winSize.width == 1024)
        newName = name + "_ipad.jpg";
    else if(winSize.height == 2048 || winSize.width == 2048)
        newName = name + "_ipadhd.jpg";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_TVOS
    newName = name + "_ipadhd.png";
#else
    newName = "";
#endif
    return newName;
}

std::string getNameWithDevice(std::string name)
{
    std::string newName;
    
#ifdef _MAC_OS_
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(winSize.height == 480 || winSize.height == 568 ||
       winSize.width == 480 || winSize.width == 568)
        newName = name + "_iphone.png";
    else if(winSize.height == 960 || winSize.height == 1136 ||
            winSize.width == 960 || winSize.width == 1136)
        newName = name + "_iphonehd.png";
    else if(winSize.height == 1024 || winSize.width == 1024)
        newName = name + "_ipad.png";
    else if(winSize.height == 2048 || winSize.width == 2048)
        newName = name + "_ipadhd.png";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_TVOS
    newName = name + "_ipadhd.png";
#else
    newName = "";
#endif
    return newName;
}

std::string getNameWithResolution(std::string name)
{
    std::string newName;
    
#ifdef _MAC_OS_
    Size winSize = Director::getInstance()->getWinSize();
    if(winSize.height == 480 || winSize.height == 568 ||
       winSize.width == 480 || winSize.width == 568)
        newName = name + ".png";
    else if(winSize.height == 960 || winSize.height == 1136 ||
            winSize.width == 960 || winSize.width == 1136 ||
            winSize.height == 1024 || winSize.width == 1024)
        newName = name + "_hd.png";
    else if(winSize.height == 2048 || winSize.width == 2048)
        newName = name + "_ipadhd.png";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_TVOS
    newName = name + "_ipadhd.png";
#else
    newName = "";
#endif
    return newName;
}

float getScaleWithDeviceiPad()
{
    float scale = 1.0f;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scaleX = winSize.width / 1536;
    float scaleY = winSize.height / 2048;
    if(scaleY < scaleX)
        scale = scaleY;
    else
        scale = scaleX;
    
    return scale;
}

float getScaleWithDevice()
{
    float scale = 1.0f;
    
#ifdef _MAC_OS_
#else
    Size winSize = Director::getInstance()->getWinSize();
    float scaleX = winSize.width / 1536;
    float scaleY = winSize.height / 2048;
    if(scaleY < scaleX)
        scale = scaleY;
    else
        scale = scaleX;
#endif
    
    return scale;
}

int getSizeWithDevice(int orgSize)
{
    int descSize;
    Size winSize = Director::getInstance()->getWinSize();
    
#ifdef _MAC_OS_
    if(winSize.height == 480 || winSize.height == 568 ||
       winSize.width == 480 || winSize.width == 568)
        descSize = orgSize * 0.5f;
    else if(winSize.height == 960 || winSize.height == 1024 || winSize.height == 1136 ||
            winSize.width == 960 || winSize.width == 1024 || winSize.width == 1136)
        descSize = orgSize * 1.0f;
    else if(winSize.height == 2048 || winSize.width == 2048)
        descSize = orgSize * 2.0f;
#else
    descSize = orgSize * 2.0f * getScaleWithDevice();
#endif
    
    return descSize;
}

long long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    long long time = ((long long)tv.tv_sec) * 1000+ tv.tv_usec / 1000;
    return time;
}

std::string to_string(int num){
    std::ostringstream os;
    os<<num;
    return os.str();
}