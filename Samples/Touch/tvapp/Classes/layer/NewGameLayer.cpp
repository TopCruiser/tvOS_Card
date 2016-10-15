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
    
    Sprite *testSprite = Sprite::create(getNameWithResolution("btn_random_nor"));
    testSprite->setAnchorPoint(Vec2(0.5, 0.5));
    testSprite->setScale(getScaleWithDevice());
    
    _randomDealItem = Sprite::create(getNameWithResolution("btn_random_nor"));
    _winningDealItem = Sprite::create(getNameWithResolution("btn_winning_nor"));
    _replayDealItem = Sprite::create(getNameWithResolution("btn_replay_nor"));
    
    btnDone = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_back_nor").c_str()),
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
    
    if(GameData::getInstance()->getGameType()==1){//freecell
        _selectDealItem = Sprite::create(getNameWithResolution("btn_select_nor"));
        _selectDealItem->setAnchorPoint(Vec2(0.5f, 0.5f));
        _selectDealItem->setScale(getScaleWithDevice());
        
        _randomDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(85.0)));
        _winningDealItem->setPosition(Vec2(getSizeWithDevice(10.0f),getSizeWithDevice(25.0)));
        _replayDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(-40)));
        _selectDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(-100.0)));
        addChild(_selectDealItem);
        
    }
    else{
        _randomDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(80)));
        _winningDealItem->setPosition(Vec2(getSizeWithDevice(10.0f),getSizeWithDevice(0.0)));
        _replayDealItem->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(-80.0)));
    }
    
    _menu->addChild(btnDone);
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
    addChild(_randomDealItem);
    addChild(_winningDealItem);
    addChild(_replayDealItem);
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setSwallowsTouches(true);
    setTouchEnabled(true);

    
    if(arrowSprite) removeChild(arrowSprite);
    
    arrowSprite = MenuItemSprite::create(Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         this, menu_selector(BoardLayer::onDummy));
    arrowSprite->setScale(0.5);
    arrowSprite->setAnchorPoint(Vec2(0.5, 1));
    arrowSprite->setPosition(Vec2(0, 0));
    addChild(arrowSprite, 1000);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    lastMovedPoint = Vec2(0, 0);
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

void NewGameLayer::pressBegan()
{
    CCLOG("Taskbarlayer - press began : (%f, %f)", lastMovedPoint.x, lastMovedPoint.y);
    Vec2 touchPoint = (lastMovedPoint);
    
    if(_randomDealItem->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(NewGameLayer::onRandomDeal,this));
        _randomDealItem->runAction(Sequence::create(FadeTo::create(0.1, 0.5), func, NULL));
    }
    if(_winningDealItem->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(NewGameLayer::onWinningDeal,this));
        _winningDealItem->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(_replayDealItem->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(NewGameLayer::onReplayDeal,this));
        _replayDealItem->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(_selectDealItem && _selectDealItem->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(NewGameLayer::onSelectDeal,this));
        _selectDealItem->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnDone->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(NewGameLayer::onBack,this));
        btnDone->runAction(Sequence::create(FadeTo::create(0.1, 0.7), func, NULL));
    }
}

bool NewGameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("lastMovedPoint: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
    
    prevPoint = touch->getLocation();
    
    return true;
}

void NewGameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Director* director = Director::getInstance();
    Point location = touch->getLocationInView();
    location = director->convertToGL(location);
    
    //added by ccl
    Vec2 delta = location - prevPoint;
    lastMovedPoint += delta;
    
    log("touch move: %f, %f", location.x, location.y);
    
    arrowSprite->setPosition(lastMovedPoint);
    prevPoint = location;//added ccl
    
    log("touch move: %f, %f", location.x, location.y);
}

void NewGameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("touch end: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
}
