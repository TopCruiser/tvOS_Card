//
//  CongratulationLayer.h
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Common.h"

class TipLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual void init(Layer* parent);
    
private:
        
    void onFacebook(Ref* sender);
    void onTwitter(Ref* sender);
    void onChat(Ref* sender);
    void onMail(Ref* sender);
    void onGameCenter(Ref* sender);
    void onReplay(Ref* sender);
    void onDone(Ref* sender);
    void onDummy(Ref* sender);
    
    std::string getMessage();
    
private:
    Layer* _parentLayer;
    Menu* _menu;
    
public:
    CREATE_FUNC(TipLayer);
};

 /* defined(__cardgame__CongratulationLayer__) */
