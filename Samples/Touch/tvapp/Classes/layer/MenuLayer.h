//
//  MenuLayer.h
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Common.h"

class MenuLayer : public cocos2d::Layer
{
public:
    static Scene* scene();
    
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    void onSolitaire(Ref* sender);
    void onFreeCell(Ref* sender);
    void onFortyThieves(Ref* sender);
    void onSpiderSolitaire(Ref* sender);
    
private:
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
private:
    Sprite* _background;
    Sprite* _title;
    Menu* _menu;

public:
    CREATE_FUNC(MenuLayer);
};
