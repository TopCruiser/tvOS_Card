//
//  LoadLayer.cpp
//  cardgame
//
//  Created by Pink on 2/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "LoadLayer.h"
#include "MenuLayer.h"

cocos2d::Scene* LoadLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    LoadLayer* layer = LoadLayer::create();
    scene->addChild(layer);
    return scene;
}

bool LoadLayer::init()
{
    if(!Layer::init())
        return false;
    
    _lastUpdateTime = 0.0f;
    _tempUpdateTime = 0.0f;
    
    _background = Sprite::create();
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(_background);
    
    _logo = Sprite::create();
    _logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(_logo);
    
    //scheduleUpdate();
    
    return true;
}

void LoadLayer::update(float dt)
{
    _tempUpdateTime += dt;
    
    if((_tempUpdateTime - _lastUpdateTime) >= 2.0f) {
        runMenuLayer();
        unscheduleUpdate();
    }
}

void LoadLayer::onEnterTransitionDidFinish()
{
    scheduleUpdate();
    //loading screent setting
    if(g_nOrientation == ORIENTATION_PORTRAIT || g_nOrientation == ORIENTATION_PORTRAIT_UPSIDEDOWN)
        updateLayoutWithPortrait();
    else if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)
        updateLayoutWithLandscape();
}

void LoadLayer::updateLayoutWithPortrait()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("logobg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    _logo->initWithFile(getNameWithResolution("logo_port").c_str());
    _logo->setScale(getScaleWithDevice());
    _logo->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
}

void LoadLayer::updateLayoutWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("logobg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    _logo->initWithFile(getNameWithResolution("logo_land").c_str());
    _logo->setScale(getScaleWithDevice());
    _logo->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
}

void LoadLayer::runMenuLayer()
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MenuLayer::scene()));
    //Director::getInstance()->resume();
}
