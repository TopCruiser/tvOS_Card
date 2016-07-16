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

class NewGameLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
private:
    void onRandomDeal(CCObject* sender);
    void onWinningDeal(CCObject* sender);
    void onReplayDeal(CCObject* sender);
    void onSelectDeal(CCObject* sender);
    void onBack(CCObject* sender);
    void didAction();
    
private:
    CCLayer* _parentLayer;
    CCMenuItem* _randomDealItem;
    CCMenuItem* _winningDealItem;
    CCMenuItem* _replayDealItem;
    CCMenuItem* _selectDealItem;
    CCMenu* _menu;
    CCSprite* background;   
    
public:
    CREATE_FUNC(NewGameLayer);
};

#endif /* defined(__cardgame__NewGameLayer__) */
