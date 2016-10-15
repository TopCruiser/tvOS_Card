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

class SpiderOptionLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void pressBegan();
    void onSelEasyMode(Ref* sender);
    void onSelNormalMode(Ref* sender);
    void onSelHardMode(Ref* sender);
    void onSelExpertMode(Ref* sender);
    void onDone(Ref* sender);
    
private:
    void createMenuWithEasy();
    void createMenuWithNormal();
    void createMenuWithExpert();
    void createMenuWithHard();
    
private:
    Layer* _parentLayer;
    MenuItem* _easyItem;
    MenuItem* _normalItem;
    MenuItem* _expertItem;
    MenuItem* _hardItem;
    MenuItem* btnDone;
    
    Menu* _menu;
    
    MenuItem* arrowSprite;
    Vec2 prevPoint;
    Vec2 lastMovedPoint;
    
public:
    CREATE_FUNC(SpiderOptionLayer);
};

#endif
