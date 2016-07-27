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
    MenuItem* btnForty = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_fortythieves_nor").c_str()),
                                                    Sprite::create(getNameWithResolution("btn_fortythieves_act").c_str()),
                                                    this, menu_selector(MenuLayer::onFortyThieves));
    MenuItem* btnFreecell = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_freecell_nor").c_str()),
                                                       Sprite::create(getNameWithResolution("btn_freecell_act").c_str()),
                                                       this, menu_selector(MenuLayer::onFreeCell));
    MenuItem* btnSpider = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_spider_nor").c_str()),
                                                     Sprite::create(getNameWithResolution("btn_spider_act").c_str()),
                                                     this, menu_selector(MenuLayer::onSpiderSolitaire));
    
    //add dummy object to receive focus
    MenuItem* dummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_freecell_nor").c_str()),
                                             Sprite::create(getNameWithResolution("btn_freecell_act").c_str()),
                                             this, menu_selector(MenuLayer::onDummy));
    dummy->setScale(0.01);
    
    btnSolitaire->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnForty->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnFreecell->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnSpider->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnSolitaire->setScale(1.0);
    btnForty->setScale(1.0);
    btnFreecell->setScale(1.0);
    btnSpider->setScale(1.0);
    
    _menu = Menu::create();
    _menu->addChild(btnSolitaire, 1, TAG_SOLITAIRE);
    _menu->addChild(btnForty, 1, TAG_FORTY_THIEVES);
    _menu->addChild(btnFreecell, 1, TAG_FREECELL);
    _menu->addChild(btnSpider, 1, TAG_SPIDER_SOLITAIRE);
    _menu->addChild(dummy);
    _menu->setVisible(false);
    
    addChild(_menu);
    
    
    //event register
//#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    Controller::startDiscoveryController();
//#endif
    
    _controllerListener = EventListenerController::create();
    
    _controllerListener->onConnected = CC_CALLBACK_2(MenuLayer::onConnectController,this);
    _controllerListener->onDisconnected = CC_CALLBACK_2(MenuLayer::onDisconnectedController,this);
    _controllerListener->onKeyDown = CC_CALLBACK_3(MenuLayer::onKeyDown, this);
    _controllerListener->onKeyUp = CC_CALLBACK_3(MenuLayer::onKeyUp, this);
    _controllerListener->onAxisEvent = CC_CALLBACK_3(MenuLayer::onAxisEvent, this);
    _controllerListener->onKeyRepeat = CC_CALLBACK_3(MenuLayer::onKeyRepeat, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);

    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(MenuLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MenuLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MenuLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    setTag(100);
    
//    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
//    setTouchEnabled(true);
    
    return true;
}

void MenuLayer::onDummy(Ref* sender)
{
    
}

void MenuLayer::onEnterTransitionDidFinish()
{
    //if(g_nOrientation == ORIENTATION_PORTRAIT || g_nOrientation == ORIENTATION_PORTRAIT_UPSIDEDOWN)
        //updateLayoutWithPortrait();
//    else if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)comment716
          updateLayoutWithLandscape();
    
    //AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Home Screen", 1);comment715
}

void MenuLayer::updateLayoutWithPortrait()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    _title->initWithFile(getNameWithResolution("logo_port").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.7f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(460.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        Point pos = Vec2(0, 0);
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
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        Point pos = Vec2(0, 0);
        switch (i) {
            case TAG_SOLITAIRE:
                pos.x = -getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(20);
//                pos.x = 0;
//                pos.y = 0;
                break;
            case TAG_FORTY_THIEVES:
                pos.x = -getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(175);
                break;
            case TAG_FREECELL:
                pos.x = getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(20);
//                pos.x = 0;
//                pos.y = 0;
                break;
            case TAG_SPIDER_SOLITAIRE:
                pos.x = getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(175);
                break;
            case TAG_MAX:
                pos.x = 100;
                pos.y = 100;
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

bool MenuLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("lastMovedPoint: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
    
//    Vec2 pos = btnSolitaire->getPosition();
//    Rect r = Rect(btnSolitaire->getPosition(), Size(200, 200));
//    
//    if(r.containsPoint(lastMovedPoint))
//    {
//        btnSolitaire->setScale(1.0);
//    }
//    else
//    {
//        btnSolitaire->setScale(0.9);
//    }
    return true;
}

void MenuLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Director* director = Director::getInstance();
    Point location = touch->getLocationInView();
    location = director->convertToGL(location);
    lastMovedPoint = location;
    
    Vec2 pos = btnSolitaire->getPosition();
    pos = director->convertToGL(pos);
    Rect r = Rect(btnSolitaire->getPosition(), Size(200, 200));
    
    if(r.containsPoint(lastMovedPoint))
    {
        btnSolitaire->setScale(1.0);
    }
    else
    {
        btnSolitaire->setScale(0.9);
    }
    
    log("touch move: %f, %f", location.x, location.y);
}

void MenuLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
//    Director* director = Director::getInstance();
//    Point location = touch->getLocationInView();
//    location = director->convertToGL(location);
//    lastMovedPoint = location;
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

//bool MenuLayer::handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//    Vec2 location = convertToNodeSpace(touch->getLocation());
//    
//    if(btnSolitaire->getBoundingBox().containsPoint(location))
//    {
//        log("detect menu item");
//    }
//    //log("touch begin: %f, %f", location.x, location.y);
//    
//    return true;
//}
//
//void MenuLayer::handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//    Vec2 location = convertToNodeSpace(touch->getLocation());
//    
//    if(btnSolitaire->getBoundingBox().containsPoint(location))
//    {
//        log("detect menu item");
//    }
//    
//    log("touch moved: %f, %f", location.x, location.y);
//}
//
//void MenuLayer::handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//    Vec2 location = convertToNodeSpace(touch->getLocation());
//    
//    log("touch ended: %f, %f", location.x, location.y);
//}

void MenuLayer::onConnectController(cocos2d::Controller* controller, cocos2d::Event* event)
{
    log("Controller connected %s", controller->getDeviceName().c_str());
    
    //controller->setAbsoluteDpadValues(true);
}

void MenuLayer::onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event)
{
}

void MenuLayer::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
    
    if (key == Controller::BUTTON_X)
    {
        //Director::getInstance()->replaceScene(Game::create());
    }
    
#endif
}

void MenuLayer::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    log("key up: %d", key);
}

void MenuLayer::onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event)
{
    log("axis event: %d", axis);
}

void MenuLayer::onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    log("key repeat: %d", key);
    
    if (key == cocos2d::Controller::BUTTON_DPAD_LEFT)
    {
        log("Left value: %f", controller->getKeyStatus(key).value);
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_RIGHT)
    {
        log("Right value: %f", controller->getKeyStatus(key).value);
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_UP)
    {
        log("Up value: %f", controller->getKeyStatus(key).value);
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_DOWN)
    {
        log("Down value: %f", controller->getKeyStatus(key).value);
    }
}

