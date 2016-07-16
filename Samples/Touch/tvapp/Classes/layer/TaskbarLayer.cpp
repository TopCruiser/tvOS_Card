//
//  TaskbarLayer.cpp
//  cardgame
//
//  Created by Pink on 2/12/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "TaskbarLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "MenuLayer.h"
#include "BoardLayer.h"
#include "AppDelegate.h"

enum EXIT_GAME {
    GAME_MENU = 0,
    GAME_PLAY,
    GAME_CENTER
};

cocos2d::CCScene* TaskbarLayer::scene()
{
    CCScene* scene = cocos2d::CCScene::create();
    TaskbarLayer* layer = TaskbarLayer::create();
    scene->addChild(layer);
    return scene;
}

bool TaskbarLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    return true;
}

void TaskbarLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    
    _background = CCSprite::create(getNameWithDevice("bg_taskbar").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setAnchorPoint(ccp(0.5f, 0.0f));
    _background->setPosition(ccp(0.0f, 0.0f));
    addChild(_background);
    
    CCSize size = _background->getContentSize();
    setContentSize(size);
    
    _settingItem = createItem(getNameWithResolution("setting_nor").c_str(), getNameWithResolution("setting_act").c_str(),
                              "Setting", getSizeWithDevice(64.0f), getSizeWithDevice(64.0f),
                              this, menu_selector(TaskbarLayer::onSetting));
    _centerItem = createItem(getNameWithResolution("center_nor").c_str(), getNameWithResolution("center_act").c_str(),
                             "Center", getSizeWithDevice(64.0f), getSizeWithDevice(64.0f),
                             this, menu_selector(TaskbarLayer::onCenter));
    
    if(!GameData::getInstance()->isRemoveAds())
        _storeItem = createItem(getNameWithResolution("store_nor").c_str(), getNameWithResolution("store_act").c_str(),
                            "Remove Ads", getSizeWithDevice(64.0f), getSizeWithDevice(64.0f),
                            this, menu_selector(TaskbarLayer::onStore));
    
    _menuItem = createItem(getNameWithResolution("menu_nor").c_str(), getNameWithResolution("menu_act").c_str(),
                           "Menu", getSizeWithDevice(64.0f), getSizeWithDevice(64.0f),
                           this, menu_selector(TaskbarLayer::onMenu));
    _playItem = createItem(getNameWithResolution("play_nor").c_str(), getNameWithResolution("play_act").c_str(),
                           "Play", getSizeWithDevice(64.0f), getSizeWithDevice(64.0f),
                           this, menu_selector(TaskbarLayer::onNewGame));
    
    _hintItem= createItem(getNameWithResolution("hint_nor").c_str(), getNameWithResolution("hint_act").c_str(),
                          "Hint", getSizeWithDevice(64.0f), getSizeWithDevice(64.0f),
                          this, menu_selector(TaskbarLayer::onHint));
    
    _undoItem = createItem(getNameWithResolution("back_nor").c_str(), getNameWithResolution("back_act").c_str(),
                           "Undo", getSizeWithDevice(64.0f), getSizeWithDevice(64.0f),
                           this, menu_selector(TaskbarLayer::onUndo));
    
    _menu = CCMenu::create();
    _menu->setAnchorPoint(ccp(0.0f, 0.0f));
    _menu->setPosition(ccp(0.0f, 0.0f));
    
    _menu->addChild(_settingItem);
    _menu->addChild(_centerItem);
    
    if(!GameData::getInstance()->isRemoveAds()) _menu->addChild(_storeItem);
    
    _menu->addChild(_menuItem);
    _menu->addChild(_playItem);
    _menu->addChild(_hintItem);
    _menu->addChild(_undoItem);
    
    addChild(_menu);
}

