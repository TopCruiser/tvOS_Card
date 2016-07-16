//
//  CardFaceLayer.h
//  cardgame
//
//  Created by lion on 3/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__CardFaceLayer__
#define __cardgame__CardFaceLayer__

#include "Common.h"

class CardFaceLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
private:
    void onCardTap(CCObject* sender);
    void onBack(CCObject* sender);
    
private:
    CCLayer* _parentLayer;
    CCSprite* _background;
    CCSprite* _title;
    CCMenu* _menu;
    
    CCMenuItem* btnBack;
    
    CCMenuItem* btnCard01;
    CCMenuItem* btnCard02;
    CCMenuItem* btnCard03;
    CCMenuItem* btnCard04;
    CCMenuItem* btnCard05;
    CCMenuItem* btnCard06;
    CCMenuItem* btnCard07;
    CCMenuItem* btnCard08;
    CCMenuItem* btnCard09;
    CCMenuItem* btnCard10;
    CCMenuItem* btnCard11;
    CCMenuItem* btnCard12;
    CCMenuItem* btnCard13;
    CCMenuItem* btnCard14;
    CCMenuItem* btnCard15;

    
    CCSprite* sprite00;
    CCSprite* sprite01;
    CCSprite* sprite02;
    CCSprite* sprite03;
    CCSprite* sprite04;
    CCSprite* sprite05;
    CCSprite* sprite06;
    CCSprite* sprite07;
    CCSprite* sprite08;
    CCSprite* sprite09;
    CCSprite* sprite10;
    CCSprite* sprite11;
    CCSprite* sprite12;
    CCSprite* sprite13;
    CCSprite* sprite14;
    
public:
    CREATE_FUNC(CardFaceLayer);
};


#endif /* defined(__cardgame__CardFaceLayer__) */
