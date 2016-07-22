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

class SolitaireOptionLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    void onSelDrawThree(Ref* sender);
    void onSelVegasStyle(Ref* sender);
    void onDone(Ref* sender);
    void onDummy(Ref* sender);
    
    bool handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    Layer* _parentLayer;
    MenuItem* _drawthreeItem;
    MenuItem* _drawthreeLabel;
    MenuItem* _vegasItem;
    MenuItem* _vegasLabel;
    Menu* _menu;
    
public:
    CREATE_FUNC(SolitaireOptionLayer);
};

#endif