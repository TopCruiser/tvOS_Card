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

class BackgroundLayer : public cocos2d::CCLayer, ImagePickerDelegate
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
    virtual void didFinishPickingWithResult(cocos2d::CCTexture2D* result);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
private:
    void onBackgroundSelected(CCObject* sender);
    void onBack(CCObject* sender);
    
private:
    CCLayer* _parentLayer;
    CCSprite* _background;
    CCSprite* _title;
    CCMenu* _menu;
    
    CCMenuItem* btnBack;
    
    CCMenuItem* btnBG01;
    CCMenuItem* btnBG02;
    CCMenuItem* btnBG03;
    CCMenuItem* btnBG04;
    CCMenuItem* btnBG05;
    CCMenuItem* btnBG06;
    CCMenuItem* btnBG07;
    CCMenuItem* btnBG08;
    
public:
    CREATE_FUNC(BackgroundLayer);
};

#endif /* defined(__cardgame__BackgroundLayer__) */
