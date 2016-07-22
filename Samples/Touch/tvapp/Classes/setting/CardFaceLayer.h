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

class CardFaceLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
private:
    void onCardTap(Ref* sender);
    void onBack(Ref* sender);
    
private:
    Layer* _parentLayer;
    Sprite* _background;
    Sprite* _title;
    Menu* _menu;
    
    MenuItem* btnBack;
    
    MenuItem* btnCard01;
    MenuItem* btnCard02;
    MenuItem* btnCard03;
    MenuItem* btnCard04;
    MenuItem* btnCard05;
    MenuItem* btnCard06;
    MenuItem* btnCard07;
    MenuItem* btnCard08;
    MenuItem* btnCard09;
    MenuItem* btnCard10;
    MenuItem* btnCard11;
    MenuItem* btnCard12;
    MenuItem* btnCard13;
    MenuItem* btnCard14;
    MenuItem* btnCard15;

    
    Sprite* sprite00;
    Sprite* sprite01;
    Sprite* sprite02;
    Sprite* sprite03;
    Sprite* sprite04;
    Sprite* sprite05;
    Sprite* sprite06;
    Sprite* sprite07;
    Sprite* sprite08;
    Sprite* sprite09;
    Sprite* sprite10;
    Sprite* sprite11;
    Sprite* sprite12;
    Sprite* sprite13;
    Sprite* sprite14;
    
public:
    CREATE_FUNC(CardFaceLayer);
};


#endif /* defined(__cardgame__CardFaceLayer__) */
