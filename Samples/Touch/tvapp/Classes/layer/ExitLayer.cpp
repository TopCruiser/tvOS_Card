//
//  ExitLayer.cpp
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "ExitLayer.h"
#include "GameLayer.h"
#include "GameData.h"

cocos2d::Scene* ExitLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    ExitLayer* layer = ExitLayer::create();
    scene->addChild(layer);
    return scene;
}

bool ExitLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void ExitLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    Sprite* background;
    background= Sprite::create(getNameWithResolution("dialog_exit").c_str());
    
    background->setScale(getScaleWithDevice());
    background->setPosition(Vec2(0.0f, 0.0f));
    addChild(background);
    
    Size size = background->getContentSize();
    setContentSize(size);
    
    btnYes = MenuItemSprite::create(Sprite::create(getNameWithResolution("exit_yes_nor").c_str()),
                                               Sprite::create(getNameWithResolution("exit_yes_act").c_str()),
                                               this, menu_selector(ExitLayer::onYES));
    
    btnNo = MenuItemSprite::create(Sprite::create(getNameWithResolution("exit_no_nor").c_str()),
                                                Sprite::create(getNameWithResolution("exit_no_act").c_str()),
                                                this, menu_selector(ExitLayer::onNO));
    MenuItem* btnDummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("exit_no_nor").c_str()),
                                             Sprite::create(getNameWithResolution("exit_no_act").c_str()),
                                                this, menu_selector(ExitLayer::onDummy));
    btnDummy->setScale(0.01);
    
    btnYes->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnNo->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnYes->setScale(getScaleWithDevice());
    btnNo->setScale(getScaleWithDevice());
    
    btnYes->setPosition(Vec2(getSizeWithDevice(80.0f), -getSizeWithDevice(70.0f)));
    
    btnNo->setPosition(Vec2(getSizeWithDevice(210.0f),  -getSizeWithDevice(70.0f)));
    
    _menu = Menu::create();
    _menu->addChild(btnYes);
    _menu->addChild(btnNo);
    
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
    
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

void ExitLayer::onDummy(Ref* sender)
{
    
}

void ExitLayer::onYES(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    _isYes = true;
    
    Size winSize = Director::getInstance()->getWinSize();
    MoveTo *_move_to = MoveTo::create(0.3f,Vec2( 0.0f, winSize.height));
    EaseIn *_easein = EaseIn::create(_move_to,0.3f);
    CallFunc *_functionCall = CallFunc::create(this,callfunc_selector(ExitLayer::didAction));
    Sequence *_sequence  =  Sequence::create( _easein, _functionCall ,NULL);
    this->runAction(_sequence);
    setLocalZOrder(0);
}

void ExitLayer::onNO(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    _isYes = false;
    
    MoveTo *_move_to = MoveTo::create(0.3f,Vec2( 0.0f, 0.0f));
    EaseIn *_easein = EaseIn::create(_move_to,0.3f);
    CallFunc *_functionCall = CallFunc::create(this,callfunc_selector(ExitLayer::didAction));
    Sequence *_sequence  =  Sequence::create( _easein, _functionCall ,NULL);
    this->runAction(_sequence);
    setLocalZOrder(0);
}

void ExitLayer::didAction()
{
    ((GameLayer*)((TaskbarLayer*)_parentLayer)->_parentLayer)->setTag(101);
    ((TaskbarLayer*)_parentLayer)->didExitLayer(_isYes);
    
}

void ExitLayer::pressBegan()
{
    CCLOG("Taskbarlayer - press began : (%f, %f)", lastMovedPoint.x, lastMovedPoint.y);
    Vec2 touchPoint = (lastMovedPoint);
    
    if(btnYes->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(ExitLayer::onYES,this));
        btnYes->runAction(Sequence::create(FadeTo::create(0.1, 0.7), func, NULL));
    }
    if(btnNo->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(ExitLayer::onNO,this));
        btnNo->runAction(Sequence::create(FadeTo::create(0.1, 0.7), func, NULL));
    }
}

bool ExitLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("lastMovedPoint: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
    
    prevPoint = touch->getLocation();
    
    return true;
}

void ExitLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
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

void ExitLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("touch end: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
}
