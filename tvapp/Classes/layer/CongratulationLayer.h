//
//  CongratulationLayer.h
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__CongratulationLayer__
#define __cardgame__CongratulationLayer__

#include "Common.h"

class CongratulationLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void init(CCLayer* parent);
    
private:
        
    void onFacebook(CCObject* sender);
    void onTwitter(CCObject* sender);
    void onChat(CCObject* sender);
    void onMail(CCObject* sender);
    void onGameCenter(CCObject* sender);
    void onReplay(CCObject* sender);
    void onDone(CCObject* sender);
    
    std::string getMessage();
    
private:
    CCLayer* _parentLayer;    
    CCMenu* _menu;
    
public:
    CREATE_FUNC(CongratulationLayer);
};

#endif
 /* defined(__cardgame__CongratulationLayer__) */
