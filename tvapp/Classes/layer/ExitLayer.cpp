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

cocos2d::CCScene* ExitLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    ExitLayer* layer = ExitLayer::create();
    scene->addChild(layer);
    return scene;
}

bool ExitLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void ExitLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    CCSprite* background;
    background= CCSprite::create(getNameWithResolution("dialog_exit").c_str());
    
    background->setScale(getScaleWithDevice());
    background->setPosition(ccp(0.0f, 0.0f));
    addChild(background);
    
    CCSize size = background->getContentSize();
    setContentSize(size);
    
    CCMenuItem* btnYes = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("exit_yes_nor").c_str()),
                                               CCSprite::create(getNameWithResolution("exit_yes_act").c_str()),
                                               this, menu_selector(ExitLayer::onYES));
    
    CCMenuItem* btnNo = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("exit_no_nor").c_str()),
                                                CCSprite::create(getNameWithResolution("exit_no_act").c_str()),
                                                this, menu_selector(ExitLayer::onNO));
    
    
    btnYes->setAnchorPoint(ccp(0.5f, 0.5f));
    btnNo->setAnchorPoint(ccp(0.5f, 0.5f));
    
    btnYes->setScale(getScaleWithDevice());
    btnNo->setScale(getScaleWithDevice());
    
    btnYes->setPosition(ccp(getSizeWithDevice(80.0f), -getSizeWithDevice(70.0f)));
    
    btnNo->setPosition(ccp(getSizeWithDevice(210.0f),  -getSizeWithDevice(70.0f)));
    
    _menu = CCMenu::create();
    _menu->addChild(btnYes);
    _menu->addChild(btnNo);
    
    _menu->setPosition(ccp(0.0f, 0.0f));
    addChild(_menu);
}


void ExitLayer::onYES(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    _isYes = true;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo *_move_to = CCMoveTo::create(0.3f,ccp( 0.0f, winSize.height));
    CCEaseIn *_easein = CCEaseIn::create(_move_to,0.3f);
    CCCallFunc *_functionCall = CCCallFunc::create(this,callfunc_selector(ExitLayer::didAction));
    CCSequence *_sequence  =  CCSequence::create( _easein, _functionCall ,NULL);
    this->runAction(_sequence);
    
}

void ExitLayer::onNO(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    _isYes = false;
    
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo *_move_to = CCMoveTo::create(0.3f,ccp( 0.0f, 0.0f));
    CCEaseIn *_easein = CCEaseIn::create(_move_to,0.3f);
    CCCallFunc *_functionCall = CCCallFunc::create(this,callfunc_selector(ExitLayer::didAction));
    CCSequence *_sequence  =  CCSequence::create( _easein, _functionCall ,NULL);
    this->runAction(_sequence);
    
}

void ExitLayer::didAction()
{
    ((TaskbarLayer*)_parentLayer)->didExitLayer(_isYes);
}