void TaskbarLayer::updateLayoutWithPortrait()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize size = getContentSize();
    
    _settingItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(50.0f), size.height/2.0f));
    _centerItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(130.0f), size.height/2.0f));
    //_storeItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(210.0f), size.height/2.0f));
    
    if(!GameData::getInstance()->isRemoveAds())
        _storeItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(230.0f), size.height/2.0f));
    
    _undoItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(50.0f), size.height/2.0f));
    _hintItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(130.0f), size.height/2.0f));
    _playItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(210.0f), size.height/2.0f));
    _menuItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(290.0f), size.height/2.0f));
    
    if(_newGameLayer != NULL)
    {
        _newGameLayer->setPosition(ccp(0.0f, winSize.height/2.0f));
        _newGameLayer->setVisible(true);        
    }
    
    if(_exitLayer != NULL)
    {
        _exitLayer->setPosition(ccp(0.0f, winSize.height/2.0f));
    }
    
}

void TaskbarLayer::updateLayoutWithLandscape()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize size = getContentSize();
    
    _settingItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(40.0f), size.height/2.0f));
    _centerItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(120.0f), size.height/2.0f));
    //_storeItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(200.0f), size.height/2.0f));
    
    if(!GameData::getInstance()->isRemoveAds())
        _storeItem->setPosition(ccp(-winSize.width/2.0f + getSizeWithDevice(220.0f), size.height/2.0f));
    
    _undoItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(40.0f), size.height/2.0f));
    _hintItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(120.0f), size.height/2.0f));
    _playItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(200.0f), size.height/2.0f));
    _menuItem->setPosition(ccp(winSize.width/2.0f - getSizeWithDevice(280.0f), size.height/2.0f));
    
    if(_newGameLayer != NULL)
    {
        _newGameLayer->setPosition(ccp(0.0f, winSize.height/2.0f));
        _newGameLayer->setVisible(true);
    }
    
    if(_exitLayer != NULL)
    {
        _exitLayer->setPosition(ccp(0.0f, winSize.height/2.0f));
    }
    
}

CCMenuItem* TaskbarLayer::createItem(const char* szNormalSpritePath, const char* szActiveSpritePath, const char* szTitle,
                                    float width, float height, CCObject* target, SEL_MenuHandler selector)
{
    CCDrawNode* drawNodeNormal = CCDrawNode::create();
    drawNodeNormal->setContentSize(CCSizeMake(width, height));
   
    CCDrawNode* drawNodeActive = CCDrawNode::create();
    drawNodeActive->setContentSize(CCSizeMake(width, height));
    
    CCSprite* spriteNormal = CCSprite::create(szNormalSpritePath);
    spriteNormal->setAnchorPoint(ccp(0.5f, 1.0f));
    spriteNormal->setPosition(ccp(width/2.0f - getSizeWithDevice(0), height));
    spriteNormal->setScale(getScaleWithDevice());
    drawNodeNormal->addChild(spriteNormal);
    
    CCSprite* spriteActive = CCSprite::create(szActiveSpritePath);
    spriteActive->setAnchorPoint(ccp(0.5f, 1.0f));
    spriteActive->setPosition(ccp(width/2.0f - getSizeWithDevice(0), height));
    spriteActive->setScale(getScaleWithDevice());
    drawNodeActive->addChild(spriteActive);
    
    CCLabelTTF* ttfLabelNormal = CCLabelTTF::create(szTitle, "tt0283m.ttf", getSizeWithDevice(16));
    ttfLabelNormal->setAnchorPoint(ccp(0.5f, 0.0f));
    ttfLabelNormal->setPosition(ccp(width/2.0f, 0.0f));
    ttfLabelNormal->setColor(ccc3(255, 255, 255));
    drawNodeNormal->addChild(ttfLabelNormal);
    
    CCLabelTTF* ttfLabelActive = CCLabelTTF::create(szTitle, "tt0283m.ttf", getSizeWithDevice(15));
    ttfLabelActive->setAnchorPoint(ccp(0.5f, 0.0f));
    ttfLabelActive->setPosition(ccp(width/2.0f, 0.0f));
    ttfLabelActive->setColor(ccc3(255, 255, 255));
    drawNodeActive->addChild(ttfLabelActive);
    
    CCMenuItem* menuItem = CCMenuItemSprite::create(drawNodeNormal, drawNodeActive, target, selector);
    return menuItem;
}

