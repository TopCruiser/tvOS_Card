//
//  MenuLayer.h
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Common.h"
#include "TipLayer.h"

class MenuLayer : public cocos2d::Layer
{
public:
    static Scene* scene();
    
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    
    void onSolitaire(Ref* sender);
    void onFreeCell(Ref* sender);
    void onFortyThieves(Ref* sender);
    void onSpiderSolitaire(Ref* sender);
    void onDummy(Ref* sender);
    void hideHintLayer();
    void pressBegan();
    
private:
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
public:
    TipLayer* tipLayer;
    
    MenuItem* btnSolitaire;
    MenuItem* btnForty;
    MenuItem* btnFreecell;
    MenuItem* btnSpider;
    
    MenuItem* arrowSprite;
    
    Vec2 prevPoint;
private:
    Sprite* _background;
    Sprite* _title;
    Menu* _menu;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);

public:
    cocos2d::Vec2 lastMovedPoint;
public:
    CREATE_FUNC(MenuLayer);
};
