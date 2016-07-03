//
//  SpiderOptionLayer.h
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__SpiderOptionLayer__
#define __cardgame__SpiderOptionLayer__

#include "Common.h"

class SpiderOptionLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
    void onSelEasyMode(CCObject* sender);
    void onSelNormalMode(CCObject* sender);
    void onSelHardMode(CCObject* sender);
    void onSelExpertMode(CCObject* sender);
    void onDone(CCObject* sender);
    
private:
    void createMenuWithEasy();
    void createMenuWithNormal();
    void createMenuWithExpert();
    void createMenuWithHard();
    
private:
    CCLayer* _parentLayer;
    CCMenuItem* _easyItem;
    CCMenuItem* _normalItem;
    CCMenuItem* _expertItem;
    CCMenuItem* _hardItem;
    CCMenu* _menu;
    
public:
    CREATE_FUNC(SpiderOptionLayer);
};

#endif
