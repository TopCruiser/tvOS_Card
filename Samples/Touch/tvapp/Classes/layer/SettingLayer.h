//
//  SettingLayer.h
//  cardgame
//
//  Created by lion on 3/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//
#ifndef __cardgame__SettingLayer__
#define __cardgame__SettingLayer__

#include "Common.h"
#include "OrientationLayer.h"
//#include "HelpLayer.h"

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;//Cocos2dx defined macros
using namespace cocos2d;

class SettingLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDelegate,cocos2d::extension::CCTableViewDataSource
{
public:
    static cocos2d::CCScene* scene();
    virtual bool init();
    virtual void init(CCLayer* parent);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
    void menuCloseCallback(CCObject* pSender);
    void onDone(CCObject* sender);
    
public:
    
    //CCTableViewDelegate inherits from CCScrollViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    
    //Click on any cell
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    //Each cell size
    //virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    
    //Generate cell
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    //The number of cell
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    //Pressed down, is highlighted, where you can set the bright state
    virtual void tableCellHighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    //Release time, cancel the bright state
    virtual void tableCellUnhighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    void scrollBar(cocos2d::extension::CCTableView* table);
    
    void didFinishCell();
    
    bool getEnabled();
    void setEnabled(bool isEnabled);
        
private:
    CCLayer* _parentLayer;
    CCSprite* _background;
    CCSprite* _header;
    CCSprite* _title;
    CCTableView *tableView;
    CCSprite* _footer;
    CCSprite* _buttonbackground;
    CCMenuItem* btnDone;
    
    OrientationLayer* _orientationLayer = NULL;
    //HelpLayer* _helpLayer = NULL;
    
    bool _isEnabled;
public:
    CREATE_FUNC(SettingLayer);
};
#endif