void TaskbarLayer::onSetting(CCObject* sender)
{
    if(_parentLayer == NULL) return;
    if(BoardLayer::getInstance()==NULL) return;
    if(BoardLayer::getInstance()->getSetting()) return;//onNewGame
    
    GameData::getInstance()->setShowSetting(true);
    
    //////////////
    if(GameData::getInstance()->getBannerHeight()>0){
        
        ((GameLayer*)_parentLayer)->upTaskbar(-GameData::getInstance()->getBannerHeight());
        GameData::getInstance()->setBannerHeight(0);
        AppDelegate::get()->sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", REMOVE_ADMOB);
    }
    //////////////
    
    GameData::getInstance()->playSoundEffect();
    
    BoardLayer::getInstance()->setSetting(true);
    
    GameData::getInstance()->setDoingAction(true);
    ((GameLayer*)_parentLayer)->showSettingLayer();
}

void TaskbarLayer::onCenter(CCObject* sender)
{
    if(BoardLayer::getInstance()->getSetting()) return;
    
    GameData::getInstance()->playSoundEffect();
    
    AppDelegate *app = AppDelegate::get();
    
    //custom
    //app->sendMessageToNative(MSG_GAMECENTER, "LeaderBoard", GameData::getInstance()->getGameType());
    
    
    
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
        {
            if(GameData::getInstance()->isVegasMode())
                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sVegasStyleScore", 1);
            else{
                if(GameData::getInstance()->isDrawFlag()){
                    app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sDraw3Score", 1);
                }else{
                    app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sDraw1Score", 1);
                }
            }
            
        }
            break;
            
        case TYPE_FREECELL:
            app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.FCHighScores", 1);
            break;
            
        case TYPE_FORTY_THIEVES:
            app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.FTHighScores", 1);
            break;
            
        case TYPE_SPIDER:
            if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY){
                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss1suitscore", 1);
            }
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL){
                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss2suitscore", 1);
            }
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT){
                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss3suitscore", 1);
            }
            else{
                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss4suitscore", 1);
            }
            break;
    }
    
}

void TaskbarLayer::onStore(CCObject* sender)
{
    if(BoardLayer::getInstance()->getSetting()) return;
    
    GameData::getInstance()->playSoundEffect();
    
    AppDelegate::get()->sendMessageToNative(MSG_REMOVE_ADS, "com.cobraclip.removeads", 1);
    
    /*
    if(GameData::getInstance()->getBannerHeight()>0){
    
        ((GameLayer*)_parentLayer)->upTaskbar(-GameData::getInstance()->getBannerHeight());
        GameData::getInstance()->setBannerHeight(0);
        AppDelegate::get()->sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", 0);
    }
    */
}

void TaskbarLayer::onMenu(CCObject* sender)
{
    //Select Game
    if(BoardLayer::getInstance()->getSetting()) return;
    
    GameData::getInstance()->playSoundEffect();
    
    _exitKind = GAME_MENU;
    
    if(BoardLayer::getInstance()->_hasWon)
    {
        didExitLayer(true);
    }
    else
    {
        BoardLayer::getInstance()->setSetting(true);
        CCSize winSize =CCDirector::sharedDirector()->getWinSize();
        
        _exitLayer = ExitLayer::create();
        _exitLayer->init(this);
        _exitLayer->setAnchorPoint(ccp(0.5f, 0.5f));
        _exitLayer->setPosition(ccp(0.0f, winSize.height));
        addChild(_exitLayer,2);
        
        CCMoveTo* action = CCMoveTo::create(0.3f, ccp(0,winSize.height/2.0f));
        CCEaseIn *_easein = CCEaseIn::create(action,0.3f);
        CCSequence *_sequence  =  CCSequence::create( _easein, NULL ,NULL);
        
        _exitLayer->runAction(_sequence);
        
    }
    
}

