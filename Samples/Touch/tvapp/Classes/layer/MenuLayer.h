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
    void onDummy(Ref* sender);
    
private:
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
public:
    MenuItem* btnSolitaire;
private:
    Sprite* _background;
    Sprite* _title;
    Menu* _menu;
    
    
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    bool handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onConnectController(cocos2d::Controller* controller, cocos2d::Event* event);
    void onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event);
    
    void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    
    void onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event);
    
    cocos2d::EventListenerKeyboard* _keybListener = nullptr;
    cocos2d::EventListener* _touchListener = nullptr;
    cocos2d::EventListenerController* _controllerListener = nullptr;

public:
    CREATE_FUNC(MenuLayer);
};
