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

cocos2d::CCScene* CongratulationLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    CongratulationLayer* layer = CongratulationLayer::create();
    scene->addChild(layer);
    return scene;
}

bool CongratulationLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void CongratulationLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    CCSprite* background = CCSprite::create(getNameWithResolution("dialog_congratulation").c_str());
    background->setScale(getScaleWithDevice());
    background->setPosition(ccp(0.0f, 0.0f));
    addChild(background);
    
    CCSize size = background->getContentSize();
    setContentSize(size);
    
    CCMenuItem* btnFacebook = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_facebook_nor").c_str()),
                                                     CCSprite::create(getNameWithResolution("btn_facebook_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onFacebook));
    
    CCMenuItem* btnTwitter = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_twitter_nor").c_str()),
                                                       CCSprite::create(getNameWithResolution("btn_twitter_act").c_str()),
                                                       this, menu_selector(CongratulationLayer::onTwitter));
    
    CCMenuItem* btnChat = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_chat_nor").c_str()),
                                                     CCSprite::create(getNameWithResolution("btn_chat_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onChat));
    
    CCMenuItem* btnMail = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_mail_nor").c_str()),
                                                     CCSprite::create(getNameWithResolution("btn_mail_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onMail));
    
    CCMenuItem* btnGameCenter = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("center_nor").c_str()),
                                                       CCSprite::create(getNameWithResolution("center_act").c_str()),
                                                       this, menu_selector(CongratulationLayer::onGameCenter));
    
    CCMenuItem* btnReplay = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("congratulation_replay_nor").c_str()),
                                                     CCSprite::create(getNameWithResolution("congratulation_replay_act").c_str()),
                                                     this, menu_selector(CongratulationLayer::onReplay));
    
    CCMenuItem* btnDone = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("congratulation_done_nor").c_str()),
                                                   CCSprite::create(getNameWithResolution("congratulation_done_act").c_str()),
                                                   this, menu_selector(CongratulationLayer::onDone));
    
    btnFacebook->setAnchorPoint(ccp(0.5f, 0.5f));
    btnTwitter->setAnchorPoint(ccp(0.5f, 0.5f));
    btnChat->setAnchorPoint(ccp(0.5f, 0.5f));
    btnMail->setAnchorPoint(ccp(0.5f, 0.5f));
    btnGameCenter->setAnchorPoint(ccp(0.5f, 0.5f));
    
    btnReplay->setAnchorPoint(ccp(0.5f, 0.5f));
    btnDone->setAnchorPoint(ccp(0.5f, 0.0f));
    
    btnFacebook->setScale(getScaleWithDevice());
    btnTwitter->setScale(getScaleWithDevice());
    btnChat->setScale(getScaleWithDevice());
    btnGameCenter->setScale(getScaleWithDevice());
    btnMail->setScale(getScaleWithDevice());
    
    btnReplay->setScale(getScaleWithDevice());
    btnDone->setScale(getScaleWithDevice());
    
    btnFacebook->setPosition(ccp(getSizeWithDevice(-210.0f), getSizeWithDevice(50.0f)));
    btnTwitter->setPosition(ccp(getSizeWithDevice(-160.0f), getSizeWithDevice(50.0f)));
    btnChat->setPosition(ccp(getSizeWithDevice(-210.0f), getSizeWithDevice(0.0f)));
    btnMail->setPosition(ccp(getSizeWithDevice(-160.0f), getSizeWithDevice(0.0f)));
    btnGameCenter->setPosition(ccp(getSizeWithDevice(200.0f), getSizeWithDevice(0.0f)));
    
    btnReplay->setPosition(ccp(getSizeWithDevice(-120.0f), -size.height/2.0f + getSizeWithDevice(45.0f)));
    btnDone->setPosition(ccp(getSizeWithDevice(148.0f),  -size.height/2.0f + getSizeWithDevice(27.0f)));
    
    _menu = CCMenu::create();
    _menu->addChild(btnFacebook);
    _menu->addChild(btnTwitter);
    _menu->addChild(btnChat);
    _menu->addChild(btnMail);
    _menu->addChild(btnGameCenter);
    _menu->addChild(btnReplay);
    _menu->addChild(btnDone);
    
    _menu->setPosition(ccp(0.0f, 0.0f));
    addChild(_menu);
    
    //showScore
    //add by khj 3.9.2015
    
    int score = ((BoardLayer*)_parentLayer)->getScore();
    
    std::string temp=to_string(score);
    
    
    CCLabelTTF* _scoreLabel = CCLabelTTF::create(temp.c_str(), "tt0283m.ttf", getSizeWithDevice(30));
    _scoreLabel->setColor(ccc3(255, 255, 255));
    addChild(_scoreLabel, 0);
    
    int moveCount = ((BoardLayer*)_parentLayer)->_totalMoveCount;
    temp=to_string(moveCount);
    
    CCLabelTTF* _moveLabel = CCLabelTTF::create(temp.c_str(), "tt0283m.ttf", getSizeWithDevice(30));
    _moveLabel->setColor(ccc3(255, 255, 255));
    addChild(_moveLabel, 0);
    
    temp=((BoardLayer*)_parentLayer)->getTime();
    
    CCLabelTTF* _timeLabel = CCLabelTTF::create(temp.c_str(), "tt0283m.ttf", getSizeWithDevice(30));
    _timeLabel->setColor(ccc3(255, 255, 255));
    addChild(_timeLabel, 0);
    
    _scoreLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    _moveLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    _timeLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    
    _scoreLabel->setPosition(ccp(getSizeWithDevice(55.0f), getSizeWithDevice(65.0f)));
    _moveLabel->setPosition(ccp(getSizeWithDevice(55.0f),  getSizeWithDevice(20.0f)));
    _timeLabel->setPosition(ccp(getSizeWithDevice(60.0f),  -getSizeWithDevice(25.0f)));
    
    
    //AppDelegate::get()->sendMessageToNative(MSG_SHOW_REWARDEDVIDEO, "Chartboost Rewarded Video", 1);