void TaskbarLayer::didExitLayer(bool isYes)
{
    
    if(_exitLayer!=NULL) _exitLayer->removeFromParentAndCleanup(true);
    _exitLayer=NULL;
    
    if(isYes)
    {
        switch(_exitKind)
        {
            case GAME_MENU:
                //if(GameData::getInstance()->getBackgroundIndex() == 7) GameData::getInstance()->setBackgroundIndex(0);
                
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuLayer::scene()));
                break;
            case GAME_PLAY:
                
                ///////////////////////////
                
                switch (GameData::getInstance()->getGameType()) {
                    case TYPE_SPIDER:
                    
                        ((GameLayer*) _parentLayer)->showSpiderOptionLayer();
                        break;
                        
                    case TYPE_SOLITAIRE:
                    
                        ((GameLayer*) _parentLayer)->showSolitaireOptionLayer();                    
                        break;
                        
                    case TYPE_FREECELL:
                    case TYPE_FORTY_THIEVES:
                        showNewGame();
                        break;
                }
                
                break;
            
        }
        
    }
    else
    {
        BoardLayer::getInstance()->setSetting(false);
    }
}

void TaskbarLayer::showNewGame()
{
    
     CCSize winSize = CCDirector::sharedDirector()->getWinSize();
     
     _newGameLayer = NewGameLayer::create();
     _newGameLayer->init(this);
     _newGameLayer->setAnchorPoint(ccp(0.5f, 0.5f));
     
     _newGameLayer->setPosition(ccp(winSize.width/2.0f, 0));
     addChild(_newGameLayer, 2);
     
     ((GameLayer*) _parentLayer)->getSettingLayer()->setEnabled(false);
     GameData::getInstance()->getInstance()->setNewGame(0);
     
     CCMoveTo* action = CCMoveTo::create(0.3f, ccp(0,winSize.height/2.0f));
     CCEaseIn *_easein = CCEaseIn::create(action,0.3f);
     CCSequence *_sequence  =  CCSequence::create( _easein, NULL ,NULL);
     
     _newGameLayer->runAction(_sequence);
    
}

void TaskbarLayer::onNewGame(CCObject* sender)
{
    //New Game
    if(BoardLayer::getInstance()==NULL) return;
    if(BoardLayer::getInstance()->getSetting()) return;//onSetting
    
    GameData::getInstance()->playSoundEffect();
    
    BoardLayer::getInstance()->setSetting(true);
    
    _exitKind = GAME_PLAY;
        
    if(BoardLayer::getInstance()->_hasWon)
    {
        didExitLayer(true);
    }
    else
    {
        CCSize winSize =CCDirector::sharedDirector()->getWinSize();
        
        _exitLayer = ExitLayer::create();
        _exitLayer->init(this);
        _exitLayer->setAnchorPoint(ccp(0.5f, 0.5f));
        _exitLayer->setPosition(ccp(0.0f, 0.0f));
        addChild(_exitLayer,2);
        
        CCMoveTo* action = CCMoveTo::create(0.3f, ccp(0,winSize.height/2.0f));
        CCEaseIn *_easein = CCEaseIn::create(action,0.3f);
        CCSequence *_sequence  =  CCSequence::create( _easein, NULL ,NULL);
        
        _exitLayer->runAction(_sequence);
    }
    
}

void TaskbarLayer::didNewGame()
{
    _newGameLayer->removeFromParentAndCleanup(true);
    _newGameLayer=NULL;
    BoardLayer::getInstance()->setSetting(false);
    ((GameLayer*) _parentLayer)->getSettingLayer()->setEnabled(true);
}

void TaskbarLayer::onHint(CCObject* sender)
{
    if(BoardLayer::getInstance()==NULL) return;
    if(BoardLayer::getInstance()->getSetting()) return;
    
    BoardLayer::getInstance()->hint();
}

void TaskbarLayer::onUndo(CCObject* sender)
{
    if(BoardLayer::getInstance()==NULL) return;
    if(BoardLayer::getInstance()->getSetting()) return;
    
    if(GameData::getInstance()->isSoundEnabled()){
        SimpleAudioEngine::sharedEngine()->playEffect("sparkle.wav");
    }
    BoardLayer::getInstance()->undo();
}

void TaskbarLayer::removeStoreButton(){
    
    if(_storeItem !=NULL)
        _storeItem->removeFromParentAndCleanup(true);
    _storeItem = NULL;
}
