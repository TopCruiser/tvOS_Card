//
//  AppDelegate.h
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "cocos2d.h"
#include "../CCApplication.h"

class  AppDelegate : private cocos2d::Application
{
public:
    
    static AppDelegate* get() { return (AppDelegate*)cocos2d::Application::getInstance(); }
    AppDelegate();
    virtual ~AppDelegate();
    
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
    
    void onOrientationChanged(int orientation);    
    void receivedFromNative(int nType, std::string strParam, int nParam);
    bool sendMessageToNative(int nType, const char* msg, int nParam);
    
    bool _isBanner;
    
};

