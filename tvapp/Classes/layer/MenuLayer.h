//
//  MenuLayer.h
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__MenuLayer__
#define __cardgame__MenuLayer__

#include "Common.h"

class MenuLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    
    void onSolitaire(Ref* sender);
    void onFreeCell(Ref* sender);
    void onFortyThieves(Ref* sender);
    void onSpiderSolitaire(Ref* sender);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
private:
    Sprite* _background;
    Sprite* _title;
    Menu* _menu;
    MenuItem* btnSolitaire;
    
public:
    CREATE_FUNC(MenuLayer);
};

#endif
