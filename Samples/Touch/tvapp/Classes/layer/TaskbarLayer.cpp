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

cocos2d::Scene* TaskbarLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    TaskbarLayer* layer = TaskbarLayer::create();
    scene->addChild(layer);
    return scene;
}

bool TaskbarLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}

void TaskbarLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    _background = Sprite::create(getNameWithDevice("bg_taskbar").c_str());
    _background->setScale(getScaleWithDevice());
    _background->setAnchorPoint(Vec2(0.5f, 0.0f));
    _background->setPosition(Vec2(0.0f, 0.0f));
    addChild(_background);
    
    Size size = _background->getContentSize();
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
    
    //add dummy object to receive focus
    MenuItem* dummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_freecell_nor").c_str()),
                                             Sprite::create(getNameWithResolution("btn_freecell_act").c_str()),
                                             this, menu_selector(TaskbarLayer::onDummy));
    dummy->setScale(0.001);
    
    _menu = Menu::create();
    _menu->setAnchorPoint(Vec2(0.0f, 0.0f));
    _menu->setPosition(Vec2(0.0f, 0.0f));
    
    _menu->addChild(_settingItem);
    _menu->addChild(_centerItem);
    
    if(!GameData::getInstance()->isRemoveAds()) _menu->addChild(_storeItem);
    
    _menu->addChild(_menuItem);
    _menu->addChild(_playItem);
    _menu->addChild(_hintItem);
    _menu->addChild(_undoItem);
    _menu->addChild(dummy);
    
    addChild(_menu);
    
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}

bool TaskbarLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void TaskbarLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void TaskbarLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void TaskbarLayer::updateLayoutWithPortrait()
{
    Size winSize = Director::getInstance()->getWinSize();
    Size size = getContentSize();
    
    _settingItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(50.0f), size.height/2.0f));
    _centerItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(130.0f), size.height/2.0f));
    //_storeItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(210.0f), size.height/2.0f));
    
    if(!GameData::getInstance()->isRemoveAds())
        _storeItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(230.0f), size.height/2.0f));
    
    _undoItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(50.0f), size.height/2.0f));
    _hintItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(130.0f), size.height/2.0f));
    _playItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(210.0f), size.height/2.0f));
    _menuItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(290.0f), size.height/2.0f));
    
    if(_newGameLayer != NULL)
    {
        _newGameLayer->setPosition(Vec2(0.0f, winSize.height/2.0f));
        _newGameLayer->setVisible(true);        
    }
    
    if(_exitLayer != NULL)
    {
        _exitLayer->setPosition(Vec2(0.0f, winSize.height/2.0f));
    }
    
}

void TaskbarLayer::updateLayoutWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    Size size = getContentSize();
    
    _settingItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(40.0f), size.height/2.0f));
    _centerItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(120.0f), size.height/2.0f));
    //_storeItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(200.0f), size.height/2.0f));
    
    if(!GameData::getInstance()->isRemoveAds())
        _storeItem->setPosition(Vec2(-winSize.width/2.0f + getSizeWithDevice(220.0f), size.height/2.0f));
    
    _undoItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(40.0f), size.height/2.0f));
    _hintItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(120.0f), size.height/2.0f));
    _playItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(200.0f), size.height/2.0f));
    _menuItem->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(280.0f), size.height/2.0f));
    
    if(_newGameLayer != NULL)
    {
        _newGameLayer->setPosition(Vec2(0.0f, winSize.height/2.0f));
        _newGameLayer->setVisible(true);
    }
    
    if(_exitLayer != NULL)
    {
        _exitLayer->setPosition(Vec2(0.0f, winSize.height/2.0f));
    }
    
}

