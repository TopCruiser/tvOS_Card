//
//  SolitaireOptionLayer.h
//  cardgame
//
//  Created by Pink on 2/10/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__SolitaireOptionLayer__
#define __cardgame__SolitaireOptionLayer__

#include "Common.h"

class SolitaireOptionLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
    void onSelDrawThree(CCObject* sender);
    void onSelVegasStyle(CCObject* sender);
    void onDone(CCObject* sender);

private:
    CCLayer* _parentLayer;
    CCMenuItem* _drawthreeItem;
    CCMenuItem* _drawthreeLabel;
    CCMenuItem* _vegasItem;
    CCMenuItem* _vegasLabel;
    CCMenu* _menu;
    
public:
    CREATE_FUNC(SolitaireOptionLayer);
};

#endif