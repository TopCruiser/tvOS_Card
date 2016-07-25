//
//  HelpLayer.h
//  cardgame
//
//  Created by lion on 4/10/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__HelpLayer__
#define __cardgame__HelpLayer__

#include "Common.h"
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;//Cocos2dx defined macros
using namespace cocos2d;

class HelpLayer : public cocos2d::Layer, public cocos2d::extension::TableViewDelegate,cocos2d::extension::TableViewDataSource
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
    
    //TableViewDelegate inherits from ScrollViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
    
    
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    //Each cell size
    //virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    
    //Generate cell
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    //The number of cell
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    //Pressed down, is highlighted, where you can set the bright state
    virtual void tableCellHighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
    //Release time, cancel the bright state
    virtual void tableCellUnhighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
    void scrollBar(cocos2d::extension::TableView* table);
    
private:
    Layer* _parentLayer;
    Sprite* _background;
    Sprite* _titlebar;
    TableView *tableView;
    MenuItem* btnDone;
    
    Sprite* _header;
    Sprite* _footer;
    Sprite* _backBackground;
    
    bool _isEnabled;
    
public:
    CREATE_FUNC(HelpLayer);
};

#endif /* defined(__cardgame__HelpLayer__) */
