//
//  BackgroundLayer.h
//  cardgame
//
//  Created by lion on 3/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__BackgroundLayer__
#define __cardgame__BackgroundLayer__

#include "Common.h"
#include "ImagePicker.h"

class BackgroundLayer : public cocos2d::Layer, ImagePickerDelegate
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    virtual void didFinishPickingWithResult(cocos2d::Texture2D* result);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void pressBegan();
    
private:
    void onBackgroundSelected(Ref* sender);
    void onBack(Ref* sender);
    
private:
    Layer* _parentLayer;
    Sprite* _background;
    Sprite* _title;
    Menu* _menu;
    
    MenuItem* btnBack;
    
    MenuItem* btnBG01;
    MenuItem* btnBG02;
    MenuItem* btnBG03;
    MenuItem* btnBG04;
    MenuItem* btnBG05;
    MenuItem* btnBG06;
    MenuItem* btnBG07;
    MenuItem* btnBG08;
    
    Vec2 lastMovedPoint;
    Vec2 prevPoint;
    
    MenuItem* arrowSprite;
    
    
    
public:
    CREATE_FUNC(BackgroundLayer);
};

#endif /* defined(__cardgame__BackgroundLayer__) */
