//
//  OrientationLayer.h
//  cardgame
//
//  Created by lion on 3/7/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__OrientationLayer__
#define __cardgame__OrientationLayer__

#include "Common.h"
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;//Cocos2dx defined macros
using namespace cocos2d;

class OrientationLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
    void onAutoMode(CCObject* sender);
    void onPortraitMode(CCObject* sender);
    void onLandscapeMode(CCObject* sender);
    void onDone(CCObject* sender);
    
private:
    void createMenuWithEasy();
    void createMenuWithNormal();
    void createMenuWithHard();
    
private:
    CCLayer* _parentLayer;
    CCMenuItem* _easyItem;
    CCMenuItem* _normalItem;
    CCMenuItem* _hardItem;
    CCMenu* _menu;
    
public:
    CREATE_FUNC(OrientationLayer);
};

#endif
