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
    
private:
    void onRandomDeal(Ref* sender);
    void onWinningDeal(Ref* sender);
    void onReplayDeal(Ref* sender);
    void onSelectDeal(Ref* sender);
    void onBack(Ref* sender);
    void didAction();
    
private:
    Layer* _parentLayer;
    MenuItem* _randomDealItem;
    MenuItem* _winningDealItem;
    MenuItem* _replayDealItem;
    MenuItem* _selectDealItem;
    Menu* _menu;
    Sprite* background;   
    
public:
    CREATE_FUNC(NewGameLayer);
};

#endif /* defined(__cardgame__NewGameLayer__) */
