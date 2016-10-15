//
//  CardFaceLayer.cpp
//  cardgame
//
//  Created by lion on 3/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "CardFaceLayer.h"
#include "GameLayer.h"
#include "GameData.h"

enum MENU_TAG {
    TAG_CARD01 = 0,
    TAG_CARD02,
    TAG_CARD03,
    TAG_CARD04,
    TAG_CARD05,
    TAG_CARD06,
    TAG_CARD07,
    TAG_CARD08,
    TAG_CARD09,
    TAG_CARD10,
    TAG_MAX
};

cocos2d::Scene* CardFaceLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    CardFaceLayer* layer = CardFaceLayer::create();
    scene->addChild(layer);
    return scene;
}

bool CardFaceLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void CardFaceLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    _background = Sprite::create();
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(_background);
    
    _title = Sprite::create();
    addChild(_title);
    
    btnBack = MenuItemSprite::create(Sprite::create(getNameWithResolution("back_nor").c_str()),
                                       Sprite::create(getNameWithResolution("back_act").c_str()),
                                       this, menu_selector(CardFaceLayer::onBack));
    btnBack->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBack->setScale(getScaleWithDevice());
    
    sprite00=Sprite::create(getNameWithResolution("spade1_10").c_str());
    sprite01=Sprite::create(getNameWithResolution("spade1_11").c_str());
    sprite02=Sprite::create(getNameWithResolution("spade1_12").c_str());
    sprite03=Sprite::create(getNameWithResolution("spade1_13").c_str());
    sprite04=Sprite::create(getNameWithResolution("spade1_1").c_str());
    sprite05=Sprite::create(getNameWithResolution("spade2_10").c_str());
    sprite06=Sprite::create(getNameWithResolution("spade2_11").c_str());
    sprite07=Sprite::create(getNameWithResolution("spade2_12").c_str());
    sprite08=Sprite::create(getNameWithResolution("spade2_13").c_str());
    sprite09=Sprite::create(getNameWithResolution("spade2_1").c_str());
    
    switch (GameData::getInstance()->getCardFaceIndex()) {
        case 0:
            sprite00->initWithFile(getNameWithResolution("spade3_10").c_str());
            sprite01->initWithFile(getNameWithResolution("spade3_11").c_str());
            sprite02->initWithFile(getNameWithResolution("spade3_12").c_str());
            sprite03->initWithFile(getNameWithResolution("spade3_13").c_str());
            sprite04->initWithFile(getNameWithResolution("spade3_1").c_str());
            break;
        case 1:
            sprite05->initWithFile(getNameWithResolution("spade3_10").c_str());
            sprite06->initWithFile(getNameWithResolution("spade3_11").c_str());
            sprite07->initWithFile(getNameWithResolution("spade3_12").c_str());
            sprite08->initWithFile(getNameWithResolution("spade3_13").c_str());
            sprite09->initWithFile(getNameWithResolution("spade3_1").c_str());
            break;
        default:
            break;
    }
    
    btnCard01 = MenuItemSprite::create(sprite00,sprite00,this, menu_selector(CardFaceLayer::onCardTap));
    btnCard02 = MenuItemSprite::create(sprite01,sprite01,this, menu_selector(CardFaceLayer::onCardTap));
    btnCard03 = MenuItemSprite::create(sprite02,sprite02, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard04 = MenuItemSprite::create(sprite03,sprite03,this, menu_selector(CardFaceLayer::onCardTap));
    //btnCard05 = MenuItemSprite::create(sprite04,sprite04, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard06 = MenuItemSprite::create(sprite05,sprite05, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard07 = MenuItemSprite::create(sprite06,sprite06, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard08 = MenuItemSprite::create(sprite07,sprite07, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard09 = MenuItemSprite::create(sprite08,sprite08, this, menu_selector(CardFaceLayer::onCardTap));
    //btnCard10 = MenuItemSprite::create(sprite09,sprite09, this, menu_selector(CardFaceLayer::onCardTap));
    
    btnCard01->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard02->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard03->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard04->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    //btnCard05->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard06->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard07->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard08->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard09->setAnchorPoint(Vec2(0.5f, 0.5f));
    //btnCard10->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard01->setScale(getScaleWithDevice());
    btnCard02->setScale(getScaleWithDevice());
    btnCard03->setScale(getScaleWithDevice());
    btnCard04->setScale(getScaleWithDevice());
    
    //btnCard05->setScale(getScaleWithDevice());
    btnCard06->setScale(getScaleWithDevice());
    btnCard07->setScale(getScaleWithDevice());
    btnCard08->setScale(getScaleWithDevice());
    btnCard09->setScale(getScaleWithDevice());
    //btnCard10->setScale(getScaleWithDevice());
    
    
    _menu = Menu::create();
    
    _menu->addChild(btnBack);
    
    _menu->addChild(btnCard01, 1, TAG_CARD01);
    _menu->addChild(btnCard02, 1, TAG_CARD02);
    _menu->addChild(btnCard03, 1, TAG_CARD03);
    _menu->addChild(btnCard04, 1, TAG_CARD04);
    
    //_menu->addChild(btnCard05, 1, TAG_CARD05);
    _menu->addChild(btnCard06, 1, TAG_CARD06);
    _menu->addChild(btnCard07, 1, TAG_CARD07);
    _menu->addChild(btnCard08, 1, TAG_CARD08);
    _menu->addChild(btnCard09, 1, TAG_CARD09);
    //_menu->addChild(btnCard10, 1, TAG_CARD10);
    _menu->setVisible(false);
    
    addChild(_menu);
    
    if(arrowSprite) removeChild(arrowSprite);
    
    arrowSprite = MenuItemSprite::create(Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         this, menu_selector(BoardLayer::onDummy));
    arrowSprite->setScale(0.5);
    arrowSprite->setAnchorPoint(Vec2(0.5, 1));
    arrowSprite->setPosition(Vec2(960, 540));
    addChild(arrowSprite, 1000);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    lastMovedPoint = Vec2(960, 540);
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
}

