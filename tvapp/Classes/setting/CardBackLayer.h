//
//  CardBackLayer.h
//  cardgame
//
//  Created by lion on 3/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__CardBackLayer__
#define __cardgame__CardBackLayer__

#include "Common.h"

#include "cocos2d.h"
#include "cocos-ext.h"

class CardBackLayer : public cocos2d::Layer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
    
private:
    void onCardTap(Ref* sender);
    void onBack(Ref*  sender);
    
private:
    Layer* _parentLayer;
    Sprite* _background;
    Sprite* _title;
    Menu* _menu;
    Menu* _btnmenu;
    cocos2d::extension::ScrollView* _ScrollView;
    
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
    MenuItem* btnCard16;
    MenuItem* btnCard17;
    MenuItem* btnCard18;
    MenuItem* btnCard19;
    MenuItem* btnCard20;
    MenuItem* btnCard21;
    MenuItem* btnCard22;
    MenuItem* btnCard23;
    MenuItem* btnCard24;
    MenuItem* btnCard25;
    MenuItem* btnCard26;
    MenuItem* btnCard27;
    MenuItem* btnCard28;
    MenuItem* btnCard29;
    MenuItem* btnCard30;
    MenuItem* btnCard31;
    MenuItem* btnCard32;
    
    //Sprite* _selectedCardBack;
    MenuItem* _selectedCardBack;
    
public:
    CREATE_FUNC(CardBackLayer);
};

#endif /* defined(__cardgame__CardBackLayer__) */