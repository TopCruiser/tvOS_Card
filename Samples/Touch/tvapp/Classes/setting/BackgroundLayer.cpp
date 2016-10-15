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

cocos2d::Scene* BackgroundLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    BackgroundLayer* layer = BackgroundLayer::create();
    scene->addChild(layer);
    return scene;
}

bool BackgroundLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void BackgroundLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    _background = Sprite::create();
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(_background);
    
    btnBack = MenuItemSprite::create(Sprite::create(getNameWithResolution("back_nor").c_str()),
                                       Sprite::create(getNameWithResolution("back_act").c_str()),
                                       this, menu_selector(BackgroundLayer::onBack));
    btnBack->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBack->setScale(getScaleWithDevice());
    
    _title = Sprite::create();
    addChild(_title);
    
    //Sprite * sprite01 =Sprite::create(getNameWithDevice("background01").c_str());
    Sprite * sprite01 =Sprite::create(getNameWithDeviceIpad("background01").c_str());
    Size bgSize= sprite01->getContentSize();
    
    float scaleX=getSizeWithDevice(160.0f)/bgSize.width;
    float scaleY=getSizeWithDevice(160.0f)/bgSize.height;
    
    sprite01->cocos2d::Node::setScale(scaleX, scaleY);
    sprite01->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG01 = MenuItemSprite::create(sprite01, sprite01, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //Sprite * sprite02 =Sprite::create(getNameWithDevice("background02").c_str());
    Sprite * sprite02 =Sprite::create(getNameWithDeviceIpad("background02").c_str());
    sprite02->cocos2d::CCNode::setScale(scaleX, scaleY);
    sprite02->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG02 = MenuItemSprite::create(sprite02, sprite02, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //Sprite * sprite03 =Sprite::create(getNameWithDevice("background03").c_str());
    Sprite * sprite03 =Sprite::create(getNameWithDeviceIpad("background03").c_str());
    sprite03->cocos2d::Node::setScale(scaleX, scaleY);
    sprite03->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG03 = MenuItemSprite::create(sprite03, sprite03, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //Sprite * sprite04 =Sprite::create(getNameWithDevice("background04").c_str());
    Sprite * sprite04 =Sprite::create(getNameWithDeviceIpad("background04").c_str());
    sprite04->cocos2d::Node::setScale(scaleX, scaleY);
    sprite04->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG04 = MenuItemSprite::create(sprite04, sprite04, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //Sprite * sprite05 =Sprite::create(getNameWithDevice("background05").c_str());
    Sprite * sprite05 =Sprite::create(getNameWithDeviceIpad("background05").c_str());
    sprite05->cocos2d::Node::setScale(scaleX, scaleY);
    sprite05->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG05 = MenuItemSprite::create(sprite05, sprite05, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //Sprite * sprite06 =Sprite::create(getNameWithDevice("background06").c_str());
    Sprite * sprite06 =Sprite::create(getNameWithDeviceIpad("background06").c_str());
    sprite06->cocos2d::Node::setScale(scaleX, scaleY);
    sprite06->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG06 = MenuItemSprite::create(sprite06, sprite06, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    //Sprite * sprite07 =Sprite::create(getNameWithDevice("background07").c_str());
    Sprite * sprite07 =Sprite::create(getNameWithDeviceIpad("background07").c_str());
    sprite07->cocos2d::Node::setScale(scaleX, scaleY);
    sprite07->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG07 = MenuItemSprite::create(sprite07, sprite07, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    Sprite * sprite08 =Sprite::create(getNameWithDevice("background08").c_str());
    
    bgSize= sprite08->getContentSize();
    
    scaleX=getSizeWithDevice(160.0f)/bgSize.width;
    scaleY=getSizeWithDevice(160.0f)/bgSize.height;
    
    sprite08->cocos2d::Node::setScale(scaleX, scaleY);
    sprite08->setContentSize(Size(getSizeWithDevice(160.0f), getSizeWithDevice(160.0f)));
    btnBG08 = MenuItemSprite::create(sprite08, sprite08, this, menu_selector(BackgroundLayer::onBackgroundSelected));
    
    btnBG01->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBG02->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBG03->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBG04->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnBG05->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBG06->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBG07->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBG08->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnBG01->setScale(getScaleWithDevice());
    btnBG02->setScale(getScaleWithDevice());
    btnBG03->setScale(getScaleWithDevice());
    btnBG04->setScale(getScaleWithDevice());
    
    btnBG05->setScale(getScaleWithDevice());
    btnBG06->setScale(getScaleWithDevice());
    btnBG07->setScale(getScaleWithDevice());
    btnBG08->setScale(getScaleWithDevice());
    
    _menu = Menu::create();
    
    _menu->addChild(btnBack);
    
    addChild(btnBG01, 1, TAG_BG01);
    addChild(btnBG02, 1, TAG_BG02);
    addChild(btnBG03, 1, TAG_BG03);
    addChild(btnBG04, 1, TAG_BG04);
    addChild(btnBG05, 1, TAG_BG05);
    addChild(btnBG06, 1, TAG_BG06);
    addChild(btnBG07, 1, TAG_BG07);
    addChild(btnBG08, 1, TAG_NATIVE);
    
//    _menu->addChild(btnBG01, 1, TAG_BG01);
//    _menu->addChild(btnBG02, 1, TAG_BG02);
//    _menu->addChild(btnBG03, 1, TAG_BG03);
//    _menu->addChild(btnBG04, 1, TAG_BG04);
//    
//    _menu->addChild(btnBG05, 1, TAG_BG05);
//    _menu->addChild(btnBG06, 1, TAG_BG06);
//    _menu->addChild(btnBG07, 1, TAG_BG07);
//    _menu->addChild(btnBG08, 1, TAG_NATIVE);
    _menu->setVisible(false);
    
    addChild(_menu);
    
    if(arrowSprite) removeChild(arrowSprite);
    
    arrowSprite = MenuItemSprite::create(Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         this, menu_selector(BoardLayer::onDummy));
    arrowSprite->setScale(0.5);
    arrowSprite->setAnchorPoint(Vec2(0.5, 1));
    arrowSprite->setPosition(Vec2(960, 540));
    addChild(arrowSprite, 1000);
    
    lastMovedPoint = Vec2(960, 540);
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
}

void BackgroundLayer::updateLayoutWithPortrait()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(Vec2(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_port").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.7f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(460.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        Point pos = Vec2(0, 0);
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
        
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        
        item->setPosition(pos);
    }
    
    _menu->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
}

void BackgroundLayer::updateLayoutWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(Vec2(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        Point pos = Vec2(960, 540);
        switch (i) {
            case TAG_BG01:
                pos.x = 400;
                pos.y = 520;
                break;
            case TAG_BG02:
                pos.x = 400;
                pos.y = 200;
                break;
            case TAG_BG03:
                pos.x = 750;
                pos.y = 520;
                break;
            case TAG_BG04:
                pos.x = 750;
                pos.y = 200;
                break;
            case TAG_BG05:
                pos.x = 1170;
                pos.y = 520;
                break;
            case TAG_BG06:
                pos.x = 1170;
                pos.y = 200;
                break;
                
            case TAG_BG07:
                pos.x = 1520;
                pos.y = 520;
                break;
            case TAG_NATIVE:
                pos.x = 1520;
                pos.y = 200;
                break;
            default:
                break;
        }
        
        Sprite* item = (Sprite*)getChildByTag(i);
        item->setPosition(pos);
    }
    
    _menu->setPosition(Vec2(0, 0));
    _menu->setVisible(true);
}

void BackgroundLayer::onBackgroundSelected(Ref* sender)
{
    //Background selected
    
    MenuItem* item = (MenuItem*)sender;
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

void BackgroundLayer::didFinishPickingWithResult(cocos2d::Texture2D* result)
{
    CCLog("%s", "BackgroundLayer didFinishPickingWithResult");
    if(result==NULL) return;
    
    GameData::getInstance()->setBackgroundIndex(TAG_NATIVE);
    ((GameLayer*)_parentLayer)->setBackground(result);
}

void BackgroundLayer::onBack(Ref* sender)
{
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

void BackgroundLayer::pressBegan()
{
    CCLOG("Taskbarlayer - press began : (%f, %f)", lastMovedPoint.x, lastMovedPoint.y);
    Vec2 touchPoint = (lastMovedPoint);
    
    if(btnBG01->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG01->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnBG02->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG02->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnBG03->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG03->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnBG04->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG04->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnBG04->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG04->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnBG05->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG05->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnBG06->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG06->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnBG07->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::onBackgroundSelected,this));
        btnBG07->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
}

bool BackgroundLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(!this->isVisible()) return false;
    
    log("lastMovedPoint: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
    
    prevPoint = touch->getLocation();
    
    return true;
}

void BackgroundLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
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

void BackgroundLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("touch end: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
}
