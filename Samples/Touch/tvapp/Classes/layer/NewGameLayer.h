//
//  NewGameLayer.h
//  cardgame
//
//  Created by lion on 3/11/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__NewGameLayer__
#define __cardgame__NewGameLayer__


#include "Common.h"

class NewGameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void pressBegan();
private:
    void onRandomDeal(Ref* sender);
    void onWinningDeal(Ref* sender);
    void onReplayDeal(Ref* sender);
    void onSelectDeal(Ref* sender);
    void onBack(Ref* sender);
    void didAction();
    
private:
    Layer* _parentLayer;
    Sprite* _randomDealItem;
    Sprite* _winningDealItem;
    Sprite* _replayDealItem;
    Sprite* _selectDealItem;
    MenuItem* btnDone;
    
    Menu* _menu;
    Sprite* background;
    
    MenuItem* arrowSprite;
    Vec2 prevPoint;
    Vec2 lastMovedPoint;
    
public:
    CREATE_FUNC(NewGameLayer);
};

#endif /* defined(__cardgame__NewGameLayer__) */