//    if(!GameData::getInstance()->isRemoveAds())
//        AppDelegate::get()->sendMessageToNative(MSG_ADCOLONY_VIDEO, "AdColony Video", 1);
//    
//    //Appirater
//    AppDelegate::get()->sendMessageToNative(MSG_APPIRATER, "Appirater", 1);comment715
    
}


void CongratulationLayer::onFacebook(CCObject* sender)
{
    //AppDelegate::get()->sendMessageToNative(MSG_SHOW_FACEBOOK, getMessage().c_str(), 1);comment715
}

void CongratulationLayer::onTwitter(CCObject* sender)
{
    //AppDelegate::get()->sendMessageToNative(MSG_SHOW_TWITTER, getMessage().c_str(), 1);comment715
}

void CongratulationLayer::onChat(CCObject* sender)
{
    //SMS
    //AppDelegate::get()->sendMessageToNative(MSG_SMS, getMessage().c_str(), 1);//comment715
}

void CongratulationLayer::onMail(CCObject* sender)
{
    //AppDelegate::get()->sendMessageToNative(MSG_EMAIL, getMessage().c_str(), 1);comment715
}

std::string CongratulationLayer::getMessage(){
    
    std::string msg = "Check out my score ";
    
    int score = ((BoardLayer*)_parentLayer)->getScore();
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

void CongratulationLayer::onGameCenter(CCObject* sender)
{
    AppDelegate* app = AppDelegate::get();
    
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

void CongratulationLayer::onReplay(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    ((BoardLayer*)_parentLayer)->didCongratulationDialog(true);
}

void CongratulationLayer::onDone(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    ((BoardLayer*)_parentLayer)->didCongratulationDialog(false);
}
