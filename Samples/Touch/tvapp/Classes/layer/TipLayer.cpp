//
//  CongratulationLayer.cpp
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "TipLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "AppDelegate.h"

cocos2d::Scene* TipLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    TipLayer* layer = TipLayer::create();
    scene->addChild(layer);
    return scene;
}

bool TipLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void TipLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    Sprite* background = Sprite::create("images.jpg");
    background->setScale(getScaleWithDevice());
    background->setPosition(Vec2(0.0f, 0.0f));
    background->setOpacity(127);
    addChild(background);
    
    Sprite* remote = Sprite::create("remote controller.png");
    remote->setScale(getScaleWithDevice());
    remote->setPosition(Vec2(300.0f, -300.0f));
    addChild(remote);
    
    Size size = background->getContentSize();
    setContentSize(size);
    
    Sprite* hintSprite = Sprite::create("hint_icon.png");
    hintSprite->setScale(0.8);
    hintSprite->setPosition(Vec2(300.0, -150.0));
    addChild(hintSprite);
    
    FadeTo* fadeIn = FadeTo::create(0.1, 127);
    FadeTo* fadeOut = FadeTo::create(0.1, 255);
    MoveTo* moveTo = MoveTo::create(0.4f, Vec2(220.0, -100.0));
    MoveTo* moveTo1 = MoveTo::create(0.01f, Vec2(300.0, -150.0));
    
    hintSprite->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.4f),
                                                                 fadeIn,
                                                                 DelayTime::create(0.5f),
                                                                 moveTo,
                                                                 DelayTime::create(0.2f),
                                                                 fadeOut,
                                                                 DelayTime::create(0.5f),
                                                                 moveTo1,
                                                                 NULL)));
    
    Size textSize;
    textSize = Size(size.width - getSizeWithDevice(120), getSizeWithDevice(700));
    //CCLabelTTF* _cellLabel = CCLabelTTF::create("Gesture Tip\n This game allows you to interact with all buttons using only Touch gesture.", "Thonburi", getSizeWithDevice(25), Size(0, 0), kCCTextAlignmentCenter);
    
//    Label* _cellLabel = Label::createWithTTF("Gesture Tip\n This game allows you to interact with all buttons \nusing only Touch gesture.", "tt0283m.ttf", getSizeWithDevice(25));
//    
//    _cellLabel->setAlignment(TextHAlignment::CENTER);
//    _cellLabel->setTextColor(Color4B(255, 255, 0, 255));
//    _cellLabel->setAnchorPoint(Vec2(0, 0));
//    _cellLabel->setPosition(Vec2(-900, 300));
//    
//    addChild(_cellLabel);
    
    Label* comment = Label::createWithTTF("Not press on Remote Controller! Move finger holding tap on it \ntoward destination button. Look out touch start point and moving distance.\n Touch should be started on center of the screen\n and moved to the destination button by distance between center and button.", "tt0283m.ttf", getSizeWithDevice(20));
    
    comment->setAlignment(TextHAlignment::CENTER);
    comment->setTextColor(Color4B(0, 255, 0, 255));
    comment->setAnchorPoint(Vec2(0, 0));
    comment->setPosition(Vec2(-750, 150));
    
    addChild(comment);
    
    Sprite* arrow = Sprite::create("arrow left.png");
    arrow->setScale(0.8);
    arrow->setPosition(Vec2(20.0, -250.0));
    arrow->setAnchorPoint(Vec2(1.0, 0.0));
    addChild(arrow);
    
    FadeTo* fade1 = FadeTo::create(1.5, 100);
    FadeTo* fade2 = FadeTo::create(0.6, 255);
    arrow->runAction(RepeatForever::create(Sequence::create(fade1, fade2, NULL)));
    
    setTag(200);
}
