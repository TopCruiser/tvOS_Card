//
//  CongratulationLayer.cpp
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "CongratulationLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "AppDelegate.h"

cocos2d::Scene* CongratulationLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    CongratulationLayer* layer = CongratulationLayer::create();
    scene->addChild(layer);
    return scene;
}

bool CongratulationLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void CongratulationLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    Sprite* background = Sprite::create(getNameWithResolution("dialog_congratulation").c_str());
    background->setScale(getScaleWithDevice());
    background->setPosition(Vec2(0.0f, 0.0f));
    addChild(background);
    
    Size size = background->getContentSize();
    setContentSize(size);
    
    MenuItem* btnFacebook = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_facebook_nor").c_str()),
                                                     Sprite::create(getNameWithResolution("btn_facebook_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onFacebook));
    
    MenuItem* btnTwitter = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_twitter_nor").c_str()),
                                                       Sprite::create(getNameWithResolution("btn_twitter_act").c_str()),
                                                       this, menu_selector(CongratulationLayer::onTwitter));
    
    MenuItem* btnChat = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_chat_nor").c_str()),
                                                     Sprite::create(getNameWithResolution("btn_chat_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onChat));
    
    MenuItem* btnMail = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_mail_nor").c_str()),
                                                     Sprite::create(getNameWithResolution("btn_mail_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onMail));
    
    MenuItem* btnGameCenter = MenuItemSprite::create(Sprite::create(getNameWithResolution("center_nor").c_str()),
                                                       Sprite::create(getNameWithResolution("center_act").c_str()),
                                                       this, menu_selector(CongratulationLayer::onGameCenter));
    
    MenuItem* btnReplay = MenuItemSprite::create(Sprite::create(getNameWithResolution("congratulation_replay_nor").c_str()),
                                                     Sprite::create(getNameWithResolution("congratulation_replay_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onReplay));
    
    MenuItem* btnDone = MenuItemSprite::create(Sprite::create(getNameWithResolution("congratulation_done_nor").c_str()),
                                                   Sprite::create(getNameWithResolution("congratulation_done_act").c_str()),
                                                   this, menu_selector(CongratulationLayer::onDone));
    
    //add dummy object to receive focus
    MenuItem* dummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_freecell_nor").c_str()),
                                             Sprite::create(getNameWithResolution("btn_freecell_act").c_str()),
                                             this, menu_selector(CongratulationLayer::onDummy));
    dummy->setScale(0.01);
    
    btnFacebook->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnTwitter->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnChat->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnMail->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnGameCenter->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    btnReplay->setAnchorPoint(Vec2(0.5f, 0.5f));
    btnDone->setAnchorPoint(Vec2(0.5f, 0.0f));
    
    btnFacebook->setScale(getScaleWithDevice());
    btnTwitter->setScale(getScaleWithDevice());
    btnChat->setScale(getScaleWithDevice());
    btnGameCenter->setScale(getScaleWithDevice());
    btnMail->setScale(getScaleWithDevice());
    
    btnReplay->setScale(getScaleWithDevice());
    btnDone->setScale(getScaleWithDevice());
    
    btnFacebook->setPosition(Vec2(getSizeWithDevice(-210.0f), getSizeWithDevice(50.0f)));
    btnTwitter->setPosition(Vec2(getSizeWithDevice(-160.0f), getSizeWithDevice(50.0f)));
    btnChat->setPosition(Vec2(getSizeWithDevice(-210.0f), getSizeWithDevice(0.0f)));
    btnMail->setPosition(Vec2(getSizeWithDevice(-160.0f), getSizeWithDevice(0.0f)));
    btnGameCenter->setPosition(Vec2(getSizeWithDevice(200.0f), getSizeWithDevice(0.0f)));
    
    btnReplay->setPosition(Vec2(getSizeWithDevice(-120.0f), -size.height/2.0f + getSizeWithDevice(45.0f)));
    btnDone->setPosition(Vec2(getSizeWithDevice(148.0f),  -size.height/2.0f + getSizeWithDevice(27.0f)));
    
    _menu = Menu::create();
    _menu->addChild(btnFacebook);
    _menu->addChild(btnTwitter);
    _menu->addChild(btnChat);
    _menu->addChild(btnMail);
    _menu->addChild(btnGameCenter);
    _menu->addChild(btnReplay);
    _menu->addChild(btnDone);
    _menu->addChild(dummy);
    
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
    
    //showScore
    //add by khj 3.9.2015
    
    int score = ((BoardLayer*)_parentLayer)->getScore();
    
    std::string temp=to_string(score);
    
    
    CCLabelTTF* _scoreLabel = CCLabelTTF::create(temp.c_str(), "tt0283m.ttf", getSizeWithDevice(30));
    _scoreLabel->setColor(Color3B(255, 255, 255));
    addChild(_scoreLabel, 0);
    
    int moveCount = ((BoardLayer*)_parentLayer)->_totalMoveCount;
    temp=to_string(moveCount);
    
    CCLabelTTF* _moveLabel = CCLabelTTF::create(temp.c_str(), "tt0283m.ttf", getSizeWithDevice(30));
    _moveLabel->setColor(Color3B(255, 255, 255));
    addChild(_moveLabel, 0);
    
    temp=((BoardLayer*)_parentLayer)->getTime();
    
    CCLabelTTF* _timeLabel = CCLabelTTF::create(temp.c_str(), "tt0283m.ttf", getSizeWithDevice(30));
    _timeLabel->setColor(Color3B(255, 255, 255));
    addChild(_timeLabel, 0);
    
    _scoreLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    _moveLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    _timeLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    _scoreLabel->setPosition(Vec2(getSizeWithDevice(55.0f), getSizeWithDevice(65.0f)));
    _moveLabel->setPosition(Vec2(getSizeWithDevice(55.0f),  getSizeWithDevice(20.0f)));
    _timeLabel->setPosition(Vec2(getSizeWithDevice(60.0f),  -getSizeWithDevice(25.0f)));
    
    
    //AppDelegate::get()->sendMessageToNative(MSG_SHOW_REWARDEDVIDEO, "Chartboost Rewarded Video", 1);
//    if(!GameData::getInstance()->isRemoveAds())
//        AppDelegate::get()->sendMessageToNative(MSG_ADCOLONY_VIDEO, "AdColony Video", 1);
//    
//    //Appirater
//    AppDelegate::get()->sendMessageToNative(MSG_APPIRATER, "Appirater", 1);comment715
    
}

void CongratulationLayer::onDummy(Ref* sender)
{
    
}

void CongratulationLayer::onFacebook(Ref* sender)
{
    //AppDelegate::get()->sendMessageToNative(MSG_SHOW_FACEBOOK, getMessage().c_str(), 1);comment715
}

void CongratulationLayer::onTwitter(Ref* sender)
{
    //AppDelegate::get()->sendMessageToNative(MSG_SHOW_TWITTER, getMessage().c_str(), 1);comment715
}

void CongratulationLayer::onChat(Ref* sender)
{
    //SMS
    //AppDelegate::get()->sendMessageToNative(MSG_SMS, getMessage().c_str(), 1);//comment715
}

void CongratulationLayer::onMail(Ref* sender)
{
    //AppDelegate::get()->sendMessageToNative(MSG_EMAIL, getMessage().c_str(), 1);comment715
}

std::string CongratulationLayer::getMessage(){
    
    std::string msg = "Check out my score ";
    
    long score = ((BoardLayer*)_parentLayer)->getScore();
    std::string temp=to_string(score);
    
    msg+=temp;
    
    msg+=" for ";
    
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
            msg+="Solitaire!";
            break;
            
        case TYPE_FREECELL:
            msg+="Freecell!";
            break;
        case TYPE_FORTY_THIEVES:
            msg+="Forty Thieves!";
            break;
            
        case TYPE_SPIDER:
            msg+="Spider Solitaire!";
            break;
    }
    
    return msg;
}

void CongratulationLayer::onGameCenter(Ref* sender)
{
//    AppDelegate* app = AppDelegate::get();
    
//    switch (GameData::getInstance()->getGameType()) {
//        case TYPE_SOLITAIRE:
//        {
//            if(GameData::getInstance()->isDrawFlag()){
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sDraw3Wins", 1);
//            }else{
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sDraw1Wins", 1);
//            }
//        }
//            break;
//            
//        case TYPE_FREECELL:
//        {
//            app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.FCTotalWins", 1);
//        }
//            break;
//            
//        case TYPE_FORTY_THIEVES:
//        {
//            app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.FTTotalWins", 1);
//        }
//            break;
//            
//        case TYPE_SPIDER:
//        {
//            if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY){
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss1suitwins", 1);
//            }
//            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL){
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss2suitwins", 1);
//            }
//            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT){
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss3suitwins", 1);
//            }
//            else{
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss4suitwins", 1);
//            }
//        }
//            break;
//    }comment715
}

void CongratulationLayer::onReplay(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    ((BoardLayer*)_parentLayer)->didCongratulationDialog(true);
}

void CongratulationLayer::onDone(Ref* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    ((BoardLayer*)_parentLayer)->didCongratulationDialog(false);
}
