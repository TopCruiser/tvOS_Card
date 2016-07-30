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

cocos2d::Scene* SolitaireOptionLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    SolitaireOptionLayer* layer = SolitaireOptionLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SolitaireOptionLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void SolitaireOptionLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    Sprite* background = Sprite::create(getNameWithResolution("dialog_solitaire_option").c_str());
    background->setScale(getScaleWithDevice());
    background->setPosition(Vec2(0.0f, 0.0f));
    addChild(background);
    
    Size size = background->getContentSize();
    setContentSize(size);
    
    _drawthreeLabel = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                               Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                               this, menu_selector(SolitaireOptionLayer::onSelDrawThree));
    
    if(GameData::getInstance()->isDrawFlag()){
        _drawthreeItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                                  Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                                  this, menu_selector(SolitaireOptionLayer::onSelDrawThree));
    
    }
    else{
        _drawthreeItem = CCMenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                                  Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                                  this, menu_selector(SolitaireOptionLayer::onSelDrawThree));
    }
    
    _vegasLabel = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                           this, menu_selector(SolitaireOptionLayer::onSelVegasStyle));
    if(GameData::getInstance()->isVegasMode())
        _vegasItem = CCMenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                              Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                              this, menu_selector(SolitaireOptionLayer::onSelVegasStyle));
    else{
        _vegasItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                              Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                              this, menu_selector(SolitaireOptionLayer::onSelVegasStyle));
    
    }
    
    MenuItem* btnDone = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_done_nor").c_str()),
                                                   Sprite::create(getNameWithResolution("btn_done_act").c_str()),
                                                   this, menu_selector(SolitaireOptionLayer::onDone));
    
    MenuItem* dummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_done_nor").c_str()),
                                               Sprite::create(getNameWithResolution("btn_done_act").c_str()),
                                               this, menu_selector(SolitaireOptionLayer::onDummy));
    dummy->setScale(0.01);
    
    _drawthreeItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    _vegasItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnDone->setAnchorPoint(Vec2(0.5f, 0.0f));
    
    _drawthreeItem->setScale(getScaleWithDevice());
    _vegasItem->setScale(getScaleWithDevice());
    btnDone->setScale(getScaleWithDevice());
    
    _drawthreeItem->setPosition(Vec2(getSizeWithDevice(200.0f), getSizeWithDevice(46.0f)));
    _drawthreeLabel->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(46.0f)));
    
    _vegasItem->setPosition(Vec2(getSizeWithDevice(200.0f), -getSizeWithDevice(39.0f)));
    _vegasLabel->setPosition(Vec2(getSizeWithDevice(10.0f), -getSizeWithDevice(39.0f)));
    btnDone->setPosition(Vec2(getSizeWithDevice(0.0f),  -size.height/2.0f + getSizeWithDevice(27.0f)));
    
    _menu = Menu::create();
    _menu->addChild(_drawthreeLabel);
    _menu->addChild(_drawthreeItem);
    _menu->addChild(_vegasLabel);
    _menu->addChild(_vegasItem);
    _menu->addChild(btnDone);
    _menu->addChild(dummy);
    
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
}

void SolitaireOptionLayer::onSelDrawThree(Ref* sender)
{
    bool isDrawFlag = GameData::getInstance()->isDrawFlag();
    isDrawFlag = !isDrawFlag;
    GameData::getInstance()->setDrawFlag(isDrawFlag);
    
    Sprite* norSpriteDraw = (Sprite*)((MenuItemSprite*)_drawthreeItem)->getNormalImage();
    Sprite* selSpriteDraw = (Sprite*)((MenuItemSprite*)_drawthreeItem)->getSelectedImage();
    
    if(isDrawFlag)
    {
        norSpriteDraw->initWithFile(getNameWithResolution("btn_check_on").c_str());
    }
    else
    {
        norSpriteDraw->initWithFile(getNameWithResolution("btn_check_off").c_str());
    }
    
    norSpriteDraw->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteDraw->setAnchorPoint(Vec2(0.0f, 0.0f));
}

void SolitaireOptionLayer::onSelVegasStyle(Ref* sender)
{
    bool isVegas = GameData::getInstance()->isVegasMode();
    isVegas = !isVegas;
    GameData::getInstance()->setVegasMode(isVegas);
    
    Sprite* norSpriteVegas = (Sprite*)((MenuItemSprite*)_vegasItem)->getNormalImage();
    Sprite* selSpriteVegas = (Sprite*)((MenuItemSprite*)_vegasItem)->getSelectedImage();
    
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
    
    norSpriteVegas->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteVegas->setAnchorPoint(Vec2(0.0f, 0.0f));
}

void SolitaireOptionLayer::onDummy(Ref* sender)
{
    
}

void SolitaireOptionLayer::onDone(Ref* sender)
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
