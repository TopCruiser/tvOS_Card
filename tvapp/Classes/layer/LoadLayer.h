//
//  LoadLayer.h
//  cardgame
//
//  Created by Pink on 2/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__LoadLayer__
#define __cardgame__LoadLayer__

#include "Common.h"

class LoadLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void update(float dt);
    virtual void onEnterTransitionDidFinish();
    
private:
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    void runMenuLayer();
    
private:
    CCSprite* _background = NULL;
    CCSprite* _logo = NULL;
    
    float _lastUpdateTime;
    float _tempUpdateTime;
    
public:
    CREATE_FUNC(LoadLayer);
};

#endif