//
//  BackgroundLayer.cpp
//  cardgame
//
//  Created by lion on 3/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "ImagePicker.h"

enum MENU_TAG {
    TAG_BG01 = 0,
    TAG_BG02,
    TAG_BG03,
    TAG_BG04,
    TAG_BG05,
    TAG_BG06,
    TAG_BG07,
    TAG_NATIVE,
    TAG_MAX
};

cocos2d::CCScene* BackgroundLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    BackgroundLayer* layer = BackgroundLayer::create();
    scene->addChild(layer);
    return scene;
}

bool BackgroundLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void BackgroundLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    _background = CCSprite::create();
    _background->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(_background);
    
    btnBack = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("back_nor").c_str()),
                                       CCSprite::create(getNameWithResolution("back_act").c_str()),
                                       this, menu_selector(BackgroundLayer::onBack));
    btnBack->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBack->setScale(getScaleWithDevice());
    
    _title = CCSprite::create();
    addChild(_title);
    
    //CCSprite * sprite01 =CCSprite::create(getNameWithDevice("background01").c_str());
    CCSprite * sprite01 =CCSprite::create(getNameWithDeviceIpad("background01").c_str());
    CCSize bgSize= sprite01->getContentSize();
    
    float scaleX=getSizeWithDevice(160.0f)/bgSize.width;
    float scaleY=getSizeWithDevice(160.0f)/bgSize.height;
    
    sprite01->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite01->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG01 = CCMenuItemSprite::create(sprite01, sprite01, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //CCSprite * sprite02 =CCSprite::create(getNameWithDevice("background02").c_str());
    CCSprite * sprite02 =CCSprite::create(getNameWithDeviceIpad("background02").c_str());
    sprite02->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite02->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG02 = CCMenuItemSprite::create(sprite02, sprite02, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //CCSprite * sprite03 =CCSprite::create(getNameWithDevice("background03").c_str());
    CCSprite * sprite03 =CCSprite::create(getNameWithDeviceIpad("background03").c_str());
    sprite03->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite03->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG03 = CCMenuItemSprite::create(sprite03, sprite03, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //CCSprite * sprite04 =CCSprite::create(getNameWithDevice("background04").c_str());
    CCSprite * sprite04 =CCSprite::create(getNameWithDeviceIpad("background04").c_str());
    sprite04->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite04->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG04 = CCMenuItemSprite::create(sprite04, sprite04, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //CCSprite * sprite05 =CCSprite::create(getNameWithDevice("background05").c_str());
    CCSprite * sprite05 =CCSprite::create(getNameWithDeviceIpad("background05").c_str());
    sprite05->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite05->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG05 = CCMenuItemSprite::create(sprite05, sprite05, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //CCSprite * sprite06 =CCSprite::create(getNameWithDevice("background06").c_str());
    CCSprite * sprite06 =CCSprite::create(getNameWithDeviceIpad("background06").c_str());
    sprite06->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite06->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG06 = CCMenuItemSprite::create(sprite06, sprite06, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //CCSprite * sprite07 =CCSprite::create(getNameWithDevice("background07").c_str());
    CCSprite * sprite07 =CCSprite::create(getNameWithDeviceIpad("background07").c_str());
    sprite07->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite07->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG07 = CCMenuItemSprite::create(sprite07, sprite07, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    CCSprite * sprite08 =CCSprite::create(getNameWithDevice("background08").c_str());
    
    bgSize= sprite08->getContentSize();
    
    scaleX=getSizeWithDevice(160.0f)/bgSize.width;
    scaleY=getSizeWithDevice(160.0f)/bgSize.height;
    
    sprite08->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite08->setContentSize(CCSizeMake(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG08 = CCMenuItemSprite::create(sprite08, sprite08, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    btnBG01->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBG02->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBG03->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBG04->setAnchorPoint(ccp(0.5f, 0.5f));
    
    btnBG05->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBG06->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBG07->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBG08->setAnchorPoint(ccp(0.5f, 0.5f));
    
    btnBG01->setScale(getScaleWithDevice());
    btnBG02->setScale(getScaleWithDevice());
    btnBG03->setScale(getScaleWithDevice());
    btnBG04->setScale(getScaleWithDevice());
    
    btnBG05->setScale(getScaleWithDevice());
    btnBG06->setScale(getScaleWithDevice());
    btnBG07->setScale(getScaleWithDevice());
    btnBG08->setScale(getScaleWithDevice());
    
    _menu = CCMenu::create();
    
    _menu->addChild(btnBack);
    
    _menu->addChild(btnBG01, 1, TAG_BG01);
    _menu->addChild(btnBG02, 1, TAG_BG02);
    _menu->addChild(btnBG03, 1, TAG_BG03);
    _menu->addChild(btnBG04, 1, TAG_BG04);
    
    _menu->addChild(btnBG05, 1, TAG_BG05);
    _menu->addChild(btnBG06, 1, TAG_BG06);
    _menu->addChild(btnBG07, 1, TAG_BG07);
    _menu->addChild(btnBG08, 1, TAG_NATIVE);
    _menu->setVisible(false);
    
    addChild(_menu);
    
}

void BackgroundLayer::updateLayoutWithPortrait()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(ccp(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_port").c_str());
    _title->setAnchorPoint(ccp(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.7f);
    _title->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(460.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        CCPoint pos = CCPointZero;
        switch (i) {
            case TAG_BG01:
                pos.x = getSizeWithDevice(-100);
                pos.y = getSizeWithDevice(110);
                break;
            case TAG_BG02:
                pos.x = getSizeWithDevice(100);
                pos.y = getSizeWithDevice(110);
                break;
            case TAG_BG03:
                pos.x = getSizeWithDevice(-100);
                pos.y = -getSizeWithDevice(60);
                break;
            case TAG_BG04:
                pos.x = getSizeWithDevice(100);
                pos.y = -getSizeWithDevice(60);
                break;
            case TAG_BG05:
                pos.x = getSizeWithDevice(-100);
                pos.y = -getSizeWithDevice(230);
                break;
            case TAG_BG06:
                pos.x = getSizeWithDevice(100);
                pos.y = -getSizeWithDevice(230);
                break;
            case TAG_BG07:
                pos.x = getSizeWithDevice(-100);
                pos.y = -getSizeWithDevice(400);
                break;
            case TAG_NATIVE:
                pos.x = getSizeWithDevice(100);
                pos.y = -getSizeWithDevice(400);
                break;
            default:
                break;
        }
        
        CCMenuItem* item = (CCMenuItem*)_menu->getChildByTag(i);
        
        item->setPosition(pos);
    }
    
    _menu->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
}

void BackgroundLayer::updateLayoutWithLandscape()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(ccp(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(ccp(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        CCPoint pos = CCPointZero;
        switch (i) {
            case TAG_BG01:
                pos.x = -getSizeWithDevice(270);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_BG02:
                pos.x = -getSizeWithDevice(270);
                pos.y = -getSizeWithDevice(190);
                break;
                
                
                
            case TAG_BG03:
                pos.x = -getSizeWithDevice(90);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_BG04:
                pos.x = -getSizeWithDevice(90);
                pos.y = -getSizeWithDevice(190);
                break;
            case TAG_BG05:
                pos.x = getSizeWithDevice(90);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_BG06:
                pos.x = getSizeWithDevice(90);
                pos.y = -getSizeWithDevice(190);
                break;
                
            case TAG_BG07:
                pos.x = getSizeWithDevice(270);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_NATIVE:
                pos.x = getSizeWithDevice(270);
                pos.y = -getSizeWithDevice(190);
                break;
            default:
                break;
        }
        
        CCMenuItem* item = (CCMenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
    }
    
    _menu->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
}

void BackgroundLayer::onBackgroundSelected(CCObject* sender)
{
    //Background selected
    
    CCMenuItem* item = (CCMenuItem*)sender;
    int backgroundIndex=item->getTag() ;
    
    if(backgroundIndex<TAG_NATIVE)
    {
        GameData::getInstance()->setBackgroundIndex(backgroundIndex);
        ((GameLayer*)_parentLayer)->setBackground(backgroundIndex);
    }
    else
        ImagePicker::getInstance()->pickImage(this);
    
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

void BackgroundLayer::didFinishPickingWithResult(cocos2d::CCTexture2D* result)
{
    CCLog("%s", "BackgroundLayer didFinishPickingWithResult");
    if(result==NULL) return;
    
    GameData::getInstance()->setBackgroundIndex(TAG_NATIVE);
    ((GameLayer*)_parentLayer)->setBackground(result);
        
    /*
     _background->initWithTexture(result);
     CCSize winSize = CCDirector::sharedDirector()->getWinSize();
     CCSize bgSize= _background->getContentSize();
     
     float scaleX=winSize.width/bgSize.width;
     float scaleY=winSize.height/bgSize.height;
     
     _background->cocos2d::CCNode::setScale(scaleX, scaleY);
     _background->setContentSize(_background->getContentSize());
    */
    
}

void BackgroundLayer::onBack(CCObject* sender)
{
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}