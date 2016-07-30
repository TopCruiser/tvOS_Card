//
//  NewGameLayer.cpp
//  cardgame
//
//  Created by lion on 3/11/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "NewGameLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "AppDelegate.h"
#include "BoardLayer.h"

enum NEW_GAME {
    RANDOM_DEAL = 0,
    WINNING_DEAL,
    REPLAY_DEAL,
    SELECT_DEAL
};

cocos2d::Scene* NewGameLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    NewGameLayer* layer = NewGameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool NewGameLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void NewGameLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    background= Sprite::create(getNameWithResolution("dialog_new_deal").c_str());
    
    background->setScale(getScaleWithDevice());
    background->setPosition(Vec2(0.0f, 0.0f));
    addChild(background);
    
    Size size = background->getContentSize();
    setContentSize(size);
    
    _randomDealItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_random_nor").c_str()),
                                               Sprite::create(getNameWithResolution("btn_random_act").c_str()),
                                               this, menu_selector(NewGameLayer::onRandomDeal));
    
    _winningDealItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_winning_nor").c_str()),
                                           Sprite::create(getNameWithResolution("btn_winning_act").c_str()),
                                           this, menu_selector(NewGameLayer::onWinningDeal));
    
    _replayDealItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_replay_nor").c_str()),
                                               Sprite::create(getNameWithResolution("btn_replay_act").c_str()),
                                               this, menu_selector(NewGameLayer::onReplayDeal));
    
    MenuItem* btnDone = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_back_nor").c_str()),
                                                   CCSprite::create(getNameWithResolution("btn_back_act").c_str()),
                                                   this, menu_selector(NewGameLayer::onBack));
    
    _randomDealItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    _winningDealItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    _replayDealItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnDone->setAnchorPoint(Vec2(0.5f, 0.0f));
    
    _randomDealItem->setScale(getScaleWithDevice());
    _winningDealItem->setScale(getScaleWithDevice());
    _replayDealItem->setScale(getScaleWithDevice());
    
    btnDone->setScale(getScaleWithDevice());
    btnDone->setPosition(Vec2(getSizeWithDevice(0.0f),  -size.height/2.0f + getSizeWithDevice(32.0f)));
    
    _menu = Menu::create();
    _menu->addChild(_randomDealItem);
    _menu->addChild(_winningDealItem);
    _menu->addChild(_replayDealItem);
    
    if(GameData::getInstance()->getGameType()==1){//freecell
        _selectDealItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_select_nor").c_str()),
                                                   Sprite::create(getNameWithResolution("btn_select_act").c_str()),
                                                   this, menu_selector(NewGameLayer::onSelectDeal));
        _selectDealItem->setAnchorPoint(Vec2(0.5f, 0.5f));
        _selectDealItem->setScale(getScaleWithDevice());
        _menu->addChild(_selectDealItem);
        
        _randomDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(85.0f)));
        _winningDealItem->setPosition(Vec2(getSizeWithDevice(10.0f),getSizeWithDevice(20.0f)));
        _replayDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(-45.0f)));
        _selectDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(-110.0f)));
        
    }
    else{
        _randomDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(80.0f)));
        _winningDealItem->setPosition(Vec2(getSizeWithDevice(10.0f),getSizeWithDevice(0.0f)));
        _replayDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(-80.0f)));
    }
    
    _menu->addChild(btnDone);
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
}

void NewGameLayer::onRandomDeal(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    GameData::getInstance()->setNewGame(RANDOM_DEAL);
    GameData::getInstance()->setSelectedGame(0);
    ((TaskbarLayer*)_parentLayer)->didNewGame();
    BoardLayer::getInstance()->replayGame();
    
}

void NewGameLayer::onWinningDeal(Ref* sender)
{
    //if(GameData::getInstance()->getNewGame()==3) return;
    
    GameData::getInstance()->playSoundEffect();
    
    GameData::getInstance()->setNewGame(WINNING_DEAL);
    ((TaskbarLayer*)_parentLayer)->didNewGame();
    BoardLayer::getInstance()->replayGame();
    
}

void NewGameLayer::onReplayDeal(Ref* sender)
{
    //if(GameData::getInstance()->getNewGame()==3) return;
    
    GameData::getInstance()->playSoundEffect();
    
    GameData::getInstance()->setNewGame(REPLAY_DEAL);
    ((TaskbarLayer*)_parentLayer)->didNewGame();
    BoardLayer::getInstance()->replayGame();
    
}

void NewGameLayer::onSelectDeal(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    //long i = arc4random() % 1000001;
    //AppDelegate::get()->sendMessageToNative(MSG_SELECTFREECELL, "SelectFreecell", i);comment715
    
    ((TaskbarLayer*)_parentLayer)->didNewGame();    
}

void NewGameLayer::onBack(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    Size winSize = Director::getInstance()->getWinSize();
    MoveTo *_move_to = MoveTo::create(0.3f,Vec2( winSize.width /2, winSize.height));
    
    EaseIn *_easein = EaseIn::create(_move_to,0.3f);
    CallFunc *_functionCall = CallFunc::create(this,callfunc_selector(NewGameLayer::didAction));
    Sequence *_sequence  =  Sequence::create( _easein, _functionCall ,NULL);
    this->runAction(_sequence);
    
    BoardLayer::getInstance()->setPreviousMode();

}

void NewGameLayer::didAction()
{
    ((TaskbarLayer*)_parentLayer)->didNewGame();
}
