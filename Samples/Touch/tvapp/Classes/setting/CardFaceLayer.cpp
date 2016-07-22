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
    btnCard05 = MenuItemSprite::create(sprite04,sprite04, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard06 = MenuItemSprite::create(sprite05,sprite05, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard07 = MenuItemSprite::create(sprite06,sprite06, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard08 = MenuItemSprite::create(sprite07,sprite07, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard09 = MenuItemSprite::create(sprite08,sprite08, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard10 = MenuItemSprite::create(sprite09,sprite09, this, menu_selector(CardFaceLayer::onCardTap));
    
    btnCard01->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard02->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard03->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard04->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard05->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard06->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard07->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard08->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard09->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard10->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard01->setScale(getScaleWithDevice());
    btnCard02->setScale(getScaleWithDevice());
    btnCard03->setScale(getScaleWithDevice());
    btnCard04->setScale(getScaleWithDevice());
    
    btnCard05->setScale(getScaleWithDevice());
    btnCard06->setScale(getScaleWithDevice());
    btnCard07->setScale(getScaleWithDevice());
    btnCard08->setScale(getScaleWithDevice());
    btnCard09->setScale(getScaleWithDevice());
    btnCard10->setScale(getScaleWithDevice());
    
    
    _menu = Menu::create();
    
    _menu->addChild(btnBack);
    
    _menu->addChild(btnCard01, 1, TAG_CARD01);
    _menu->addChild(btnCard02, 1, TAG_CARD02);
    _menu->addChild(btnCard03, 1, TAG_CARD03);
    _menu->addChild(btnCard04, 1, TAG_CARD04);
    
    _menu->addChild(btnCard05, 1, TAG_CARD05);
    _menu->addChild(btnCard06, 1, TAG_CARD06);
    _menu->addChild(btnCard07, 1, TAG_CARD07);
    _menu->addChild(btnCard08, 1, TAG_CARD08);
    _menu->addChild(btnCard09, 1, TAG_CARD09);
    _menu->addChild(btnCard10, 1, TAG_CARD10);
    _menu->setVisible(false);
    
    addChild(_menu);
    
}


void CardFaceLayer::updateLayoutWithPortrait()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(Vec2(-winSize.width/2 + getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_port").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.7f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(460.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        Point pos = Vec2(0, 0);
        switch (i) {
            case TAG_CARD01:
                pos.x = getSizeWithDevice(-90);
                pos.y = getSizeWithDevice(140);
                break;
            case TAG_CARD02:
                pos.x = getSizeWithDevice(-90);
                pos.y = getSizeWithDevice(0);
                break;
            case TAG_CARD03:
                pos.x = getSizeWithDevice(-90);
                pos.y = getSizeWithDevice(-140);
                break;
            case TAG_CARD04:
                pos.x = getSizeWithDevice(-90);
                pos.y = getSizeWithDevice(-280);
                break;
            case TAG_CARD05:
                pos.x = getSizeWithDevice(-90);
                pos.y = getSizeWithDevice(-420);
                break;
            case TAG_CARD06:
                pos.x = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(140);
                break;
            case TAG_CARD07:
                pos.x = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(0);
                break;
            case TAG_CARD08:
                pos.x = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(-140);
                break;
            case TAG_CARD09:
                pos.x = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(-280);
                break;
            case TAG_CARD10:
                pos.x = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(-420);
                break;
            default:
                break;
        }
        
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
    }
    
    _menu->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
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
        Point pos = Vec2(0, 0);
        switch (i) {
            case TAG_CARD01:
                pos.x = -getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_CARD02:
                pos.x = -getSizeWithDevice(115);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_CARD03:
                pos.x = -getSizeWithDevice(0);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_CARD04:
                pos.x = getSizeWithDevice(115);
                pos.y = -getSizeWithDevice(20);
                break;
            case TAG_CARD05:
                pos.x = getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(20);
                break;
                
            case TAG_CARD06:
                pos.x = -getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(175);
                break;
            
            case TAG_CARD07:
                pos.x = -getSizeWithDevice(115);
                pos.y = -getSizeWithDevice(175);
                break;
            
            case TAG_CARD08:
                pos.x = getSizeWithDevice(0);
                pos.y = -getSizeWithDevice(175);
                break;
                
            
            case TAG_CARD09:
                pos.x = getSizeWithDevice(115);
                pos.y = -getSizeWithDevice(175);
                break;
            case TAG_CARD10:
                pos.x = getSizeWithDevice(230);
                pos.y = -getSizeWithDevice(175);
                break;
            default:
                break;
        }
        
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
    }
    
    _menu->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
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
                sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=2;
            }
            else {
                sprite00->initWithFile(getNameWithResolution("spade1_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade1_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade1_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade1_13").c_str());
                sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());

                sprite05->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade3_13").c_str());
                sprite09->initWithFile(getNameWithResolution("spade3_1").c_str());
                cardFaceIndex=1;
            }
            break;
        case 1:
            if(cardFaceIndex<5) {
                sprite00->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade3_13").c_str());
                sprite04->initWithFile(getNameWithResolution("spade3_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=0;
            }
            else {
                sprite00->initWithFile(getNameWithResolution("spade1_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade1_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade1_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade1_13").c_str());
                sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=2;
            }
            break;
        default:
            if(cardFaceIndex<5) {
                sprite00->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade3_13").c_str());
                sprite04->initWithFile(getNameWithResolution("spade3_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade2_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade2_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade2_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade2_13").c_str());
                sprite09->initWithFile(getNameWithResolution("spade2_1").c_str());
                cardFaceIndex=0;
            }
            else {
                sprite00->initWithFile(getNameWithResolution("spade1_10").c_str());
                sprite01->initWithFile(getNameWithResolution("spade1_11").c_str());
                sprite02->initWithFile(getNameWithResolution("spade1_12").c_str());
                sprite03->initWithFile(getNameWithResolution("spade1_13").c_str());
                sprite04->initWithFile(getNameWithResolution("spade1_1").c_str());
                
                sprite05->initWithFile(getNameWithResolution("spade3_10").c_str());
                sprite06->initWithFile(getNameWithResolution("spade3_11").c_str());
                sprite07->initWithFile(getNameWithResolution("spade3_12").c_str());
                sprite08->initWithFile(getNameWithResolution("spade3_13").c_str());
                sprite09->initWithFile(getNameWithResolution("spade3_1").c_str());
                cardFaceIndex=1;
            }
            break;
    }
    
    sprite00->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite01->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite02->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite03->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite04->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    sprite05->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite06->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite07->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite08->setAnchorPoint(Vec2(0.0f, 0.0f));
    sprite09->setAnchorPoint(Vec2(0.0f, 0.0f));
    
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
