//
//  GameLayer.h
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__GameLayer__
#define __cardgame__GameLayer__

#include "Common.h"
#include "SolitaireOptionLayer.h"
#include "SpiderOptionLayer.h"
#include "BoardLayer.h"
#include "TaskbarLayer.h"

#include "SettingLayer.h"
#include "CardBackLayer.h"
#include "BackgroundLayer.h"
#include "CardFaceLayer.h"
#include "StatisticsLayer.h"
#include "HelpLayer.h"

///////
#include "ImagePicker.h"

class GameLayer : public cocos2d::Layer, ImagePickerDelegate
{
public:
    static cocos2d::Scene* scene();
   
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    
    virtual void didFinishPickingWithResult(cocos2d::Texture2D* result);//for getnativeBackground
    
    void showBoardLayerWithSolitaire();
    void showBoardLayerWithFreecell();
    void showBoardLayerWithFortythieves();
    void showBoardLayerWithSpider();
    
    void showTaskbar();
    void upTaskbar(int bannerHeight);
    
    void showSettingLayer();
    void hideSettingLayer();
    
    void showCardBackLayer();
    void showBackgroundLayer();
    void showCardFaceLayer();
    
    void showStatisticsLayer();
    void hideStatisticsLayer();
    
    void showHelpLayer();
    void hideHelpLayer();
    
    void updateLayoutWithLandscape();
    SettingLayer* getSettingLayer();
    void setBackground(int backgroundIndex);
    void setBackground(Texture2D* result);
    
    void showSolitaireOptionLayer();
    void showSpiderOptionLayer();
    TaskbarLayer* getTaskbarLayer();
    void removeOptionLayers();
    
private:    
    
    void doneSettingAnimation();
    
public:
    Sprite* _background = NULL;
    Sprite* _blankBanner = NULL;
    
    SolitaireOptionLayer* _solitaireOptionLayer = NULL;
    SpiderOptionLayer* _spiderOptionLayer = NULL;
    BoardLayer* _boardLayer = NULL;
    TaskbarLayer* _taskbarLayer = NULL;
    
    SettingLayer* _settingLayer=NULL;
    CardBackLayer* _cardBackLayer=NULL;
    BackgroundLayer* _backgroundLayer=NULL;
    CardFaceLayer* _cardFaceLayer=NULL;
    StatisticsLayer* _statisticsLayer=NULL;
    HelpLayer* _helpLayer=NULL;
    
    bool _isFirstLunch;
    bool _isShowTaskbar;
    
public:
    CREATE_FUNC(GameLayer);
};

#endif