//
//  SolitaireOptionLayer.cpp
//  cardgame
//
//  Created by Pink on 2/10/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "SolitaireOptionLayer.h"
#include "GameLayer.h"
#include "GameData.h"

cocos2d::CCScene* SolitaireOptionLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    SolitaireOptionLayer* layer = SolitaireOptionLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SolitaireOptionLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void SolitaireOptionLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    CCSprite* background = CCSprite::create(getNameWithResolution("dialog_solitaire_option").c_str());
    background->setScale(getScaleWithDevice());
    background->setPosition(ccp(0.0f, 0.0f));
    addChild(background);
    
    CCSize size = background->getContentSize();
    setContentSize(size);
    
    _drawthreeLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                               CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                               this, menu_selector(SolitaireOptionLayer::onSelDrawThree));
    
    if(GameData::getInstance()->isDrawFlag()){
        _drawthreeItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                                  CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                                  this, menu_selector(SolitaireOptionLayer::onSelDrawThree));
    
    }
    else{
        _drawthreeItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                                  CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                                  this, menu_selector(SolitaireOptionLayer::onSelDrawThree));
    }
    
    _vegasLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                           this, menu_selector(SolitaireOptionLayer::onSelVegasStyle));
    if(GameData::getInstance()->isVegasMode())
        _vegasItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                              CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                              this, menu_selector(SolitaireOptionLayer::onSelVegasStyle));
    else{
        _vegasItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                              CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                              this, menu_selector(SolitaireOptionLayer::onSelVegasStyle));
    
    }
    
    CCMenuItem* btnDone = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_done_nor").c_str()),
                                                   CCSprite::create(getNameWithResolution("btn_done_act").c_str()),
                                                   this, menu_selector(SolitaireOptionLayer::onDone));
    
    _drawthreeItem->setAnchorPoint(ccp(0.5f, 0.5f));
    _vegasItem->setAnchorPoint(ccp(0.5f, 0.5f));
    btnDone->setAnchorPoint(ccp(0.5f, 0.0f));
    
    _drawthreeItem->setScale(getScaleWithDevice());
    _vegasItem->setScale(getScaleWithDevice());
    btnDone->setScale(getScaleWithDevice());
    
    _drawthreeItem->setPosition(ccp(getSizeWithDevice(200.0f), getSizeWithDevice(46.0f)));
    _drawthreeLabel->setPosition(ccp(getSizeWithDevice(10.0f), getSizeWithDevice(46.0f)));
    
    _vegasItem->setPosition(ccp(getSizeWithDevice(200.0f), -getSizeWithDevice(39.0f)));
    _vegasLabel->setPosition(ccp(getSizeWithDevice(10.0f), -getSizeWithDevice(39.0f)));
    btnDone->setPosition(ccp(getSizeWithDevice(0.0f),  -size.height/2.0f + getSizeWithDevice(27.0f)));
    
    _menu = CCMenu::create();
    _menu->addChild(_drawthreeLabel);
    _menu->addChild(_drawthreeItem);
    _menu->addChild(_vegasLabel);
    _menu->addChild(_vegasItem);
    _menu->addChild(btnDone);
    
    _menu->setPosition(ccp(0.0f, 0.0f));
    addChild(_menu);
}

void SolitaireOptionLayer::onSelDrawThree(CCObject* sender)
{
    bool isDrawFlag = GameData::getInstance()->isDrawFlag();
    isDrawFlag = !isDrawFlag;
    GameData::getInstance()->setDrawFlag(isDrawFlag);
    
    CCSprite* norSpriteDraw = (CCSprite*)((CCMenuItemSprite*)_drawthreeItem)->getNormalImage();
    CCSprite* selSpriteDraw = (CCSprite*)((CCMenuItemSprite*)_drawthreeItem)->getSelectedImage();
    
    if(isDrawFlag)
    {
        norSpriteDraw->initWithFile(getNameWithResolution("btn_check_on").c_str());
    }
    else
    {
        norSpriteDraw->initWithFile(getNameWithResolution("btn_check_off").c_str());
    }
    
    norSpriteDraw->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteDraw->setAnchorPoint(ccp(0.0f, 0.0f));
}

void SolitaireOptionLayer::onSelVegasStyle(CCObject* sender)
{
    bool isVegas = GameData::getInstance()->isVegasMode();
    isVegas = !isVegas;
    GameData::getInstance()->setVegasMode(isVegas);
    
    CCSprite* norSpriteVegas = (CCSprite*)((CCMenuItemSprite*)_vegasItem)->getNormalImage();
    CCSprite* selSpriteVegas = (CCSprite*)((CCMenuItemSprite*)_vegasItem)->getSelectedImage();
    
    if(isVegas)
    {
        norSpriteVegas->initWithFile(getNameWithResolution("btn_check_on").c_str());
        selSpriteVegas->initWithFile(getNameWithResolution("btn_check_on").c_str());
    }
    else
    {
        norSpriteVegas->initWithFile(getNameWithResolution("btn_check_off").c_str());
        selSpriteVegas->initWithFile(getNameWithResolution("btn_check_off").c_str());
    }
    
    norSpriteVegas->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteVegas->setAnchorPoint(ccp(0.0f, 0.0f));
}

void SolitaireOptionLayer::onDone(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    if(GameData::getInstance()->isMenuLayer())
        ((GameLayer*)_parentLayer)->showBoardLayerWithSolitaire();
    else
    {
        removeFromParentAndCleanup(true);
        ((GameLayer*)_parentLayer)->removeOptionLayers();
        ((GameLayer*)_parentLayer)->getTaskbarLayer()->showNewGame();
    }    
}