MenuItem* TaskbarLayer::createItem(const char* szNormalSpritePath, const char* szActiveSpritePath, const char* szTitle,
                                    float width, float height, Ref* target, SEL_MenuHandler selector)
{
    DrawNode* drawNodeNormal = DrawNode::create();
    drawNodeNormal->setContentSize(Size(width, height));
   
    DrawNode* drawNodeActive = DrawNode::create();
    drawNodeActive->setContentSize(Size(width, height));
    
    Sprite* spriteNormal = Sprite::create(szNormalSpritePath);
    spriteNormal->setAnchorPoint(Vec2(0.5f, 1.0f));
    spriteNormal->setPosition(Vec2(width/2.0f - getSizeWithDevice(0), height));
    spriteNormal->setScale(getScaleWithDevice());
    drawNodeNormal->addChild(spriteNormal);
    
    Sprite* spriteActive = Sprite::create(szActiveSpritePath);
    spriteActive->setAnchorPoint(Vec2(0.5f, 1.0f));
    spriteActive->setPosition(Vec2(width/2.0f - getSizeWithDevice(0), height));
    spriteActive->setScale(getScaleWithDevice());
    drawNodeActive->addChild(spriteActive);
    
    CCLabelTTF* ttfLabelNormal = CCLabelTTF::create(szTitle, "tt0283m.ttf", getSizeWithDevice(16));
    ttfLabelNormal->setAnchorPoint(Vec2(0.5f, 0.0f));
    ttfLabelNormal->setPosition(Vec2(width/2.0f, 0.0f));
    ttfLabelNormal->setColor(Color3B(255, 255, 255));
    drawNodeNormal->addChild(ttfLabelNormal);
    
    CCLabelTTF* ttfLabelActive = CCLabelTTF::create(szTitle, "tt0283m.ttf", getSizeWithDevice(15));
    ttfLabelActive->setAnchorPoint(Vec2(0.5f, 0.0f));
    ttfLabelActive->setPosition(Vec2(width/2.0f, 0.0f));
    ttfLabelActive->setColor(Color3B(255, 255, 255));
    drawNodeActive->addChild(ttfLabelActive);
    
    MenuItem* menuItem = MenuItemSprite::create(drawNodeNormal, drawNodeActive, target, selector);
    return menuItem;
}

void TaskbarLayer::onSetting(Ref* sender)
{
    if(_parentLayer == NULL) return;
    if(BoardLayer::getInstance()==NULL) return;
    if(BoardLayer::getInstance()->getSetting()) return;//onNewGame
    
    GameData::getInstance()->setShowSetting(true);
    
    //////////////
    if(GameData::getInstance()->getBannerHeight()>0){
        
        ((GameLayer*)_parentLayer)->upTaskbar(-GameData::getInstance()->getBannerHeight());
        GameData::getInstance()->setBannerHeight(0);
        //AppDelegate::get()->sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", REMOVE_ADMOB);comment715
    }
    //////////////
    
    GameData::getInstance()->playSoundEffect();
    
    BoardLayer::getInstance()->setSetting(true);
    
    GameData::getInstance()->setDoingAction(true);
    ((GameLayer*)_parentLayer)->showSettingLayer();
}

void TaskbarLayer::onCenter(Ref* sender)
{
    if(BoardLayer::getInstance()->getSetting()) return;
    
    GameData::getInstance()->playSoundEffect();
    
    //AppDelegate *app = AppDelegate::get();comment715
    
    //custom
    //app->sendMessageToNative(MSG_GAMECENTER, "LeaderBoard", GameData::getInstance()->getGameType());
    
    
    
//    switch (GameData::getInstance()->getGameType()) {
//        case TYPE_SOLITAIRE:
//        {
//            if(GameData::getInstance()->isVegasMode())
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sVegasStyleScore", 1);
//            else{
//                if(GameData::getInstance()->isDrawFlag()){
//                    app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sDraw3Score", 1);
//                }else{
//                    app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.sDraw1Score", 1);
//                }
//            }
//            
//        }
//            break;
//            
//        case TYPE_FREECELL:
//            app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.FCHighScores", 1);
//            break;
//            
//        case TYPE_FORTY_THIEVES:
//            app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.FTHighScores", 1);
//            break;
//            
//        case TYPE_SPIDER:
//            if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY){
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss1suitscore", 1);
//            }
//            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL){
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss2suitscore", 1);
//            }
//            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT){
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss3suitscore", 1);
//            }
//            else{
//                app->sendMessageToNative(MSG_GAMECENTER, "com.cobraclip.cardgames.ss4suitscore", 1);
//            }
//            break;
//    }comment715
    
}

void TaskbarLayer::onStore(Ref* sender)
{
    if(BoardLayer::getInstance()->getSetting()) return;
    
    GameData::getInstance()->playSoundEffect();
    
    //AppDelegate::get()->sendMessageToNative(MSG_REMOVE_ADS, "com.cobraclip.removeads", 1);comment715
    
    /*
    if(GameData::getInstance()->getBannerHeight()>0){
    
        ((GameLayer*)_parentLayer)->upTaskbar(-GameData::getInstance()->getBannerHeight());
        GameData::getInstance()->setBannerHeight(0);
        AppDelegate::get()->sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", 0);
    }
    *///comment715
}

