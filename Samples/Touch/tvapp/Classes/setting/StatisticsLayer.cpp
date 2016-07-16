//
//  StatisticsLayer.cpp
//  cardgame
//
//  Created by lion on 3/10/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "StatisticsLayer.h"
#include "GameLayer.h"
#include "GameData.h"

Scene* StatisticsLayer::scene()
{
    Scene *scene = Scene::create();
    StatisticsLayer *layer = (StatisticsLayer*)StatisticsLayer::create();
    scene->addChild(layer);
    return scene;
}

bool StatisticsLayer::init()
{
    if(!Layer::init()) return false;
    
    return true;
}

void StatisticsLayer::init(Layer* parent)
{
    _parentLayer = parent;
    _isEnabled=true;
    
    //_background = Sprite::create(getNameWithDevice("settingback").c_str());
    _background = Sprite::create(getNameWithDeviceJpg("settingback").c_str());
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));
    _background->setScale(getScaleWithDevice());
    _background->setVisible(false);
    addChild(_background);
    
    _header = Sprite::create(getNameWithDevice("setting_titlebar").c_str());
    _header->setScale(getScaleWithDevice());
    _header->setAnchorPoint(Vec2(0.5f, 0.0f));
    addChild(_header);
    
    _footer = Sprite::create(getNameWithDevice("bg_taskbar").c_str());
    _footer->setScale(getScaleWithDevice());
    _footer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _footer->setPosition(Vec2(0.0f, 0.0f));
    addChild(_footer);
    
    _titlebar = Sprite::create(getNameWithResolution("statistics").c_str());
    _titlebar->setAnchorPoint(Vec2(0.5f, 0.5f));
    _titlebar->setScale(getScaleWithDevice());
    addChild(_titlebar);
    
    CCSize winSize = Director::getInstance()->getWinSize();
    tableView=TableView::create(this, Size(winSize.width-getSizeWithDevice(200.0f), winSize.height-getSizeWithDevice(190.0f)));
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    tableView->setAnchorPoint(Vec2(0, 0));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    
    this->addChild(tableView,1);
    tableView->reloadData();
    
    _backBackground = Sprite::create(getNameWithResolution("setting_buttonback").c_str());
    _backBackground->setAnchorPoint(Vec2(0.5, 0.5));
    _backBackground->setScale(getScaleWithDevice());
    addChild(_backBackground);
    
    _resetBackground = Sprite::create(getNameWithResolution("setting_buttonback").c_str());
    _resetBackground->setAnchorPoint(Vec2(0.5, 0.5));
    _resetBackground->setScale(getScaleWithDevice());
    addChild(_resetBackground);
    
    btnReset = CCMenuItemSprite::create(Sprite::create(getNameWithResolution("btn_reset_nor").c_str()),
                                        Sprite::create(getNameWithResolution("btn_reset_act").c_str()),
                                        this, menu_selector(StatisticsLayer::onReset));
    
    btnReset->setAnchorPoint(Vec2(0.5f, 0.0f));
    btnReset->setScale(getScaleWithDevice());
    //btnReset->setPosition(Vec2(winSize.width*0.4f,  getSizeWithDevice(30.0f)));
    
    btnDone = CCMenuItemSprite::create(Sprite::create(getNameWithResolution("btn_close_nor").c_str()),
                                       Sprite::create(getNameWithResolution("btn_close_act").c_str()),
                                       this, menu_selector(StatisticsLayer::onDone));
    
    btnDone->setAnchorPoint(Vec2(0.5f, 0.0f));
    btnDone->setScale(getScaleWithDevice());
    //btnDone->setPosition(Vec2(winSize.width*0.6f,  getSizeWithDevice(30.0f)));
    
    
    
    CCMenu* _menu = CCMenu::create();
    _menu->addChild(btnDone);
    _menu->addChild(btnReset);
    
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
    
    
}

