//
//  LoadLayer.h
//  cardgame
//
//  Created by Pink on 2/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Common.h"

class LoadLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void update(float dt);
    virtual void onEnterTransitionDidFinish();
    
private:
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    void runMenuLayer();
    
private:
    Sprite* _background = NULL;
    Sprite* _logo = NULL;
    
    float _lastUpdateTime;
    float _tempUpdateTime;
    
public:
    CREATE_FUNC(LoadLayer);
};
