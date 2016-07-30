//
//  ExitLayer.h
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__ExitLayer__
#define __cardgame__ExitLayer__

#include "Common.h"

class ExitLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
    
private:
    void onYES(Ref* sender);
    void onNO(Ref* sender);
    void onDummy(Ref* sender);
    void didAction();
    
private:
    Layer* _parentLayer;
    Menu* _menu;
    bool _isYes;
    
public:
    CREATE_FUNC(ExitLayer);
};

#endif /* defined(__cardgame__ExitLayer__) */