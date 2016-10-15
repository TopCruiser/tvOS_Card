//
//  CongratulationLayer.h
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//
#include "Common.h"
#include <iostream>

class TipLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
private:
    Layer* _parentLayer;
    
public:
    CREATE_FUNC(TipLayer);
};

