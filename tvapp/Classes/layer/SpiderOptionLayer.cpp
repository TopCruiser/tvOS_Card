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

cocos2d::CCScene* SpiderOptionLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    SpiderOptionLayer* layer = SpiderOptionLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SpiderOptionLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void SpiderOptionLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    CCSprite* background = CCSprite::create(getNameWithResolution("dialog_spider_option").c_str());
    background->setScale(getScaleWithDevice());
    background->setPosition(ccp(0.0f, 0.0f));
    addChild(background);
    
    CCSize size = background->getContentSize();
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
    
    CCMenuItem* btnDone = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_done_nor").c_str()),
                                                   CCSprite::create(getNameWithResolution("btn_done_act").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onDone));
    CCMenuItem* easyLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    CCMenuItem* normalLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    CCMenuItem* expertLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                       CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                       this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    
    
    CCMenuItem* hardLabel = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   CCSprite::create(getNameWithResolution("btn_check_label").c_str()),
                                                   this, menu_selector(SpiderOptionLayer::onSelHardMode));
    
    _easyItem->setAnchorPoint(ccp(0.5f, 0.5f));
    _normalItem->setAnchorPoint(ccp(0.5f, 0.5f));
    _expertItem->setAnchorPoint(ccp(0.5f, 0.5f));
    _hardItem->setAnchorPoint(ccp(0.5f, 0.5f));
    btnDone->setAnchorPoint(ccp(0.5f, 0.0f));
    
    _easyItem->setScale(getScaleWithDevice());
    _normalItem->setScale(getScaleWithDevice());
    _expertItem->setScale(getScaleWithDevice());
    _hardItem->setScale(getScaleWithDevice());
    btnDone->setScale(getScaleWithDevice());
    
    _easyItem->setPosition(ccp(getSizeWithDevice(230.0f), getSizeWithDevice(100.0f)));
    _normalItem->setPosition(ccp(getSizeWithDevice(230.0f), getSizeWithDevice(30.0f)));
    
    _expertItem->setPosition(ccp(getSizeWithDevice(230.0f), -getSizeWithDevice(45.0f)));
    _hardItem->setPosition(ccp(getSizeWithDevice(230.0f), -getSizeWithDevice(120.0f)));
    
    easyLabel->setPosition(ccp(getSizeWithDevice(10.0f), getSizeWithDevice(100.0f)));
    normalLabel->setPosition(ccp(getSizeWithDevice(10.0f), getSizeWithDevice(30.0f)));
    
    expertLabel->setPosition(ccp(getSizeWithDevice(10.0f), -getSizeWithDevice(45.0f)));
    hardLabel->setPosition(ccp(getSizeWithDevice(10.0f), -getSizeWithDevice(120.0f)));
    
    btnDone->setPosition(ccp(getSizeWithDevice(0.0f),  -size.height/2.0f + getSizeWithDevice(27.0f)));
    
    _menu = CCMenu::create();
    _menu->addChild(easyLabel);
    _menu->addChild(normalLabel);
    
    _menu->addChild(expertLabel);
    _menu->addChild(hardLabel);
    
    _menu->addChild(_easyItem);
    _menu->addChild(_normalItem);
    
    _menu->addChild(_expertItem);
    _menu->addChild(_hardItem);
    
    _menu->addChild(btnDone);
    
    _menu->setPosition(ccp(0.0f, 0.0f));
    addChild(_menu);
}

void SpiderOptionLayer::createMenuWithEasy()
{
 
    _easyItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    
    _hardItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
}

void SpiderOptionLayer::createMenuWithNormal()
{
    _easyItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    _hardItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
}

void SpiderOptionLayer::createMenuWithExpert()
{
    _easyItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    _hardItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
}

void SpiderOptionLayer::createMenuWithHard()
{
    _easyItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelEasyMode));
    _normalItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelNormalMode));
    
    _expertItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           CCSprite::create(getNameWithResolution("btn_check_off").c_str()),
                                           this, menu_selector(SpiderOptionLayer::onSelExpertMode));
    _hardItem = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         CCSprite::create(getNameWithResolution("btn_check_on").c_str()),
                                         this, menu_selector(SpiderOptionLayer::onSelHardMode));
}

void SpiderOptionLayer::onSelEasyMode(CCObject* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_EASY);
    
    CCSprite* norSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getNormalImage();
    CCSprite* selSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getSelectedImage();
    CCSprite* norSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getNormalImage();
    CCSprite* selSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getSelectedImage();
    
    CCSprite* norSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getNormalImage();
    CCSprite* selSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getSelectedImage();
    CCSprite* norSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getNormalImage();
    CCSprite* selSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_on").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
}

void SpiderOptionLayer::onSelNormalMode(CCObject* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_NORMAL);
    
    CCSprite* norSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getNormalImage();
    CCSprite* selSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getSelectedImage();
    CCSprite* norSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getNormalImage();
    CCSprite* selSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getSelectedImage();
    
    CCSprite* norSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getNormalImage();
    CCSprite* selSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getSelectedImage();
    CCSprite* norSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getNormalImage();
    CCSprite* selSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_on").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
}

void SpiderOptionLayer::onSelExpertMode(CCObject* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_EXPERT);
    
    CCSprite* norSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getNormalImage();
    CCSprite* selSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getSelectedImage();
    CCSprite* norSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getNormalImage();
    CCSprite* selSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getSelectedImage();
    
    CCSprite* norSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getNormalImage();
    CCSprite* selSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getSelectedImage();
    CCSprite* norSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getNormalImage();
    CCSprite* selSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_on").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
}

void SpiderOptionLayer::onSelHardMode(CCObject* sender)
{
    GameData::getInstance()->setSpiderMode(SPIDER_MODE_HARD);
    
    CCSprite* norSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getNormalImage();
    CCSprite* selSpriteEasy = (CCSprite*)((CCMenuItemSprite*)_easyItem)->getSelectedImage();
    CCSprite* norSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getNormalImage();
    CCSprite* selSpriteNormal = (CCSprite*)((CCMenuItemSprite*)_normalItem)->getSelectedImage();
    
    CCSprite* norSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getNormalImage();
    CCSprite* selSpriteExpert = (CCSprite*)((CCMenuItemSprite*)_expertItem)->getSelectedImage();
    CCSprite* norSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getNormalImage();
    CCSprite* selSpriteHard = (CCSprite*)((CCMenuItemSprite*)_hardItem)->getSelectedImage();
    
    norSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteEasy->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteNormal->initWithFile(getNameWithResolution("btn_check_off").c_str());
    
    norSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    selSpriteExpert->initWithFile(getNameWithResolution("btn_check_off").c_str());
    norSpriteHard->initWithFile(getNameWithResolution("btn_check_on").c_str());
    selSpriteHard->initWithFile(getNameWithResolution("btn_check_on").c_str());
    
    norSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteEasy->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteNormal->setAnchorPoint(ccp(0.0f, 0.0f));
    
    norSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteExpert->setAnchorPoint(ccp(0.0f, 0.0f));
    norSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
    selSpriteHard->setAnchorPoint(ccp(0.0f, 0.0f));
}

void SpiderOptionLayer::onDone(CCObject* sender)
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