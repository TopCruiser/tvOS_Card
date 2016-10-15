//
//  MenuLayer.cpp
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "MenuLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "AppDelegate.h"

enum MENU_TAG {
    TAG_SOLITAIRE = 0,
    TAG_FORTY_THIEVES,
    TAG_FREECELL,
    TAG_SPIDER_SOLITAIRE,
    TAG_MAX
};

Scene* MenuLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    MenuLayer* layer = MenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MenuLayer::init()
{
    if(!Layer::init())
        return false;
    
    GameData::getInstance()->setMenuLayer(true);
    
    _background = Sprite::create();
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(_background);
    
    _title = Sprite::create();
    addChild(_title);
    
    btnSolitaire = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_solitaire_nor").c_str()),
                                                        Sprite::create(getNameWithResolution("btn_solitaire_act").c_str()),
                                                        this, menu_selector(MenuLayer::onSolitaire));
    btnForty = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_fortythieves_nor").c_str()),
                                                    Sprite::create(getNameWithResolution("btn_fortythieves_act").c_str()),
                                                    this, menu_selector(MenuLayer::onFortyThieves));
    btnFreecell = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_freecell_nor").c_str()),
                                                       Sprite::create(getNameWithResolution("btn_freecell_act").c_str()),
                                                       this, menu_selector(MenuLayer::onFreeCell));
    btnSpider = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_spider_nor").c_str()),
                                                     Sprite::create(getNameWithResolution("btn_spider_act").c_str()),
                                                     this, menu_selector(MenuLayer::onSpiderSolitaire));
    
    //add dummy object to receive focus
    MenuItem* dummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_freecell_nor").c_str()),
                                             Sprite::create(getNameWithResolution("btn_freecell_act").c_str()),
                                             this, menu_selector(MenuLayer::onDummy));
    dummy->setScale(0.001);
    //dummy->setPosition(Vec2(960, 540));
    
    btnSolitaire->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnForty->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnFreecell->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnSpider->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnSolitaire->setScale(0.8);
    btnForty->setScale(0.8);
    btnFreecell->setScale(0.8);
    btnSpider->setScale(0.8);
    
    _menu = Menu::create();
    _menu->addChild(btnSolitaire, 1, TAG_SOLITAIRE);
    _menu->addChild(btnForty, 1, TAG_FORTY_THIEVES);
    _menu->addChild(btnFreecell, 1, TAG_FREECELL);
    _menu->addChild(btnSpider, 1, TAG_SPIDER_SOLITAIRE);
    _menu->addChild(dummy);
    _menu->setVisible(false);
    
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
    arrowSprite->setPosition(Vec2(960, 540));
    addChild(arrowSprite, 1000);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    lastMovedPoint = Vec2(960, 540);
    
//    if(!g_bTipDisplay)
//    {
//        tipLayer = TipLayer::create();
//        tipLayer->init(this);
//        tipLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
//        tipLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
//        addChild(tipLayer, 6);
//        g_bTipDisplay = true;
//    }
    setTag(100);
    return true;
}

void MenuLayer::onDummy(Ref* sender)
{
    
}

void MenuLayer::onEnterTransitionDidFinish()
{
    updateLayoutWithLandscape();
}

void MenuLayer::updateLayoutWithPortrait()
{
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    _title->initWithFile(getNameWithResolution("logo_port").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.7f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(460.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        cocos2d::Point pos = Vec2(0, 0);
        switch (i) {
            case TAG_SOLITAIRE:
                pos.x = getSizeWithDevice(0);
                pos.y = getSizeWithDevice(90);
                break;
            case TAG_FORTY_THIEVES:
                pos.x = getSizeWithDevice(0);
                pos.y = -getSizeWithDevice(60);
                break;
            case TAG_FREECELL:
                pos.x = getSizeWithDevice(0);
                pos.y = -getSizeWithDevice(210);
                break;
            case TAG_SPIDER_SOLITAIRE:
                pos.x = getSizeWithDevice(0);
                pos.y = -getSizeWithDevice(360);
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

void MenuLayer::updateLayoutWithLandscape()
{
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        cocos2d::Point pos = Vec2(960, 540);
        switch (i) {
            case TAG_SOLITAIRE:
                pos.x = getSizeWithDevice(280);
                pos.y = getSizeWithDevice(240);
                break;
            case TAG_FORTY_THIEVES:
                pos.x = getSizeWithDevice(660);
                pos.y = getSizeWithDevice(240);
                break;
            case TAG_FREECELL:
                pos.x = getSizeWithDevice(280);
                pos.y = getSizeWithDevice(100);
                break;
            case TAG_SPIDER_SOLITAIRE:
                pos.x = getSizeWithDevice(660);
                pos.y = getSizeWithDevice(100);
                break;
//            case TAG_MAX:
//                pos.x = 100;
//                pos.y = 100;
//                break;
            default:
                break;
        }
        
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
    }
    
    //_menu->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setPosition(Vec2(0, 0));
    _menu->setVisible(true);
}

bool MenuLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("lastMovedPoint: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
    
    prevPoint = touch->getLocation();
    
    return true;
}

void MenuLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
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

void MenuLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("touch end: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
}

void MenuLayer::onSolitaire(Ref* sender)
{   //solitaire game select
    GameData::getInstance()->playSoundEffect();
    GameData::getInstance()->setGameType(TYPE_SOLITAIRE);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::scene()));
}

void MenuLayer::onFreeCell(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    GameData::getInstance()->setGameType(TYPE_FREECELL);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::scene()));
}

void MenuLayer::onFortyThieves(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    GameData::getInstance()->setGameType(TYPE_FORTY_THIEVES);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::scene()));
}

void MenuLayer::onSpiderSolitaire(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    GameData::getInstance()->setGameType(TYPE_SPIDER);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::scene()));
}

//event listener
void MenuLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    log("key pressed: %d", keyCode);
}

void MenuLayer::hideHintLayer()
{
    if(tipLayer->isVisible())
        tipLayer->setVisible(false);
}

void MenuLayer::pressBegan()
{
    CCLOG("Taskbarlayer - press began : (%f, %f)", lastMovedPoint.x, lastMovedPoint.y);
    Vec2 touchPoint = convertToNodeSpace(lastMovedPoint);
    
    if(btnSolitaire->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(MenuLayer::onSolitaire,this));
        btnSolitaire->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnForty->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(MenuLayer::onFortyThieves,this));
        btnForty->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnFreecell->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(MenuLayer::onFreeCell,this));
        btnFreecell->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnSpider->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(MenuLayer::onSpiderSolitaire,this));
        btnSpider->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
}
