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

class SettingLayer : public cocos2d::Layer, public cocos2d::extension::TableViewDelegate,cocos2d::extension::TableViewDataSource
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
    
    //CCTableViewDelegate inherits from CCScrollViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
    
    //Click on any cell
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    //Each cell size
    //virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual Size tableCellSizeForIndex(TableView *table, unsigned int idx);
    
    //Generate cell
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, unsigned int idx);
    //The number of cell
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    //Pressed down, is highlighted, where you can set the bright state
    virtual void tableCellHighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
    //Release time, cancel the bright state
    virtual void tableCellUnhighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
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
    
    OrientationLayer* _orientationLayer = NULL;
    //HelpLayer* _helpLayer = NULL;
    
    bool _isEnabled;
public:
};
#endif