void CardFaceLayer::pressBegan()
{
    CCLOG("Taskbarlayer - press began : (%f, %f)", lastMovedPoint.x, lastMovedPoint.y);
    Vec2 touchPoint = convertToNodeSpace(lastMovedPoint);
    
    if(btnCard01->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard01->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard02->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard02->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard03->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard03->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard04->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard04->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
//    if(btnCard05->getBoundingBox().containsPoint(touchPoint))
//    {
//        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
//        btnCard05->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
//    }
    if(btnCard06->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard06->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard07->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard07->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard08->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard08->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard09->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
        btnCard09->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
//    if(btnCard10->getBoundingBox().containsPoint(touchPoint))
//    {
//        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardFaceLayer::onCardTap,this));
//        btnCard10->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
//    }
}

bool CardFaceLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(!this->isVisible()) return false;
    
    log("lastMovedPoint: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
    
    prevPoint = touch->getLocation();
    
    return true;
}

void CardFaceLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Director* director = Director::getInstance();
    Point location = touch->getLocationInView();
    location = director->convertToGL(location);
    
    //added by ccl
    Vec2 delta = location - prevPoint;
    lastMovedPoint += delta;
    
    log("touch move: %f, %f", location.x, location.y);
    
    arrowSprite->setPosition(lastMovedPoint);
    prevPoint = location;//added ccl
    
    log("touch move: %f, %f", location.x, location.y);
}

void CardFaceLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("touch end: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
}

void CardFaceLayer::updateLayoutWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(Vec2(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        Point pos = Vec2(960, 540);
        switch (i) {
            case TAG_CARD01:
                pos.x = 450;
                pos.y = 520;
                break;
            case TAG_CARD02:
                pos.x = (750);
                pos.y = (520);
                break;
            case TAG_CARD03:
                pos.x = (1050);
                pos.y = (520);
                break;
            case TAG_CARD04:
                pos.x = (1350);
                pos.y = (520);
                break;
            case TAG_CARD05:
                pos.x = (1450);
                pos.y = (520);
                break;
                
            case TAG_CARD06:
                pos.x = (450);
                pos.y = (250);
                break;
            
            case TAG_CARD07:
                pos.x = (750);
                pos.y = (250);
                break;
            
            case TAG_CARD08:
                pos.x = (1050);
                pos.y = (250);
                break;
                
            case TAG_CARD09:
                pos.x = (1350);
                pos.y = (250);
                break;
            case TAG_CARD10:
                pos.x = (1190);
                pos.y = (250);
                break;
            default:
                break;
        }
        if(i == 4 || i == 9) continue;
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
    }
    
    _menu->setPosition(Vec2(0, 0));
    _menu->setVisible(true);
}

void CardFaceLayer::onCardTap(Ref* sender)
{   //card selected
    MenuItem* item = (MenuItem*)sender;
    Blink *blink_ = Blink::create(1.0f, 7);
    item->runAction(blink_);
    
    int cardFaceIndex=item->getTag();
    
    switch (GameData::getInstance()->getCardFaceIndex()) {
        case 0:
            if(cardFaceIndex<5) {
                sprite00->initWithFile(getNameWithResolution("spade1_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade1_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade1_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade1_13").c_str());
                //sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                //sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=2;
            }
            else {
                sprite00->initWithFile(getNameWithResolution("spade1_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade1_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade1_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade1_13").c_str());
                //sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());

                sprite05->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade3_13").c_str());
                //sprite09->initWithFile(getNameWithResolution("spade3_1").c_str());
                cardFaceIndex=1;
            }
            break;
        case 1:
            if(cardFaceIndex<5) {
                sprite00->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade3_13").c_str());
                //sprite04->initWithFile(getNameWithResolution("spade3_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                //sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=0;
            }
            else {
                sprite00->initWithFile(getNameWithResolution("spade1_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade1_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade1_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade1_13").c_str());
                //sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                //sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=2;
            }
            break;
        default:
            if(cardFaceIndex<5) {
                sprite00->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade3_13").c_str());
                //sprite04->initWithFile(getNameWithResolution("spade3_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                //sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=0;
            }
            else {
                sprite00->initWithFile(getNameWithResolution("spade1_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade1_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade1_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade1_13").c_str());
                //sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade3_13").c_str());
                //sprite09->initWithFile(getNameWithResolution("spade3_1").c_str());
                cardFaceIndex=1;
            }
            break;
    }
    
    sprite00->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite01->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite02->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite03->setAnchorPoint(Vec2(0.0f, 0.0f));
    //sprite04->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    sprite05->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite06->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite07->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite08->setAnchorPoint(Vec2(0.0f, 0.0f));
    //sprite09->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    GameData::getInstance()->setCardFaceIndex(cardFaceIndex);
    
    int cardCount=BoardLayer::getInstance()->cards->count();
    int cardBackIndex=GameData::getInstance()->getCardBackIndex();
    
    for(int i=0;i<cardCount;i++){
        Card* card=(Card*)(BoardLayer::getInstance()->cards->objectAtIndex(i));
        card->setCardSprite(cardFaceIndex, cardBackIndex);        
    }
    
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
    
}

void CardFaceLayer::onBack(Ref* sender)
{
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}
