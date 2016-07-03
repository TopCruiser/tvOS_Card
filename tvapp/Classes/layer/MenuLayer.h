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

class MenuLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    
    void onSolitaire(CCObject* sender);
    void onFreeCell(CCObject* sender);
    void onFortyThieves(CCObject* sender);
    void onSpiderSolitaire(CCObject* sender);
    
private:
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
private:
    CCSprite* _background;
    CCSprite* _title;
    CCMenu* _menu;
    
public:
    CREATE_FUNC(MenuLayer);
};

#endif
