//
//  HelpLayer.cpp
//  cardgame
//
//  Created by lion on 4/10/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "HelpLayer.h"
#include "GameLayer.h"
#include "GameData.h"

Scene* HelpLayer::scene()
{
    Scene *scene = Scene::create();
    HelpLayer *layer = (HelpLayer*)HelpLayer::create();
    scene->addChild(layer);
    return scene;
}

bool HelpLayer::init()
{
    if(!Layer::init()) return false;
    
    return true;
}

void HelpLayer::init(Layer* parent)
{
    _parentLayer = parent;
    _isEnabled=true;
    
    //_background = CCSprite::create(getNameWithDevice("settingback").c_str());
    _background = CCSprite::create(getNameWithDeviceJpg("settingback").c_str());
    _background->setAnchorPoint(ccp(0.5f, 0.5f));
    _background->setScale(getScaleWithDevice());
    _background->setVisible(false);
    addChild(_background);
    
    _header = CCSprite::create(getNameWithDevice("setting_titlebar").c_str());
    _header->setScale(getScaleWithDevice());
    _header->setAnchorPoint(ccp(0.5f, 0.0f));
    addChild(_header);
    
    _footer = CCSprite::create(getNameWithDevice("bg_taskbar").c_str());
    _footer->setScale(getScaleWithDevice());
    _footer->setAnchorPoint(ccp(0.5f, 0.0f));
    _footer->setPosition(ccp(0.0f, 0.0f));
    addChild(_footer);
    
    _titlebar = CCSprite::create(getNameWithResolution("help").c_str());
    _titlebar->setAnchorPoint(ccp(0.5f, 0.5f));
    _titlebar->setScale(getScaleWithDevice());
    addChild(_titlebar);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    tableView=TableView::create(this, CCSizeMake(winSize.width-getSizeWithDevice(120.0f), winSize.height-getSizeWithDevice(190.0f)));
    tableView->setDirection(cocos2d::extension::TableView::Direction::VERTICAL);
    tableView->setAnchorPoint(ccp(0, 0));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    
    this->addChild(tableView,1);
    tableView->reloadData();
    
    _backBackground = CCSprite::create(getNameWithResolution("setting_buttonback").c_str());
    _backBackground->setAnchorPoint(ccp(0.5, 0.5));
    _backBackground->setScale(getScaleWithDevice());
    addChild(_backBackground);
    
    btnDone = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_back_nor").c_str()),
                                       CCSprite::create(getNameWithResolution("btn_back_act").c_str()),
                                       this, menu_selector(HelpLayer::onDone));
    
    btnDone->setAnchorPoint(ccp(0.5f, 0.0f));
    btnDone->setScale(getScaleWithDevice());
    
    CCMenu* _menu = CCMenu::create();
    _menu->addChild(btnDone);
        
    _menu->setPosition(ccp(0.0f, 0.0f));
    addChild(_menu);
    
    //if(g_nOrientation == ORIENTATION_PORTRAIT || g_nOrientation == ORIENTATION_PORTRAIT_UPSIDEDOWN)
        //updateLayoutWithPortrait();
    //else if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)
        //updateLayoutWithLandscape();
}

