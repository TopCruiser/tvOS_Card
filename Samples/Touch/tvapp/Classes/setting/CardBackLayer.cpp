//
//  CardBackLayer.cpp
//  cardgame
//
//  Created by lion on 3/9/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "CardBackLayer.h"

#include "GameData.h"
#include "GameLayer.h"

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
    TAG_CARD11,
    TAG_CARD12,
    TAG_CARD13,
    TAG_CARD14,
    TAG_CARD15,
    TAG_CARD16,
    TAG_CARD17,
    TAG_CARD18,
    TAG_CARD19,
    TAG_CARD20,
    TAG_CARD21,
    TAG_CARD22,
    TAG_CARD23,
    TAG_CARD24,
    TAG_CARD25,
    TAG_CARD26,
    TAG_CARD27,
    TAG_CARD28,
    TAG_CARD29,
    TAG_CARD30,
    TAG_CARD31,
    TAG_CARD32,
    TAG_MAX
};

cocos2d::Scene* CardBackLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    CardBackLayer* layer = CardBackLayer::create();
    scene->addChild(layer);
    return scene;
}

bool CardBackLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void CardBackLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    _background = Sprite::create();
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));    
    addChild(_background);
    
    btnBack = MenuItemSprite::create(Sprite::create(getNameWithResolution("back_nor").c_str()),
                                       Sprite::create(getNameWithResolution("back_act").c_str()),
                                       this, menu_selector(CardBackLayer::onBack));
    btnBack->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnBack->setScale(getScaleWithDevice());
    //addChild(btnBack);
    
    Menu* _btnmenu = Menu::create();
    _btnmenu->addChild(btnBack);
    _btnmenu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_btnmenu);
    
    _title = Sprite::create();
    addChild(_title);
    
    _selectedCardBack = MenuItemSprite::create(Sprite::create(getNameWithResolution("selected_cardback").c_str()),
                                               Sprite::create(getNameWithResolution("selected_cardback").c_str()), NULL);
    _selectedCardBack->setAnchorPoint(Vec2(0.5f, 0.5f));
    _selectedCardBack->setScale(getScaleWithDevice());
    
    btnCard01 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card01").c_str()),
                                                        Sprite::create(getNameWithResolution("card01").c_str()),
                                                        this, menu_selector(CardBackLayer::onCardTap));
    btnCard02 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card02").c_str()),
                                                    Sprite::create(getNameWithResolution("card02").c_str()),
                                                    this, menu_selector(CardBackLayer::onCardTap));
    btnCard03 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card03").c_str()),
                                                       Sprite::create(getNameWithResolution("card03").c_str()),
                                                       this, menu_selector(CardBackLayer::onCardTap));
    btnCard04 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card04").c_str()),
                                                     Sprite::create(getNameWithResolution("card04").c_str()),
                                                     this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard05 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card05").c_str()),
                                         Sprite::create(getNameWithResolution("card05").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard06 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card06").c_str()),
                                         Sprite::create(getNameWithResolution("card06").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard07 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card07").c_str()),
                                         Sprite::create(getNameWithResolution("card07").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard08 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card08").c_str()),
                                         Sprite::create(getNameWithResolution("card08").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard09 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card09").c_str()),
                                         Sprite::create(getNameWithResolution("card09").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard10 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card10").c_str()),
                                         Sprite::create(getNameWithResolution("card10").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard11 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card11").c_str()),
                                         Sprite::create(getNameWithResolution("card11").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard12 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card12").c_str()),
                                         Sprite::create(getNameWithResolution("card12").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    
    btnCard13 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card13").c_str()),
                                         Sprite::create(getNameWithResolution("card13").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard14 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card14").c_str()),
                                         Sprite::create(getNameWithResolution("card14").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard15 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card15").c_str()),
                                         Sprite::create(getNameWithResolution("card15").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard16 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card16").c_str()),
                                         Sprite::create(getNameWithResolution("card16").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard17 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card17").c_str()),
                                         Sprite::create(getNameWithResolution("card17").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard18 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card18").c_str()),
                                         Sprite::create(getNameWithResolution("card18").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard19 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card19").c_str()),
                                         Sprite::create(getNameWithResolution("card19").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard20 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card20").c_str()),
                                         Sprite::create(getNameWithResolution("card20").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard21 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card21").c_str()),
                                         Sprite::create(getNameWithResolution("card21").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard22 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card22").c_str()),
                                         Sprite::create(getNameWithResolution("card22").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard23 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card23").c_str()),
                                         Sprite::create(getNameWithResolution("card23").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard24 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card24").c_str()),
                                         Sprite::create(getNameWithResolution("card24").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard25 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card25").c_str()),
                                         Sprite::create(getNameWithResolution("card25").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard26 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card26").c_str()),
                                         Sprite::create(getNameWithResolution("card26").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard27 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card27").c_str()),
                                         Sprite::create(getNameWithResolution("card27").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard28 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card28").c_str()),
                                         Sprite::create(getNameWithResolution("card28").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard29 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card29").c_str()),
                                         Sprite::create(getNameWithResolution("card29").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard30 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card30").c_str()),
                                         Sprite::create(getNameWithResolution("card30").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
    btnCard31 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card31").c_str()),
                                         Sprite::create(getNameWithResolution("card31").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    btnCard32 = MenuItemSprite::create(Sprite::create(getNameWithResolution("card32").c_str()),
                                         Sprite::create(getNameWithResolution("card32").c_str()),
                                         this, menu_selector(CardBackLayer::onCardTap));
    
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
    btnCard11->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard12->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard13->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard14->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard15->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard16->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard17->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard18->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard19->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard20->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard21->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard22->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard23->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard24->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard25->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard26->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard27->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard28->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnCard29->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard30->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard31->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnCard32->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    
    
    btnCard01->setScale(0.7);
    btnCard02->setScale(0.7);
    btnCard03->setScale(0.7);
    btnCard04->setScale(0.7);
    
    btnCard05->setScale(0.7);
    btnCard06->setScale(0.7);
    btnCard07->setScale(0.7);
    btnCard08->setScale(0.7);
    
    btnCard09->setScale(0.7);
    btnCard10->setScale(0.7);
    btnCard11->setScale(0.7);
    btnCard12->setScale(0.7);
    
    btnCard13->setScale(0.7);
    btnCard14->setScale(0.7);
    btnCard15->setScale(0.7);
    btnCard16->setScale(0.7);
    
    btnCard17->setScale(0.7);
    btnCard18->setScale(0.7);
    btnCard19->setScale(0.7);
    btnCard20->setScale(0.7);
    
    btnCard21->setScale(0.7);
    btnCard22->setScale(0.7);
    btnCard23->setScale(0.7);
    btnCard24->setScale(0.7);
    
    btnCard25->setScale(0.7);
    btnCard26->setScale(0.7);
    btnCard27->setScale(0.7);
    btnCard28->setScale(0.7);
    
    btnCard29->setScale(0.7);
    btnCard30->setScale(0.7);
    btnCard31->setScale(0.7);
    btnCard32->setScale(0.7);
    
    _menu = Menu::create();
    //add dummy object to receive focus
    MenuItem* dummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_freecell_nor").c_str()),
                                             Sprite::create(getNameWithResolution("btn_freecell_act").c_str()),
                                             this, menu_selector(CardBackLayer::onDummy));
    //dummy->setScale(0.001);
    
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
    _menu->addChild(btnCard11, 1, TAG_CARD11);
    _menu->addChild(btnCard12, 1, TAG_CARD12);
    
    _menu->addChild(btnCard13, 1, TAG_CARD13);
    _menu->addChild(btnCard14, 1, TAG_CARD14);
    _menu->addChild(btnCard15, 1, TAG_CARD15);
    _menu->addChild(btnCard16, 1, TAG_CARD16);

    _menu->addChild(btnCard17, 1, TAG_CARD17);
    _menu->addChild(btnCard18, 1, TAG_CARD18);
    _menu->addChild(btnCard19, 1, TAG_CARD19);
    _menu->addChild(btnCard20, 1, TAG_CARD20);
    
    _menu->addChild(btnCard21, 1, TAG_CARD21);
    _menu->addChild(btnCard22, 1, TAG_CARD22);
    _menu->addChild(btnCard23, 1, TAG_CARD23);
    _menu->addChild(btnCard24, 1, TAG_CARD24);

    _menu->addChild(btnCard25, 1, TAG_CARD25);
    _menu->addChild(btnCard26, 1, TAG_CARD26);
    _menu->addChild(btnCard27, 1, TAG_CARD27);
    _menu->addChild(btnCard28, 1, TAG_CARD28);
    
    _menu->addChild(btnCard29, 1, TAG_CARD29);
    _menu->addChild(btnCard30, 1, TAG_CARD30);
    _menu->addChild(btnCard31, 1, TAG_CARD31);
    _menu->addChild(btnCard32, 1, TAG_CARD32);
    
    //_menu->addChild(dummy);
    
    _menu->addChild(_selectedCardBack, 3, 10000);
    _menu->setVisible(false);
    _menu->setPosition(Vec2(0, 0));
    addChild(_menu);
    
    if(arrowSprite) removeChild(arrowSprite);
    
    arrowSprite = MenuItemSprite::create(Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                         this, menu_selector(BoardLayer::onDummy));
    arrowSprite->setScale(0.5);
    arrowSprite->setAnchorPoint(Vec2(0.5, 1));
    arrowSprite->setPosition(Vec2(960, 540));
    addChild(arrowSprite, 1000);
    
    lastMovedPoint = Vec2(960, 540);
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
}

void CardBackLayer::onDummy(cocos2d::Ref *sender)
{
    
}

void CardBackLayer::updateLayoutWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    btnBack->setPosition(Vec2(getSizeWithDevice(60), winSize.height-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));

    int InitY = 570;
    int DeltaY = 180;
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        Point pos = Vec2(960, 540);
        switch (i) {
                ///////////////////////by amr
            case TAG_CARD01:
                pos.x = (160);
                pos.y = (InitY);
                break;
            case TAG_CARD02:
                pos.x = (320);
                pos.y = (InitY);
                break;
            case TAG_CARD03:
                pos.x = (480);
                pos.y = (InitY);
                break;
            case TAG_CARD04:
                pos.x = (640);
                pos.y = (InitY);
                break;
            case TAG_CARD05:
                pos.x = (800);
                pos.y = (InitY);
                break;
            case TAG_CARD06:
                pos.x = (1760);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD07:
                pos.x = (1120);
                pos.y = (InitY);
                break;
            case TAG_CARD08:
                pos.x = (1280);
                pos.y = (InitY);
                break;
            case TAG_CARD09:
                pos.x = (1440);
                pos.y = (InitY);
                break;
            case TAG_CARD10:
                pos.x = (1600);
                pos.y = (InitY);
                break;
            case TAG_CARD11:
                pos.x = (1760);
                pos.y = (InitY);
                break;
                //second row
            case TAG_CARD12:
                pos.x = (160);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD13:
                pos.x = (320);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD14:
                pos.x = (480);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD15:
                pos.x = (640);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD16:
                pos.x = (800);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD17:
                pos.x = (960);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD18:
                pos.x = (1120);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD19:
                pos.x = (1280);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD20:
                pos.x = (1440);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD21:
                pos.x = (1600);
                pos.y = (InitY - (DeltaY * 1));
                break;
            case TAG_CARD22:
                pos.x = (1760);
                pos.y = (InitY - (DeltaY * 1));
                break;
                //third row
            case TAG_CARD23:
                pos.x = (160);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD24:
                pos.x = (320);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD25:
                pos.x = (480);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD26:
                pos.x = (640);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD27:
                pos.x = (800);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD28:
                pos.x = (960);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD29:
                pos.x = (1120);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD30:
                pos.x = (1280);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD31:
                pos.x = (1440);
                pos.y = (InitY - (DeltaY * 2));
                break;
            case TAG_CARD32:
                pos.x = (1600);
                pos.y = (InitY - (DeltaY * 2));
                break;
            default:
                break;
                
                ///////////////////////by amr
        }
        
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
        
        if(i==GameData::getInstance()->getCardBackIndex())
            _selectedCardBack->setPosition(pos);
    }
    
    _menu->setVisible(true);
    
//    _ScrollView->setViewSize(Size(winSize.width, winSize.height/2.0));
//    _ScrollView->setContentSize(Size(winSize.width/2,winSize.height*3.0));
//    _ScrollView->setContentOffset(Vec2(winSize.width/2,-winSize.height*2.0));
}

void CardBackLayer::onCardTap(Ref* sender)
{   //card selected
    MenuItem* item = (MenuItem*)sender;

    _selectedCardBack->setPosition(item->getPosition());
    
    int cardBackIndex=item->getTag();
    GameData::getInstance()->setCardBackIndex(cardBackIndex);
    
    long cardCount=BoardLayer::getInstance()->cards->count();
    int cardFaceIndex=GameData::getInstance()->getCardFaceIndex();

    for(int i=0;i<cardCount;i++){
        Card* card=(Card*)(BoardLayer::getInstance()->cards->getObjectAtIndex(i));
        card->setCardSprite(cardFaceIndex, cardBackIndex);
    }
    
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

void CardBackLayer::onBack(Ref* sender)
{
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

bool CardBackLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(!this->isVisible()) return false;
    
    log("lastMovedPoint: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
    
    prevPoint = touch->getLocation();
    
    return true;
}

void CardBackLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
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

void CardBackLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("touch end: %f, %f", lastMovedPoint.x, lastMovedPoint.y);
}

void CardBackLayer::pressBegan()
{
    CCLOG("Taskbarlayer - press began : (%f, %f)", lastMovedPoint.x, lastMovedPoint.y);
    Vec2 touchPoint = convertToNodeSpace(lastMovedPoint);
    
    if(btnCard01->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard01->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard02->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard02->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard03->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard03->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard04->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard04->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard05->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard05->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard06->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard06->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard07->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard07->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard08->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard08->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard09->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard09->runAction(Sequence::create(ScaleTo::create(0.01, 0.7), ScaleTo::create(0.01, 1.0), func, NULL));
    }
    if(btnCard10->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard10->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard11->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard11->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    
    if(btnCard12->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard12->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard13->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard13->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard14->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard14->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard15->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard15->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard16->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard16->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard17->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard17->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard18->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard18->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard19->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard19->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard20->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard20->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard21->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard21->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard22->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard22->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard23->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard23->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard24->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard24->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard25->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard25->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard26->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard26->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard27->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard27->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard28->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard28->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard29->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard29->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard30->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard30->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard31->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard31->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
    if(btnCard32->getBoundingBox().containsPoint(touchPoint))
    {
        CallFuncN *func = CallFuncN::create(CC_CALLBACK_1(CardBackLayer::onCardTap,this));
        btnCard32->runAction(Sequence::create(ScaleTo::create(0.1, 0.7), func, NULL));
    }
}
