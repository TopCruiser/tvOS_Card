//
//  SpiderOptionLayer.cpp
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "SpiderOptionLayer.h"
#include "GameLayer.h"
#include "GameData.h"

cocos2d::Scene* SpiderOptionLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    SpiderOptionLayer* layer = SpiderOptionLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SpiderOptionLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void SpiderOptionLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    Sprite* background = Sprite::create(getNameWithResolution("dialog_spider_option").c_str());
    background->setScale(getScaleWithDevice());
    background->setPosition(Vec2(0.0f, 0.0f));
    addChild(background);
    
    Size size = background->getContentSize();
    setContentSize(size);
    
    int mode = GameData::getInstance()->getSpiderMode();
    switch (mode) {
        case SPIDER_MODE_EASY:
            createMenuWithEasy();
            break;
        case SPIDER_MODE_NORMAL:
            createMenuWithNormal();
            break;
            
        case SPIDER_MODE_EXPERT:
            createMenuWithExpert();
            break;
            
        case SPIDER_MODE_HARD:
            createMenuWithHard();
            break;
        default:
            break;
    }
    
    MenuItem* btnDone = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_done_nor").c_str()),
                                                   Sprite::create(getNameWithResolution("btn_done_act").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onDone));
    MenuItem* easyLabel = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    MenuItem* normalLabel = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    MenuItem* expertLabel = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                       Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                       this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    
    
    MenuItem* hardLabel = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   Sprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onSelHardMode));
    
    _easyItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    _normalItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    _expertItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    _hardItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnDone->setAnchorPoint(Vec2(0.5f, 0.0f));
    
    _easyItem->setScale(getScaleWithDevice());
    _normalItem->setScale(getScaleWithDevice());
    _expertItem->setScale(getScaleWithDevice());
    _hardItem->setScale(getScaleWithDevice());
    btnDone->setScale(getScaleWithDevice());
    
    _easyItem->setPosition(Vec2(getSizeWithDevice(230.0f), getSizeWithDevice(100.0f)));
    _normalItem->setPosition(Vec2(getSizeWithDevice(230.0f), getSizeWithDevice(30.0f)));
    
    _expertItem->setPosition(Vec2(getSizeWithDevice(230.0f), -getSizeWithDevice(45.0f)));
    _hardItem->setPosition(Vec2(getSizeWithDevice(230.0f), -getSizeWithDevice(120.0f)));
    
    _hardItem->setPosition(Vec2(0.6, 0.6));//pending
    
    easyLabel->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(100.0f)));
    normalLabel->setPosition(Vec2(getSizeWithDevice(10.0f), getSizeWithDevice(30.0f)));
    
    expertLabel->setPosition(Vec2(getSizeWithDevice(10.0f), -getSizeWithDevice(45.0f)));
    hardLabel->setPosition(Vec2(getSizeWithDevice(10.0f), -getSizeWithDevice(120.0f)));
    
    btnDone->setPosition(Vec2(getSizeWithDevice(0.0f),  -size.height/2.0f + getSizeWithDevice(27.0f)));
    
    _menu = Menu::create();
    _menu->addChild(easyLabel);
    _menu->addChild(normalLabel);
    
    _menu->addChild(expertLabel);
    _menu->addChild(hardLabel);
    
    _menu->addChild(_easyItem);
    _menu->addChild(_normalItem);
    
    _menu->addChild(_expertItem);
    _menu->addChild(_hardItem);
    
    _menu->addChild(btnDone);
    
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
}

void SpiderOptionLayer::createMenuWithEasy()
{
 
    _easyItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    
    _hardItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
}

void SpiderOptionLayer::createMenuWithNormal()
{
    _easyItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    _hardItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
}

void SpiderOptionLayer::createMenuWithExpert()
{
    _easyItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    _hardItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
}

void SpiderOptionLayer::createMenuWithHard()
{
    _easyItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           Sprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    _hardItem = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         Sprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
    
}

void SpiderOptionLayer::onSelEasyMode(Ref* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_EASY);
    
    Sprite* norSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getNormalImage();
    Sprite* selSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getSelectedImage();
    Sprite* norSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getNormalImage();
    Sprite* selSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getSelectedImage();
    
    Sprite* norSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getNormalImage();
    Sprite* selSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getSelectedImage();
    Sprite* norSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getNormalImage();
    Sprite* selSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_on").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
}

void SpiderOptionLayer::onSelNormalMode(Ref* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_NORMAL);
    
    Sprite* norSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getNormalImage();
    Sprite* selSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getSelectedImage();
    Sprite* norSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getNormalImage();
    Sprite* selSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getSelectedImage();
    
    Sprite* norSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getNormalImage();
    Sprite* selSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getSelectedImage();
    Sprite* norSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getNormalImage();
    Sprite* selSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_on").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
}

void SpiderOptionLayer::onSelExpertMode(Ref* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_EXPERT);
    
    Sprite* norSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getNormalImage();
    Sprite* selSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getSelectedImage();
    Sprite* norSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getNormalImage();
    Sprite* selSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getSelectedImage();
    
    Sprite* norSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getNormalImage();
    Sprite* selSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getSelectedImage();
    Sprite* norSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getNormalImage();
    Sprite* selSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_on").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
}

void SpiderOptionLayer::onSelHardMode(Ref* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_HARD);
    
    Sprite* norSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getNormalImage();
    Sprite* selSpriteEasy = (Sprite*)((MenuItemSprite*)_easyItem)->getSelectedImage();
    Sprite* norSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getNormalImage();
    Sprite* selSpriteNormal = (Sprite*)((MenuItemSprite*)_normalItem)->getSelectedImage();
    
    Sprite* norSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getNormalImage();
    Sprite* selSpriteExpert = (Sprite*)((MenuItemSprite*)_expertItem)->getSelectedImage();
    Sprite* norSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getNormalImage();
    Sprite* selSpriteHard = (Sprite*)((MenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_on").c_str());
    
    norSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(Vec2(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(Vec2(0.0f, 0.0f));
}

void SpiderOptionLayer::onDone(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    if(GameData::getInstance()->isMenuLayer())
        ((GameLayer*)_parentLayer)->showBoardLayerWithSpider();
    else
    {
        removeFromParentAndCleanup(true);
        ((GameLayer*)_parentLayer)->removeOptionLayers();
        ((GameLayer*)_parentLayer)->getTaskbarLayer()->showNewGame();
    }
}
