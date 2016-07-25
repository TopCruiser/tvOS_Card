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
//#include "OrientationLayer.h" comment715
//#include "HelpLayer.h"

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;//Cocos2dx defined macros

using namespace cocos2d;

class SettingLayer : public cocos2d::Layer, public cocos2d::extension::TableViewDelegate, cocos2d::extension::TableViewDataSource
{
public:
    static cocos2d::Scene* scene();
    virtual bool init();
    virtual void init(Layer* parent);
    
    void updateLayoutWithPortrait();
    void updateLayoutWithLandscape();
    
    void menuCloseCallback(Ref* pSender);
    void onDone(Ref* sender);
    
public:
    
    //Click on any cell
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    //Each cell size
    //virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    
    //Generate cell
    virtual TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    //The number of cell
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell);
    
    //virtual Size cellSizeForTable(TableView *table);
    
    void scrollBar(cocos2d::extension::TableView* table);
    
    void didFinishCell();
    
    bool getEnabled();
    void setEnabled(bool isEnabled);
        
private:
    Layer* _parentLayer;
    Sprite* _background;
    Sprite* _header;
    Sprite* _title;
    TableView *tableView;
    Sprite* _footer;
    Sprite* _buttonbackground;
    MenuItem* btnDone;
    
    //OrientationLayer* _orientationLayer = NULL;comment715
    //HelpLayer* _helpLayer = NULL;
    
    bool _isEnabled;
public:
    CREATE_FUNC(SettingLayer);
};
#endif
