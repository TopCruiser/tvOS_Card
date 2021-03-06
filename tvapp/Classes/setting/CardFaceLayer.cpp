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

cocos2d::CCScene* CardFaceLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    CardFaceLayer* layer = CardFaceLayer::create();
    scene->addChild(layer);
    return scene;
}

bool CardFaceLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void CardFaceLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    _background = CCSprite::create();
    _background->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(_background);
    
    _title = CCSprite::create();
    addChild(_title);
    
    btnBack = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("back_nor").c_str()),
                                       CCSprite::create(getNameWithResolution("back_act").c_str()),
                                       this, menu_selector(CardFaceLayer::onBack));
    btnBack->setAnchorPoint(ccp(0.5f, 0.5f));
    btnBack->setScale(getScaleWithDevice());
    
    sprite00=CCSprite::create(getNameWithResolution("spade1_10").c_str());
    sprite01=CCSprite::create(getNameWithResolution("spade1_11").c_str());
    sprite02=CCSprite::create(getNameWithResolution("spade1_12").c_str());
    sprite03=CCSprite::create(getNameWithResolution("spade1_13").c_str());
    sprite04=CCSprite::create(getNameWithResolution("spade1_1").c_str());
    sprite05=CCSprite::create(getNameWithResolution("spade2_10").c_str());
    sprite06=CCSprite::create(getNameWithResolution("spade2_11").c_str());
    sprite07=CCSprite::create(getNameWithResolution("spade2_12").c_str());
    sprite08=CCSprite::create(getNameWithResolution("spade2_13").c_str());
    sprite09=CCSprite::create(getNameWithResolution("spade2_1").c_str());
    
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
    
    btnCard01 = CCMenuItemSprite::create(sprite00,sprite00,this, menu_selector(CardFaceLayer::onCardTap));
    btnCard02 = CCMenuItemSprite::create(sprite01,sprite01,this, menu_selector(CardFaceLayer::onCardTap));
    btnCard03 = CCMenuItemSprite::create(sprite02,sprite02, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard04 = CCMenuItemSprite::create(sprite03,sprite03,this, menu_selector(CardFaceLayer::onCardTap));
    btnCard05 = CCMenuItemSprite::create(sprite04,sprite04, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard06 = CCMenuItemSprite::create(sprite05,sprite05, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard07 = CCMenuItemSprite::create(sprite06,sprite06, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard08 = CCMenuItemSprite::create(sprite07,sprite07, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard09 = CCMenuItemSprite::create(sprite08,sprite08, this, menu_selector(CardFaceLayer::onCardTap));
    btnCard10 = CCMenuItemSprite::create(sprite09,sprite09, this, menu_selector(CardFaceLayer::onCardTap));
    
    btnCard01->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard02->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard03->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard04->setAnchorPoint(ccp(0.5f, 0.5f));
    
    btnCard05->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard06->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard07->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard08->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard09->setAnchorPoint(ccp(0.5f, 0.5f));
    btnCard10->setAnchorPoint(ccp(0.5f, 0.5f));
    
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
    
    
    _menu = CCMenu::create();
    
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
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(ccp(-winSize.width/2 + getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_port").c_str());
    _title->setAnchorPoint(ccp(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.7f);
    _title->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(460.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        CCPoint pos = CCPointZero;
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
        
        CCMenuItem* item = (CCMenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
    }
    
    _menu->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
}

void CardFaceLayer::updateLayoutWithLandscape()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(ccp(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(ccp(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        CCPoint pos = CCPointZero;
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
        
        CCMenuItem* item = (CCMenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
    }
    
    _menu->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
}

void CardFaceLayer::onCardTap(CCObject* sender)
{   //card selected
    CCMenuItem* item = (CCMenuItem*)sender;
    CCBlink *blink_ = CCBlink::create(1.0f, 7);
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
    
    sprite00->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite01->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite02->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite03->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite04->setAnchorPoint(ccp(0.0f, 0.0f));
    
    sprite05->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite06->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite07->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite08->setAnchorPoint(ccp(0.0f, 0.0f));
    sprite09->setAnchorPoint(ccp(0.0f, 0.0f));
    
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

void CardFaceLayer::onBack(CCObject* sender)
{
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}
