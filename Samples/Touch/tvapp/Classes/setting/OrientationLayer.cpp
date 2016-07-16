//
//  OrientationLayer.cpp
//  cardgame
//
//  Created by lion on 3/7/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "OrientationLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "AppDelegate.h"

enum ORIENTATION_CUSTOM
{
    ORIENTATION_AUTO = 0,
    ORIENTATION_PORTRAIT_ONLY,
    ORIENTATION_LANDSCAPE_ONLY,
};

cocos2d::CCScene* OrientationLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    OrientationLayer* layer = OrientationLayer::create();
    scene->addChild(layer);
    return scene;
}

bool OrientationLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void OrientationLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    CCSprite* background = CCSprite::create(getNameWithResolution("dialog_orientation").c_str());
    background->setScale(getScaleWithDevice());
    background->setPosition(ccp(0.0f, 0.0f));
    addChild(background);
    
    CCSize size = background->getContentSize();
    setContentSize(size);
    
    switch(GameData::getInstance()->getCustomOrientation()){
        case 0:
            createMenuWithEasy();
            break;
        case 1:
            createMenuWithNormal();
            break;
        default:
            createMenuWithHard();
            break;
    }
    
    CCMenuItem* btnDone = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_done_nor").c_str()),
                                                   CCSprite::create(getNameWithResolution("btn_done_act").c_str()),
                                                   this, menu_selector(OrientationLayer::onDone));
    CCMenuItem* easyLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                     CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                     this, menu_selector(OrientationLayer::onAutoMode));
    CCMenuItem* normalLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                       CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                       this, menu_selector(OrientationLayer::onPortraitMode));
    CCMenuItem* hardLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                     CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                     this, menu_selector(OrientationLayer::onLandscapeMode));
    
    _easyItem->setAnchorPoint(ccp(0.5f, 0.5f));
    _normalItem->setAnchorPoint(ccp(0.5f, 0.5f));
    _hardItem->setAnchorPoint(ccp(0.5f, 0.5f));
    btnDone->setAnchorPoint(ccp(0.5f, 0.0f));
    
    _easyItem->setScale(getScaleWithDevice());
    _normalItem->setScale(getScaleWithDevice());
    _hardItem->setScale(getScaleWithDevice());
    btnDone->setScale(getScaleWithDevice());
    
    _easyItem->setPosition(ccp(getSizeWithDevice(185.0f), getSizeWithDevice(70.0f)));
    _normalItem->setPosition(ccp(getSizeWithDevice(185.0f), getSizeWithDevice(10.0f)));
    _hardItem->setPosition(ccp(getSizeWithDevice(185.0f), -getSizeWithDevice(50.0f)));
    
    easyLabel->setPosition(ccp(getSizeWithDevice(10.0f), getSizeWithDevice(80.0f)));
    normalLabel->setPosition(ccp(getSizeWithDevice(10.0f), getSizeWithDevice(10.0f)));
    hardLabel->setPosition(ccp(getSizeWithDevice(10.0f), -getSizeWithDevice(60.0f)));
    btnDone->setPosition(ccp(getSizeWithDevice(0.0f),  -size.height/2.0f + getSizeWithDevice(27.0f)));
    
    _menu = CCMenu::create();
    _menu->addChild(easyLabel);
    _menu->addChild(normalLabel);
    _menu->addChild(hardLabel);
    _menu->addChild(_easyItem);
    _menu->addChild(_normalItem);
    _menu->addChild(_hardItem);
    _menu->addChild(btnDone);
    
    _menu->setPosition(ccp(0.0f, 0.0f));
    addChild(_menu);
}

void OrientationLayer::createMenuWithEasy()
{
    
    _easyItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         this, menu_selector(OrientationLayer::onAutoMode));
    _normalItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(OrientationLayer::onPortraitMode));
    _hardItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(OrientationLayer::onLandscapeMode));
}

void OrientationLayer::createMenuWithNormal()
{
    _easyItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(OrientationLayer::onAutoMode));
    _normalItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           this, menu_selector(OrientationLayer::onPortraitMode));
    _hardItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(OrientationLayer::onLandscapeMode));
}

void OrientationLayer::createMenuWithHard()
{
    _easyItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(OrientationLayer::onAutoMode));
    _normalItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(OrientationLayer::onPortraitMode));
    _hardItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         this, menu_selector(OrientationLayer::onLandscapeMode));
}

void OrientationLayer::onAutoMode(CCObject* sender)
{
    GameData::getInstance()->setCustomOrientation(ORIENTATION_AUTO);
    AppDelegate::get()->sendMessageToNative(MSG_ORIENTATION, "Auto", ORIENTATION_AUTO);
    
    CCSprite* norSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getNormalImage();
    CCSprite* selSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getSelectedImage();
    CCSprite* norSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getNormalImage();
    CCSprite* selSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getSelectedImage();
    CCSprite* norSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getNormalImage();
    CCSprite* selSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_on").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
}

void OrientationLayer::onPortraitMode(CCObject* sender)
{
    GameData::getInstance()->setCustomOrientation(ORIENTATION_PORTRAIT_ONLY);
    AppDelegate::get()->sendMessageToNative(MSG_ORIENTATION, "Portrait", ORIENTATION_PORTRAIT_ONLY);
    
    CCSprite* norSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getNormalImage();
    CCSprite* selSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getSelectedImage();
    CCSprite* norSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getNormalImage();
    CCSprite* selSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getSelectedImage();
    CCSprite* norSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getNormalImage();
    CCSprite* selSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_on").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
}

void OrientationLayer::onLandscapeMode(CCObject* sender)
{
    GameData::getInstance()->setCustomOrientation(ORIENTATION_LANDSCAPE_ONLY);
    AppDelegate::get()->sendMessageToNative(MSG_ORIENTATION, "Landscape", ORIENTATION_LANDSCAPE_ONLY);
    
    CCSprite* norSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getNormalImage();
    CCSprite* selSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getSelectedImage();
    CCSprite* norSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getNormalImage();
    CCSprite* selSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getSelectedImage();
    CCSprite* norSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getNormalImage();
    CCSprite* selSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_on").c_str());
    
    norSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
}

void OrientationLayer::onDone(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    removeFromParentAndCleanup(true);
    ((SettingLayer*)_parentLayer)->didFinishCell();
    //_spiderOptionLayer = NULL;
}