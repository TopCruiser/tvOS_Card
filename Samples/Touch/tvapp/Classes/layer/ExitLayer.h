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

class ExitLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
    
private:
    void onYES(CCObject* sender);
    void onNO(CCObject* sender);
    void didAction();
    
private:
    CCLayer* _parentLayer;
    CCMenu* _menu;
    bool _isYes;
    
public:
    CREATE_FUNC(ExitLayer);
};

#endif /* defined(__cardgame__ExitLayer__) */