void StatisticsLayer::updateLayoutWithPortrait(){
    CCSize winSize = Director::getInstance()->getWinSize();
    _background->setRotation(0.0f);
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(Vec2(winSize.width/2.0f, winSize.height-getSizeWithDevice(117)));
    _footer->setPosition(Vec2(winSize.width/2.0f, 0));
    
    _titlebar->setPosition(Vec2(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    tableView->setPosition(Vec2(getSizeWithDevice(120.0f), getSizeWithDevice(95.0f)));
    
    tableView->setViewSize( CCSizeMake(winSize.width-getSizeWithDevice(240.0f), winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _backBackground->setPosition(Vec2(winSize.width*0.25, getSizeWithDevice(42)));
    _resetBackground->setPosition(Vec2(winSize.width*0.75, getSizeWithDevice(42)));
                                 
    btnReset->setPosition(Vec2(winSize.width*0.25f,  getSizeWithDevice(20.0f)));
    btnDone->setPosition(Vec2(winSize.width*0.75f,  getSizeWithDevice(20.0f)));
    
}

void StatisticsLayer::updateLayoutWithLandscape(){
    CCSize winSize = Director::getInstance()->getWinSize();
    _background->setRotation(90.0f);
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(Vec2(winSize.width/2.0f, winSize.height - getSizeWithDevice(117)));
    _footer->setPosition(Vec2(winSize.width/2.0f, 0));
    
    _titlebar->setPosition(Vec2(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    
    tableView->setPosition(Vec2(getSizeWithDevice(120.0f), getSizeWithDevice(95.0f)));
    tableView->setViewSize( CCSizeMake(winSize.width-getSizeWithDevice(240.0f), winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _backBackground->setPosition(Vec2(winSize.width*0.25, getSizeWithDevice(42)));
    _resetBackground->setPosition(Vec2(winSize.width*0.75, getSizeWithDevice(42)));
    
    btnReset->setPosition(Vec2(winSize.width*0.25f,  getSizeWithDevice(20.0f)));
    btnDone->setPosition(Vec2(winSize.width*0.75f,  getSizeWithDevice(20.0f)));
    
}

void StatisticsLayer::onDone(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    ((GameLayer*)_parentLayer)->hideStatisticsLayer();
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

void StatisticsLayer::onReset(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    //initialize
    std::vector<std::string> _gameTypeName;
    
    _gameTypeName.push_back("Draw3");
    _gameTypeName.push_back("Draw1");
    _gameTypeName.push_back("Freecell");
    _gameTypeName.push_back("FortyThieves");
    _gameTypeName.push_back("Suit1");
    _gameTypeName.push_back("Suit2");
    _gameTypeName.push_back("Suit3");
    _gameTypeName.push_back("Suit4");
    
    for(int j=0; j<10; j++){
        for(int i=0; i<8; i++){
            GameData::getInstance()->deleteStatisticsItem(_gameTypeName[i], j);
        }
    }
    ((GameLayer*)_parentLayer)->hideStatisticsLayer();
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

//The number of cell
ssize_t StatisticsLayer::numberOfCellsInTableView(TableView *table)
{
    return 88;
}

//Generate cell
TableViewCell* StatisticsLayer::tableCellAtIndex(TableView *table, unsigned int idx)
{
    //CCString *nameString=CCString::createWithFormat("cell_%d.png",idx);
    
    TableViewCell *cell = table->dequeueCell();
    
    //if(!cell)
    //{
    //CCLog("if no cell %d", idx);
    cell = new TableViewCell();
    cell->autorelease();
    
    CCSize winSize = Director::getInstance()->getWinSize();
    
    CCLabelTTF* _subLabel = CCLabelTTF::create("", "tt0283.ttf", getSizeWithDevice(30), CCSizeMake(winSize.width/2.0f, getSizeWithDevice(80.0f)), kCCTextAlignmentRight, kCCVerticalTextAlignmentBottom);
                                               
    _subLabel->setColor(ccc3(255, 255, 255));
    _subLabel->setAnchorPoint(CCPointZero);
    _subLabel->setPosition(CCPointZero);
    
    CCLabelTTF* _cellLabel = CCLabelTTF::create("0", "tt0283m.ttf", getSizeWithDevice(30));
    _cellLabel->setColor(ccc3(255, 255, 255));
    _cellLabel->setAnchorPoint(CCPointZero);
    
    
    _cellLabel->setPosition(Vec2(winSize.width/2 + getSizeWithDevice(20.0f),0));
    const char* label;
    
    int i=idx / 11;
    int j=idx % 11;
    
    std::vector<std::string> _gameTypeName;
    std::vector<std::string> _statisticsItem;
    
    _gameTypeName.push_back("Draw3");
    _gameTypeName.push_back("Draw1");
    _gameTypeName.push_back("Freecell");
    _gameTypeName.push_back("FortyThieves");
    _gameTypeName.push_back("Suit1");
    _gameTypeName.push_back("Suit2");
    _gameTypeName.push_back("Suit3");
    _gameTypeName.push_back("Suit4");
    
    _statisticsItem.push_back("Games Won: ");
    _statisticsItem.push_back("Games Lost: ");
    _statisticsItem.push_back("Shortest Winning Time: ");
    _statisticsItem.push_back("Average Winning Time: ");
    _statisticsItem.push_back("Longest Winning Time: ");
    _statisticsItem.push_back("Wins without Undo: ");
    _statisticsItem.push_back("High Standard Score: ");
    _statisticsItem.push_back("High Vegas Score: ");
    _statisticsItem.push_back("Current Winning Streak: ");
    _statisticsItem.push_back("Longest Winning Streak: ");
    
    
    //std::string temp=_gameTypeName[2];
    //CCLog("aaaaaaa = %s", temp);
    //const char* ch=temp.c_str();
    //CCLog("%s", ch);

    
    if(j==0){
        //Statistics
        
        Sprite* titleSprite = Sprite::create();
        titleSprite->setAnchorPoint(CCPointZero);
        titleSprite->setPosition(Vec2(winSize.width/2 - getSizeWithDevice(120), 0));
        cell->addChild(titleSprite);
        
        switch (i) {
            case 0:
                titleSprite->initWithFile(getNameWithResolution("solitaire_draw3").c_str());
                break;
            
            case 1:
                titleSprite->initWithFile(getNameWithResolution("solitaire_draw1").c_str());
                break;
                
            case 2:
                titleSprite->initWithFile(getNameWithResolution("freecell").c_str());
                break;
                
            case 3:
                titleSprite->initWithFile(getNameWithResolution("forty").c_str());
                break;
                
            case 4:
                titleSprite->initWithFile(getNameWithResolution("spider_1suit").c_str());
                break;
                
            case 5:
                titleSprite->initWithFile(getNameWithResolution("spider_2suit").c_str());
                break;
                
            case 6:
                titleSprite->initWithFile(getNameWithResolution("spider_3suit").c_str());
                break;
                
            case 7:
                titleSprite->initWithFile(getNameWithResolution("spider_4suit").c_str());
                break;
                
            default:
                break;
        }
        
    }
    else{
        if(j==8  && i>1) _subLabel->setString("Most Winning Moves");
        else  _subLabel->setString(_statisticsItem[j-1].c_str());
        
        cell->addChild(_subLabel);
        label=GameData::getInstance()->getStatisticsItem(_gameTypeName[i], j-1).c_str();
        _cellLabel->setString(label);
        cell->addChild(_cellLabel);
    }
    
    //}
    /*
     else
     {
     CCLog("else  %d", idx);
     //Create and would not need to re create, or you'll find out the picture with the words wrong
     CCTexture2D *aTexture=CCTextureCache::sharedTextureCache()->addImage(getNameWithResolution("setting_nor").c_str());
     Sprite *pSprite=(Sprite *)cell->getChildByTag(123);
     pSprite->setTexture(aTexture);
     }
     */
    return cell;
    
}


Size StatisticsLayer::cellSizeForTable(TableView *table)
{
    Size winSize = Director::getInstance()->getWinSize();
    return CCSizeMake(winSize.width-getSizeWithDevice(240.0f), getSizeWithDevice(80.0f));
}

void StatisticsLayer::tableCellHighlight(TableView *table, TableViewCell *cell)
{
    
}

void StatisticsLayer::tableCellUnhighlight(TableView *table, TableViewCell *cell)
{
    
}

void StatisticsLayer::tableCellTouched(TableView *table, TableViewCell *cell)
{
}

void StatisticsLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
}

void StatisticsLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
}

TableView* StatisticsLayer::getTableView()
{
    return tableView;
}