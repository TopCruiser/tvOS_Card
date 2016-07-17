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
    
    MenuItem* btnSolitaire = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_solitaire_nor").c_str()),
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
    
    btnSolitaire->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnForty->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnFreecell->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnSpider->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnSolitaire->setScale(getScaleWithDevice());
    btnForty->setScale(getScaleWithDevice());
    btnFreecell->setScale(getScaleWithDevice());
    btnSpider->setScale(getScaleWithDevice());
    
    _menu = Menu::create();
    _menu->addChild(btnSolitaire, 1, TAG_SOLITAIRE);
    _menu->addChild(btnForty, 1, TAG_FORTY_THIEVES);
    _menu->addChild(btnFreecell, 1, TAG_FREECELL);
    _menu->addChild(btnSpider, 1, TAG_SPIDER_SOLITAIRE);
    _menu->setVisible(false);
    
    addChild(_menu);
    
    return true;
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
        Point pos = CCPointZero;
        switch (i) {
            case TAG_SOLITAIRE:
                pos.x = -getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_FORTY_THIEVES:
                pos.x = -getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(175);
                break;
            case TAG_FREECELL:
                pos.x = getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_SPIDER_SOLITAIRE:
                pos.x = getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(175);
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