void HelpLayer::updateLayoutWithPortrait(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _background->setRotation(0.0f);
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(ccp(winSize.width/2.0f, winSize.height-getSizeWithDevice(117)));
    _footer->setPosition(ccp(winSize.width/2.0f, 0));
    
    _titlebar->setPosition(ccp(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    tableView->setPosition(ccp(getSizeWithDevice(60.0f), getSizeWithDevice(95.0f)));
    
    tableView->setViewSize( CCSizeMake(winSize.width-getSizeWithDevice(120.0f), winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _backBackground->setPosition(ccp(winSize.width/2.0f, getSizeWithDevice(42)));
    btnDone->setPosition(ccp(winSize.width/2.0f,  getSizeWithDevice(20.0f)));
    
}

void HelpLayer::updateLayoutWithLandscape(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _background->setRotation(90.0f);
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(ccp(winSize.width/2.0f, winSize.height - getSizeWithDevice(117)));
    _footer->setPosition(ccp(winSize.width/2.0f, 0));
    
    _titlebar->setPosition(ccp(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    
    tableView->setPosition(ccp(getSizeWithDevice(60.0f), getSizeWithDevice(95.0f)));
    tableView->setViewSize( CCSizeMake(winSize.width-getSizeWithDevice(120.0f), winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _backBackground->setPosition(ccp(winSize.width/2.0f, getSizeWithDevice(42)));
    btnDone->setPosition(ccp(winSize.width/2.0f,  getSizeWithDevice(20.0f)));
    
}

void HelpLayer::onDone(CCObject* sender)
{
    GameData::getInstance()->playSoundEffect();
    
    ((GameLayer*)_parentLayer)->hideHelpLayer();
    ((GameLayer*)_parentLayer)->getSettingLayer()->didFinishCell();
}

//The number of cell
ssize_t HelpLayer::numberOfCellsInTableView(TableView *table)
{
    return 8;
}

//Generate cell
TableViewCell* HelpLayer::tableCellAtIndex(TableView *table, unsigned int idx)
{
    //CCString *nameString=CCString::createWithFormat("cell_%d.png",idx);
    
    TableViewCell *cell = table->dequeueCell();
    
    //if(!cell)
    //{
    //CCLog("if no cell %d", idx);
    cell = new TableViewCell();
    cell->autorelease();
    
    CCSprite* titleSprite = CCSprite::create();
    titleSprite->setAnchorPoint(CCPointZero);
    titleSprite->setPosition(ccp(0,0));
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize textSize;
    if(g_nOrientation == ORIENTATION_PORTRAIT || g_nOrientation == ORIENTATION_PORTRAIT_UPSIDEDOWN)
    {
        if(idx == 1) textSize = CCSizeMake(winSize.width-getSizeWithDevice(120), getSizeWithDevice(1300));
        else textSize = CCSizeMake(winSize.width-getSizeWithDevice(120), getSizeWithDevice(900));
    }
    else
        textSize = CCSizeMake(winSize.width-getSizeWithDevice(120), getSizeWithDevice(700));
    
    CCLabelTTF* _cellLabel = CCLabelTTF::create("", "Thonburi", getSizeWithDevice(25), textSize, kCCTextAlignmentLeft);
    
    _cellLabel->setColor(ccc3(255, 255, 255));
    _cellLabel->setAnchorPoint(CCPointZero);
    _cellLabel->setPosition(ccp(0,0));
    
    //_cellLabel->set
    if(idx==0){
        titleSprite->initWithFile(getNameWithResolution("solitaire").c_str());
        titleSprite->setPosition(ccp(titleSprite->getContentSize().width/2, titleSprite->getContentSize().height/2));
        cell->addChild(titleSprite);
    }
    if(idx == 1){
        //_cellLabel->setString("The game begins gging it or by clicking it.");
        
        //_cellLabel->initWithString("The game begins gging it or by clicking it. The game begins gging it or by clicking it. The game begins gging it or by clicking it.", "Thonburi", getSizeWithDevice(30), CCSizeMake(getSizeWithDevice(200), getSizeWithDevice(80)), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        
        _cellLabel->setString("The game begins with 28 cards arranged into seven columns.\nThe first column contains one card, the second has two cards, and so on. The top card in each column is face up, the rest are face down. \nFour Home stacks are positioned at the upper-right corner. This is where you build the piles needed to win. \n\nEach Home stack must start with an ace. If you  don't have any, you'll have to move cards between columns until you uncover one. \nYou can't move cards between columns at random, however. \nColumns must be built in descending order, from king to ace. So you can place a 10 on a jack, but not on a 3. \n\nAs an added twist, cards in columns must also alternate red and black. \nYou aren't limited to moving single cards. You can also move sequentially organized runs of cards between columns. Just click the deepest card in the run and drag them all to another column. \n\nIf you run out of moves, you'll have to draw more cards by clicking the deck in the upper-right corner. If the deck runs out, click its outline on the table to reshuffle it. \nYou can move a card to the Home stack either by dragging it or by clicking it.");
        cell->addChild(_cellLabel);
    }
    if(idx==2){
        titleSprite->initWithFile(getNameWithResolution("freecell").c_str());
        titleSprite->setPosition(ccp(titleSprite->getContentSize().width/2, titleSprite->getContentSize().height/2));
        cell->addChild(titleSprite);
    }
    if(idx == 3){
        _cellLabel->setString("The tableau contains: \n   a manouevre zone with 8 manoeuvre stacks \n   four free cells at the top left \n   four foundation stacks at the top right \n \nIn the manoeuvre zone, form descendingsequences of alternate color. Cards are moved individually.\nThe four 'free cells', at the top left of the tableau, are each able to store a signle card. Cards may be placed here to help moving cards around the manoeuvre zone. \n \nIf a manoeuvre stack becomes empty during play, any exposed card from the free cells or another manoeuvre stack may be moved into the empty stack. \n \nCards are moved to the foundation to form ascending suit sequences. The game is won when all cards are moved to the foundation.");
        cell->addChild(_cellLabel);
    }
    if(idx==4){
        titleSprite->initWithFile(getNameWithResolution("spider").c_str());
        titleSprite->setPosition(ccp(titleSprite->getContentSize().width/2, titleSprite->getContentSize().height/2));
        cell->addChild(titleSprite);
    }
    if(idx == 5){
        _cellLabel->setString("Cards can be moved in the manoeuvre zone, onto cards of 1 higher rank, regardless of suiit. \nMultiple cards can be moved as a run, but only if they form a descending sequence ofthe same suit. \nAny Card (or run), can be moved into a vacant manoeuvre stack. \n \nClicking the talon will deal onenew card to each manoeuvre stack. Dealing these cards introduces new cards into play, but also covers other cards. A good general strategy for spider solitaire is to move as many cards as possible before dealing from the talon. \n \nSpider solitaire ends when all cards are moved into the 8 foundation stacks. \n \nThe 1-suit and 2-suit variations of spider solitaire are easier than the 4-suit version. Because there are less suits, it is easier to form same-suit runs. These raise the success rate significantly. In particular, 1-suit spider solitaire is quite easy, and can be a good place for beginners to start.");
        cell->addChild(_cellLabel);
    }
    if(idx==6){
        titleSprite->initWithFile(getNameWithResolution("forty").c_str());
        titleSprite->setPosition(ccp(titleSprite->getContentSize().width/2, titleSprite->getContentSize().height/2));
        cell->addChild(titleSprite);
    }
    if(idx == 7){
        _cellLabel->setString("The tableau contains: \n   A stock in the top left corner.\n   a manoeuvre zone with 10 stacks of 4 cards. \n   8 foundation stacks on the left and right sides of the screen. \n \nIn the manoeuvre zone, form descending same-suit sequences. (Eg: 7 of Clubs, on 9 of Clubs...) \nIn the foundation stacks, form ascending sequences of the same suit. (Eg: 3 of diamonds, on 2 of Diamonds, on Ace of Diamonds...) \nOnly one card can me be moved at once. \nAn empty column in the manoeuvre can be filled with any card.");
        cell->addChild(_cellLabel);
    }
    //}
    /*
     else
     {
     CCLog("else  %d", idx);
     //Create and would not need to re create, or you'll find out the picture with the words wrong
     CCTexture2D *aTexture=CCTextureCache::sharedTextureCache()->addImage(getNameWithResolution("setting_nor").c_str());
     CCSprite *pSprite=(CCSprite *)cell->getChildByTag(123);
     pSprite->setTexture(aTexture);
     }
     */
    return cell;
    
}


//CCSize HelpLayer::cellSizeForTable(CCTableView *table)
//{
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    return CCSizeMake(winSize.width-getSizeWithDevice(250.0f), getSizeWithDevice(500.0f));//40
//}

Size HelpLayer::tableCellSizeForIndex(TableView *table, unsigned int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    if(idx%2 == 0)  return CCSizeMake(winSize.width-getSizeWithDevice(120), getSizeWithDevice(80));
    else {
        if(g_nOrientation == ORIENTATION_PORTRAIT || g_nOrientation == ORIENTATION_PORTRAIT_UPSIDEDOWN)
        {
            if(idx == 1) return CCSizeMake(winSize.width-getSizeWithDevice(120), getSizeWithDevice(1300));
            else return CCSizeMake(winSize.width-getSizeWithDevice(120), getSizeWithDevice(900));
        }
            
        
        
        return CCSizeMake(winSize.width-getSizeWithDevice(120), getSizeWithDevice(700));
    }
    
}

void HelpLayer::tableCellHighlight(TableView *table, TableViewCell *cell)
{
    
}

void HelpLayer::tableCellUnhighlight(TableView *table, TableViewCell *cell)
{
    
}

void HelpLayer::tableCellTouched(TableView *table, TableViewCell *cell)
{
}

void HelpLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
}

void HelpLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
}