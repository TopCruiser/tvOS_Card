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
    btnCard11->setScale(getScaleWithDevice());
    btnCard12->setScale(getScaleWithDevice());
    
    btnCard13->setScale(getScaleWithDevice());
    btnCard14->setScale(getScaleWithDevice());
    btnCard15->setScale(getScaleWithDevice());
    btnCard16->setScale(getScaleWithDevice());
    
    btnCard17->setScale(getScaleWithDevice());
    btnCard18->setScale(getScaleWithDevice());
    btnCard19->setScale(getScaleWithDevice());
    btnCard20->setScale(getScaleWithDevice());
    
    btnCard21->setScale(getScaleWithDevice());
    btnCard22->setScale(getScaleWithDevice());
    btnCard23->setScale(getScaleWithDevice());
    btnCard24->setScale(getScaleWithDevice());
    
    btnCard25->setScale(getScaleWithDevice());
    btnCard26->setScale(getScaleWithDevice());
    btnCard27->setScale(getScaleWithDevice());
    btnCard28->setScale(getScaleWithDevice());
    
    btnCard29->setScale(getScaleWithDevice());
    btnCard30->setScale(getScaleWithDevice());
    btnCard31->setScale(getScaleWithDevice());
    btnCard32->setScale(getScaleWithDevice());
    
    _menu = Menu::create();
    //_menu->addChild(btnBack);
    
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
    
    _menu->addChild(_selectedCardBack, 3, 10000);
    _menu->setVisible(false);
    //addChild(_menu);
    
    Size winSize = Director::getInstance()->getWinSize();
    /////size of the viewable part of scrollview
    //if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)
        _ScrollView = ScrollView::create(Size(winSize.width, winSize.height/1.75f), _menu);
//    else
//        _ScrollView = ScrollView::create(Size(winSize.width, winSize.height/1.45f), _menu);comment715
    _ScrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    _ScrollView->setAnchorPoint(Vec2(0, 0));
    _ScrollView->setPosition(Vec2(0, 0));
    addChild(_ScrollView);
    
//    if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)
//    {
        /////size of the viewable part of scrollview
        _ScrollView->setViewSize(Size(winSize.width, winSize.height/1.75f));
        ////size of the whole content (the big rectangle that we scroll in)
        _ScrollView->setContentSize(Size(winSize.width/2,winSize.height*1.5));
        //position it so that the top most is visible initially,
        _ScrollView->setContentOffset(Vec2(winSize.width/2,-winSize.height*0.95));
    //}
//    else//portrait
//    {
//        /////size of the viewable part of scrollview
//        _ScrollView->setViewSize(Size(winSize.width, winSize.height/1.45f));
//        ////size of the whole content (the big rectangle that we scroll in)
//        _ScrollView->setContentSize(Size(winSize.width/2,winSize.height*2.1));
//        //position it so that the top most is visible initially,
//        //_ScrollView->setContentOffset(Vec2(winSize.width/2,-winSize.height*2));
//        _ScrollView->setContentOffset(Vec2(winSize.width/2,-winSize.height*1.4));
//    }comment715
}

void CardBackLayer::updateLayoutWithPortrait()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_port").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
//    btnBack->setPosition(Vec2(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    btnBack->setPosition(Vec2(getSizeWithDevice(60), winSize.height-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_port").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.7f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(460.0f)));
    
    int InitY = winSize.height*2;
    int DeltaY = 150;
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        CCPoint pos = CCPointZero;
        switch (i) {
            case TAG_CARD01:
                pos.x = getSizeWithDevice(-180);
//                pos.y = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(InitY);
                break;
            case TAG_CARD02:
                pos.x = getSizeWithDevice(0);
//                pos.y = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(InitY);
                break;
            case TAG_CARD03:
                pos.x = getSizeWithDevice(180);
//                pos.y = getSizeWithDevice(90);
                pos.y = getSizeWithDevice(InitY);
                break;
                
            case TAG_CARD04:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(60);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
            case TAG_CARD05:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(60);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
            case TAG_CARD06:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(60);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
                
            case TAG_CARD07:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(210);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
            case TAG_CARD08:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(210);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
            case TAG_CARD09:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(210);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
                
            case TAG_CARD10:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(360);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
            case TAG_CARD11:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(360);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
            case TAG_CARD12:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(360);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
                
            case TAG_CARD13:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(510);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
            case TAG_CARD14:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(510);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
            case TAG_CARD15:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(510);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
                
            case TAG_CARD16:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(660);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 5));
                break;
            case TAG_CARD17:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(660);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 5));
                break;
            case TAG_CARD18:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(660);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 5));
                break;
                
            case TAG_CARD19:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(810);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 6));
                break;
            case TAG_CARD20:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(810);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 6));
                break;
            case TAG_CARD21:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(810);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 6));
                break;
                
            case TAG_CARD22:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(960);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 7));
                break;
            case TAG_CARD23:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(960);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 7));
                break;
            case TAG_CARD24:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(960);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 7));
                break;
                
            case TAG_CARD25:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(1110);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 8));
                break;
            case TAG_CARD26:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(1110);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 8));
                break;
            case TAG_CARD27:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(1110);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 8));
                break;
                
            case TAG_CARD28:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(1260);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 9));
                break;
            case TAG_CARD29:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(1260);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 9));
                break;
            case TAG_CARD30:
                pos.x = getSizeWithDevice(180);
