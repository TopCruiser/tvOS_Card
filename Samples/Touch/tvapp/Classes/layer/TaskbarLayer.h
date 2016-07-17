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
    
    void onSetting(CCObject* sender);
    void onCenter(CCObject* sender);
    void onStore(CCObject* sender);
    void onMenu(CCObject* sender);
    void onNewGame(CCObject* sender);
    void onUndo(CCObject* sender);
    void onHint(CCObject* sender);
    
    void showNewGame();
    void didNewGame();
    void didExitLayer(bool isYes);
    
    void removeStoreButton();
    
private:
    MenuItem* createItem(const char* szNormalSpritePath, const char* szActiveSpritePath, const char* szTitle,
                           float width, float height, CCObject* target, SEL_MenuHandler selector);
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