void TaskbarLayer::onMenu(Ref* sender)
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
        Size winSize =Director::getInstance()->getWinSize();
        
        _exitLayer = ExitLayer::create();
        _exitLayer->init(this);
        _exitLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
        _exitLayer->setPosition(Vec2(0.0f, winSize.height));
        setLocalZOrder(6);
        addChild(_exitLayer,1);
        
        MoveTo* action = MoveTo::create(0.3f, Vec2(0,winSize.height/2.0f));
        EaseIn *_easein = EaseIn::create(action,0.3f);
        Sequence *_sequence  =  Sequence::create( _easein, NULL ,NULL);
        
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
                
                Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MenuLayer::scene()));
                break;
            case GAME_PLAY:
                
                ///////////////////////////
                
                switch (GameData::getInstance()->getGameType()) {
                    case TYPE_SPIDER:
                    
                        setLocalZOrder(1);
                        ((GameLayer*) _parentLayer)->showSpiderOptionLayer();
                        break;
                        
                    case TYPE_SOLITAIRE:
                    
                        setLocalZOrder(1);
                        ((GameLayer*) _parentLayer)->showSolitaireOptionLayer();                    
                        break;
                        
                    case TYPE_FREECELL:
                    case TYPE_FORTY_THIEVES:
                        setLocalZOrder(1);
                        showNewGame();
                        break;
                }
                
                break;
            
        }
        
    }
    else
    {
        setLocalZOrder(0);
        BoardLayer::getInstance()->setSetting(false);
    }
}

void TaskbarLayer::showNewGame()
{
    
     Size winSize = Director::getInstance()->getWinSize();
     
     _newGameLayer = NewGameLayer::create();
     _newGameLayer->init(this);
     _newGameLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
     
     _newGameLayer->setPosition(Vec2(winSize.width/2.0f, 0));
     addChild(_newGameLayer, 2);
     
     ((GameLayer*) _parentLayer)->getSettingLayer()->setEnabled(false);
     GameData::getInstance()->getInstance()->setNewGame(0);
     
     MoveTo* action = MoveTo::create(0.3f, Vec2(0,winSize.height/2.0f));
     EaseIn *_easein = EaseIn::create(action,0.3f);
     Sequence *_sequence  =  Sequence::create( _easein, NULL ,NULL);
     
     _newGameLayer->runAction(_sequence);
}

void TaskbarLayer::onNewGame(Ref* sender)
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
        Size winSize =Director::getInstance()->getWinSize();
        
        _exitLayer = ExitLayer::create();
        _exitLayer->init(this);
        _exitLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
        _exitLayer->setPosition(Vec2(0.0f, 0.0f));
        setLocalZOrder(6);
        addChild(_exitLayer,2);
        
        MoveTo* action = MoveTo::create(0.3f, Vec2(0,winSize.height/2.0f));
        EaseIn *_easein = EaseIn::create(action,0.3f);
        Sequence *_sequence = Sequence::create( _easein, NULL ,NULL);
        
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

void TaskbarLayer::onHint(Ref* sender)
{
    if(BoardLayer::getInstance()==NULL) return;
    if(BoardLayer::getInstance()->getSetting()) return;
    
    BoardLayer::getInstance()->hint();
}

void TaskbarLayer::onUndo(Ref* sender)
{
    if(BoardLayer::getInstance()==NULL) return;
    if(BoardLayer::getInstance()->getSetting()) return;
    
    if(GameData::getInstance()->isSoundEnabled()){
        //SimpleAudioEngine::sharedEngine()->playEffect("sparkle.wav");
    }
    BoardLayer::getInstance()->undo();
}

void TaskbarLayer::onDummy(cocos2d::Ref *sender)
{
    
}

void TaskbarLayer::removeStoreButton(){
    
    if(_storeItem !=NULL)
        _storeItem->removeFromParentAndCleanup(true);
    _storeItem = NULL;
}

bool TaskbarLayer::pressesBegan(Vec2 touchPoint)
{
    
    CCLOG("Taskbarlayer - press began : (%f, %f)", touchPoint.x, touchPoint.y);
    touchPoint = convertToNodeSpace(touchPoint);
    
    if(_settingItem->getBoundingBox().containsPoint(touchPoint)) onSetting(this);
    if(_undoItem->getBoundingBox().containsPoint(touchPoint)) onUndo(this);
    if(_playItem->getBoundingBox().containsPoint(touchPoint)) onNewGame(this);
    if(_hintItem->getBoundingBox().containsPoint(touchPoint)) onHint(this);
    if(_centerItem->getBoundingBox().containsPoint(touchPoint)) onCenter(this);
    if(_storeItem->getBoundingBox().containsPoint(touchPoint)) onStore(this);
    if(_menuItem->getBoundingBox().containsPoint(touchPoint)) onMenu(this);
    
    return true;
    
}