//                pos.y = -getSizeWithDevice(1260);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 9));
                break;
                
            case TAG_CARD31:
                pos.x = getSizeWithDevice(-180);
//                pos.y = -getSizeWithDevice(1410);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 10));
                break;
            case TAG_CARD32:
                pos.x = getSizeWithDevice(0);
//                pos.y = -getSizeWithDevice(1410);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 10));
                break;
            default:
                break;
        }
        
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
        
//        if(i==GameData::getInstance()->getCardBackIndex())
//            _selectedCardBack->setPosition(Vec2(winSize.width/2.0f+pos.x, winSize.height/2.0f+pos.y));
        if(i==GameData::getInstance()->getCardBackIndex())
            _selectedCardBack->setPosition(pos);

    }
    
//    _menu->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
    
    /////size of the viewable part of scrollview
    _ScrollView->setViewSize(Size(winSize.width, winSize.height/1.45f));
    ////size of the whole content (the big rectangle that we scroll in)
    _ScrollView->setContentSize(Size(winSize.width/2,winSize.height*2.1));
    //position it so that the top most is visible initially,
    //_ScrollView->setContentOffset(Vec2(winSize.width/2,-winSize.height*2));
    _ScrollView->setContentOffset(Vec2(winSize.width/2,-winSize.height*1.4));
}

void CardBackLayer::updateLayoutWithLandscape()
{
    CCSize winSize = Director::getInstance()->getWinSize();
    
    _background->initWithFile(getNameWithDevice("menubg_land").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    //btnBack->setPosition(Vec2(-winSize.width/2+getSizeWithDevice(60), winSize.height/2.0f-getSizeWithDevice(60)));
    btnBack->setPosition(Vec2(getSizeWithDevice(60), winSize.height-getSizeWithDevice(60)));
    
    _title->initWithFile(getNameWithResolution("logo_land").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 1.0f));
    _title->setScale(getScaleWithDevice() * 0.5f);
    _title->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f + getSizeWithDevice(300.0f)));

    int InitY = winSize.height*1.4;
    int DeltaY = 155;
    
    for(int i = 0; i < TAG_MAX; i++)
    {
        CCPoint pos = CCPointZero;
        switch (i) {
                ///////////////////////by amr
            case TAG_CARD01:
                pos.x = -getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(20);
                pos.y = getSizeWithDevice(InitY);
                break;
            case TAG_CARD02:
                pos.x = -getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(20);
                pos.y = getSizeWithDevice(InitY);
                break;
            case TAG_CARD03:
                pos.x = getSizeWithDevice(-78);
//                pos.y = -getSizeWithDevice(20);
                pos.y = getSizeWithDevice(InitY);
                break;
            case TAG_CARD04:
                pos.x = getSizeWithDevice(78);
//                pos.y = -getSizeWithDevice(20);
                pos.y = getSizeWithDevice(InitY);
                break;
            case TAG_CARD05:
                pos.x = getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(20);
                pos.y = getSizeWithDevice(InitY);
                break;
            case TAG_CARD06:
                pos.x = getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(20);
                pos.y = getSizeWithDevice(InitY);
                break;
                
                
             
            case TAG_CARD07:
                pos.x = -getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(175);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
            case TAG_CARD08:
                pos.x = -getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(175);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
            case TAG_CARD09:
                pos.x = getSizeWithDevice(-78);
//                pos.y = -getSizeWithDevice(175);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
            case TAG_CARD10:
                pos.x = getSizeWithDevice(78);
//                pos.y = -getSizeWithDevice(175);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
            case TAG_CARD11:
                pos.x = getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(175);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
            case TAG_CARD12:
                pos.x = getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(175);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 1));
                break;
                
                
            case TAG_CARD13:
                pos.x = -getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(330);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
            case TAG_CARD14:
                pos.x = -getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(330);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
            case TAG_CARD15:
                pos.x = getSizeWithDevice(-78);
