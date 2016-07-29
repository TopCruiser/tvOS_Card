//
//  TaskbarLayer.h
//  cardgame
//
//  Created by Pink on 2/12/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__TaskbarLayer__
#define __cardgame__TaskbarLayer__

#include "Common.h"
#include "NewGameLayer.h"
#include "ExitLayer.h"

#include "SpiderOptionLayer.h"
#include "SolitaireOptionLayer.h"

class TaskbarLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
    void onSetting(Ref* sender);
    void onCenter(Ref* sender);
    void onStore(Ref* sender);
    void onMenu(Ref* sender);
    void onNewGame(Ref* sender);
    void onUndo(Ref* sender);
    void onHint(Ref* sender);
    void onDummy(Ref* sender);
    void showNewGame();
    void didNewGame();
    void didExitLayer(bool isYes);
    
    void removeStoreButton();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    bool pressesBegan(Vec2 touchPoint);
    
private:
    MenuItem* createItem(const char* szNormalSpritePath, const char* szActiveSpritePath, const char* szTitle,
                           float width, float height, Ref* target, SEL_MenuHandler selector);
private:
    Layer* _parentLayer;
    Sprite* _background;
    Menu* _menu;
    MenuItem* _settingItem;
    MenuItem* _centerItem;
    MenuItem* _storeItem = NULL;
    MenuItem* _menuItem;
    MenuItem* _playItem;
    MenuItem* _undoItem;
    MenuItem* _hintItem;
    NewGameLayer* _newGameLayer;
    ExitLayer* _exitLayer;
    int _exitKind;
    
    
    SpiderOptionLayer* _spiderOptionLayer;
    SolitaireOptionLayer* _solitaireOptionLayer;
    
public:
    CREATE_FUNC(TaskbarLayer);
};

#endif