//                pos.y = -getSizeWithDevice(330);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
            case TAG_CARD16:
                pos.x = getSizeWithDevice(78);
//                pos.y = -getSizeWithDevice(330);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
            case TAG_CARD17:
                pos.x = getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(330);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
            case TAG_CARD18:
                pos.x = getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(330);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 2));
                break;
                
                
            case TAG_CARD19:
                pos.x = -getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(485);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
            case TAG_CARD20:
                pos.x = -getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(485);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
            case TAG_CARD21:
                pos.x = getSizeWithDevice(-78);
//                pos.y = -getSizeWithDevice(485);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
            case TAG_CARD22:
                pos.x = getSizeWithDevice(78);
//                pos.y = -getSizeWithDevice(485);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
            case TAG_CARD23:
                pos.x = getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(485);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
            case TAG_CARD24:
                pos.x = getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(485);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 3));
                break;
                
            case TAG_CARD25:
                pos.x = -getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(640);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
            case TAG_CARD26:
                pos.x = -getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(640);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
            case TAG_CARD27:
                pos.x = getSizeWithDevice(-78);
//                pos.y = -getSizeWithDevice(640);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
            case TAG_CARD28:
                pos.x = getSizeWithDevice(78);
//                pos.y = -getSizeWithDevice(640);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
            case TAG_CARD29:
                pos.x = getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(640);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
            case TAG_CARD30:
                pos.x = getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(640);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 4));
                break;
                
            case TAG_CARD31:
                pos.x = -getSizeWithDevice(382);
//                pos.y = -getSizeWithDevice(795);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 5));
                break;
            case TAG_CARD32:
                pos.x = -getSizeWithDevice(230);
//                pos.y = -getSizeWithDevice(795);
                pos.y = getSizeWithDevice(InitY - (DeltaY * 5));
                break;
            default:
                break;
                
                ///////////////////////by amr
        }
        
        MenuItem* item = (MenuItem*)_menu->getChildByTag(i);
        item->setPosition(pos);
        
//        if(i==GameData::getInstance()->getCardBackIndex())
//            _selectedCardBack->setPosition(Vec2(winSize.width/2.0f+pos.x, winSize.height/2.0f+pos.y));
        if(i==GameData::getInstance()->getCardBackIndex())
            _selectedCardBack->setPosition(pos);
    }
    
//    _menu->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _menu->setVisible(true);
    
    /////size of the viewable part of scrollview
    _ScrollView->setViewSize(Size(winSize.width, winSize.height/1.75f));
    ////size of the whole content (the big rectangle that we scroll in)
    _ScrollView->setContentSize(Size(winSize.width/2,winSize.height*1.5));
    //position it so that the top most is visible initially,
    _ScrollView->setContentOffset(Vec2(winSize.width/2,-winSize.height*0.95));
}

void CardBackLayer::onCardTap(CCObject* sender)
{   //card selected
    MenuItem* item = (MenuItem*)sender;
    //CCBlink *blink_ = CCBlink::create(1.0f, 7);
    //item->runAction(blink_);
    
//    CCSize winSize = Director::getInstance()->getWinSize();
//    _selectedCardBack->setPosition(Vec2(winSize.width/2.0f+item->getPositionX(), winSize.height/2.0f+item->getPositionY()));
    //_selectedCardBack->setPosition(Vec2(item->getPositionX(), item->getPositionY()));
    _selectedCardBack->setPosition(item->getPosition());
    
    int cardBackIndex=item->getTag();
    GameData::getInstance()->setCardBackIndex(cardBackIndex);
    
    int cardCount=BoardLayer::getInstance()->cards->count();
    int cardFaceIndex=GameData::getInstance()->getCardFaceIndex();

    for(int i=0;i<cardCount;i++){
        Card* card=(Card*)(BoardLayer::getInstance()->cards->objectAtIndex(i));
        card->setCardSprite(cardFaceIndex, cardBackIndex);
    }
    
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

void CardBackLayer::onBack(CCObject* sender)
{
    setVisible(false);
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}
