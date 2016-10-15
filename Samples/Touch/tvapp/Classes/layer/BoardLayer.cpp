//
//  BoardLayer.cpp
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "BoardLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "CardSprite.h"
#include "Move.h"
#include "AppDelegate.h"
#include "WinningDeal.h"
#include "MyObjective-C-Interface.h"

#define LABEL_HEIGHT                85.0f
#define SOLITAIRE_MARGIN_PORT       10.0f
#define SOLITAIRE_PADDING_PORT      5.0f
#define SOLITAIRE_MARGIN_LAND       20.0f
#define SOLITAIRE_SMALLPADDING_LAND 10.0f

float SOLITAIRE_LARGEPADDING_LAND = 70.0f;
//#define SOLITAIRE_LARGEPADDING_LAND 70.0f //ipad : 20, iphone : 70

#define FREECELL_MARGIN_PORT        10.0f
#define FREECELL_PADDING_PORT       5.0f
#define FREECELL_MARGIN_LAND        20.0f
#define FREECELL_SMALLPADDING_LAND  10.0f
#define FREECELL_LARGEPADDING_LAND  20.0f //70.0f

#define FORTY_MARGIN_PORT           10.0f
#define FORTY_PADDING_PORT          5.0f
#define FORTY_MARGIN_LAND           20.0f
#define FORTY_PADDING_LAND          10.0f

#define SPIDER_PADDING_PORT         5.0f
#define SPIDER_MARGIN_PORT          10.0f
#define SPIDER_PADDING_LAND         10.0f
#define SPIDER_MARGIN_LAND          20.0f

enum NEW_GAME {
    RANDOM_DEAL = 0,
    WINNING_DEAL,
    REPLAY_DEAL,
    SELECT_DEAL
};

cocos2d::Scene* BoardLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    BoardLayer* layer = BoardLayer::create();
    scene->addChild(layer);
    return scene;
}

bool BoardLayer::init()
{
    if(!Layer::init()) return false;
    
    return true;
}

void BoardLayer::init(Layer* parent)
{
    _parentLayer = parent;
    
    //added by KHJ 04/18/2015
    std::string deviceName = getNameWithDevice("test");
    
    if(deviceName.find("test_ipad") != std::string::npos)
    {
        SOLITAIRE_LARGEPADDING_LAND = 20.0f;
    }
    //
    
    _cells = 4;
    _suits = 4;
    _stacks = 7;
    _directMode = 1;
    _gameScore = 0;
    _cuttingScore = 0;
    
    _stageTime = 0.0f;
    _startTime = 0.0f;
    _tempTime = 0.0f;
    _tempTime1 = 0.0f;
    _playstackVerticalSpace = 60.0f;
    
    _hasWon = false;
    _gameFirstStarted = false;
    _startedGameFlag = false;
    _actuallyCardMoved = false;
    bTouchBegan = false;
    lastMovedPoint = Vec2(960, 540);
    
    cards = new __Array; cards->init();
    playCells = new __Array; playCells->init();
    freeCells = new __Array; freeCells->init();
    goalCells = new __Array; goalCells->init();
    moves = new __Array; moves->init();
    
    _dealer = NULL;
    _dealTo = NULL;
    _draggingCard = NULL;
    
    _isSetting=false;

    initLayout();
    
    MyObjectDoSomethingWith(this, "bgm.mp3");
    if(GameData::getInstance()->isEffectEnabled()){
        MyObjectDoSomethingWith(this, "");
    }
    GameData::getInstance()->setSelectedGame(0);//in freecell
    GameData::getInstance()->setNewGame(0);//random dealer
    
}

BoardLayer* BoardLayer::_instance = NULL;

BoardLayer* BoardLayer:: getInstance()
{
    return _instance;
}

void BoardLayer::setInstance(BoardLayer* _board){
    _instance=_board;
}

void BoardLayer::setCells(int cells)
{
    _cells = cells;
}

void BoardLayer::setSuits(int suits)
{
    _suits = suits;
}

void BoardLayer::setStacks(int stacks)
{
    _stacks = stacks;
}

long BoardLayer::getScore()
{
    return _gameScore;
}

Deck* BoardLayer::getDealTo()
{
    return _dealTo;
}

void BoardLayer::replayGame()
{
    unschedule(schedule_selector(BoardLayer::setTime));
    
    _hasWon = false;
    _startedGameFlag = false;
    _actuallyCardMoved = false;
    
    initLayout();
    
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* deck = (Deck*) goalCells->getObjectAtIndex(i);
        deck->removeAllChildrenWithCleanup(true);
    }
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*) playCells->getObjectAtIndex(i);
        deck->removeAllChildrenWithCleanup(true);
    }
    
    if(freeCells!=NULL){
        
        for(int i = 0; i < freeCells->count(); i++)
        {
            Deck* deck = (Deck*) freeCells->getObjectAtIndex(i);
            deck->removeAllChildrenWithCleanup(true);
        }
        freeCells->removeAllObjects();
        
    }
    
    if(_dealTo!=NULL){
        _dealTo->removeAllChildrenWithCleanup(true);
        _dealTo = NULL;
    }
    
    _dealer->removeAllChildrenWithCleanup(true);
    playCells->removeAllObjects();
    goalCells->removeAllObjects();
    
    moves->removeAllObjects();
    
    if(_draggingCard!=NULL)
    {
        _draggingCard->removeAllChildrenWithCleanup(true);
        _draggingCard = NULL;
    }
    cards->removeAllObjects();
    
    if(GameData::getInstance()->getNewGame() == REPLAY_DEAL)
        setPreviousMode();
    
    if(GameData::getInstance()->getGameType() == TYPE_SPIDER)
    {
        switch (GameData::getInstance()->getSpiderMode()) {
            case SPIDER_MODE_EASY:
                setSuits(1);
                break;
            case SPIDER_MODE_NORMAL:
                setSuits(2);
                break;
            case SPIDER_MODE_EXPERT:
                setSuits(3);
                break;
            case SPIDER_MODE_HARD:
                setSuits(8);  
                break;
            default:
                break;
        }
    }
    
    setTouchEnabled(false);
    startNewGame();
    
    ((GameLayer*)_parentLayer)->_taskbarLayer->setLocalZOrder(0);
}
void BoardLayer::startNewGame()
{
    AppDelegate::get()->AppDelegate::get()->sendMessageToNative(MSG_SHOW_CHARTBOOST, "Game Start", 1);
//    if(!GameData::getInstance()->isRemoveAds())
//    {
//        if(GameData::getInstance()->isMenuLayer())
//            AppDelegate::get()->sendMessageToNative(MSG_SHOW_CHARTBOOST, "Game Start", 1);
//        else
//            AppDelegate::get()->sendMessageToNative(MSG_SHOW_CHARTBOOST, "New Game", 1);
//    }comment 715
    
    GameData::getInstance()->setMenuLayer(false);
    
    //Google Analytics
//    switch (GameData::getInstance()->getGameType()) {
//        case TYPE_SOLITAIRE:
//            AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Solitaire Screen", 1);
//            break;
//            
//        case TYPE_FREECELL:
//            AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Freecell Screen", 1);
//            break;
//            
//        case TYPE_FORTY_THIEVES:
//            AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Forty Thieves Screen", 1);
//            break;
//            
//        case TYPE_SPIDER:
//            AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Spider Solitaire Screen", 1);
//            break;
//    } //commented 716
    //
    
//    switch (GameData::getInstance()->getGameType()) {
//        case TYPE_SOLITAIRE:
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "Solitaire Win", 1);
//            break;
//        case TYPE_FREECELL:
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "FreeCell Win", 1);
//            break;
//        case TYPE_FORTY_THIEVES:
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "Spider Solitaire Win", 1);
//            break;
//        case TYPE_SPIDER:
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "Forty Thieves Win", 1);
//            break;           
//        
//    }
    
    _isHint = false;
    
    _solitaireAllFace = 0;
    _solitaireAllAces = true;
    
    _freecellUseCount = 0;
    _freecellOneCard = true;
    _freecellOnlyKing = true;
    
    index=0; count=0; stack=0;
    if(GameData::getInstance()->isRightHanded())
        _directMode = -1;
    
    if(!_hasWon && _gameFirstStarted)
    {   //at first, gamefirststarted==false, second, gamefirststarted=true
        std::string lostStr = getGameString() + "lost";
        int lostCount = GameData::getInstance()->getInt(lostStr, 0);
        lostCount++;
        GameData::getInstance()->setInt(lostStr, lostCount);
        
        std::string prevGameResult = getGameString() + "prevGameResult";
        GameData::getInstance()->setInt(prevGameResult, 0);
        saveGameStatus();
    }
    
    setGameInfo();
    
    _hasWon = false;
    
    cards->removeAllObjects();
    createPlayCells();
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
        createFreeCells();
    createGoalCells();
    createDealer();

    updateLayoutWithLandscape();
    
    GameData::getInstance()->setDoingAction(true);
    
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
        schedule(schedule_selector(BoardLayer::drawDealer), 0.04f);
    else
        schedule(schedule_selector(BoardLayer::addCardsToPlayCell), 0.05f);
    
    //CurrentValue
    if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE){
        _isCurrentDrawFlag = GameData::getInstance()->isDrawFlag();
        _isCurrentVegas = GameData::getInstance()->isVegasMode();
    }
    
    if(GameData::getInstance()->getGameType() == TYPE_SPIDER){
        _currentSpiderMode = GameData::getInstance()->getSpiderMode();
    }
    
    _parentLayer->setTag(101);
}

std::string BoardLayer::getGameString()
{
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
            if(GameData::getInstance()->isDrawFlag())
                return "Draw3";
            else
                return "Draw1";
        case TYPE_FREECELL:
            return "Freecell";
        case TYPE_FORTY_THIEVES:
            return "FortyThieves";
        case TYPE_SPIDER:
            if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY)
                return "Suit1";
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL)
                return "Suit2";
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT)
                return "Suit3";
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_HARD)
                return "Suit4";
        default:
            break;
    }
    
    return "";
}

void BoardLayer::saveGameStatus()
{
    std::string winStr = getGameString() + "Wins";
    std::string highScoreStr = getGameString() + "highscore";
    std::string shortTimeStr = getGameString() + "shortTime";
    std::string longTimeStr = getGameString() + "longTime";
    std::string avgTimeStr = getGameString() + "averangeTime";
    std::string undoStr = getGameString() + "withoutUndo";
    std::string hintStr = getGameString() + "withoutHint";
    std::string gameCountStr = getGameString() + "gameCount";
    std::string longWinStreakStr = getGameString() + "longStreak";
    std::string currentWinStreakStr = getGameString() + "currentStreak";
    std::string prevGameResult = getGameString() + "prevGameResult";
    std::string totalMovesStr = getGameString() + "winningMoves";
    std::string vegasStr = getGameString() + "vegasScore";
    
    std::string totalScoreStr = getGameString() + "totalScore";
    std::string totalVegasStr = getGameString() + "totalVegasScore";
    
    std::string selectFreecellStr = getGameString() + "selectFreecell";
    
    int oldScore = GameData::getInstance()->getInt(highScoreStr, 0);
    int oldWins = GameData::getInstance()->getInt(winStr, 0);
    
    if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE && GameData::getInstance()->isVegasMode())
    {
        if(GameData::getInstance()->getInt(vegasStr, 0) < _gameScore)
            GameData::getInstance()->setInt(vegasStr, (int)_gameScore);
    }
    else
    {
        if(_gameScore > oldScore)
            GameData::getInstance()->setInt(highScoreStr, (int)_gameScore);
    }
    
    int totalGameCount = GameData::getInstance()->getInt(gameCountStr, 0);
    
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL){
        
        if(GameData::getInstance()->getNewGame() == SELECT_DEAL){
            int selectFreecellCount = GameData::getInstance()->getInt(selectFreecellStr, 0);
            selectFreecellCount ++;
            GameData::getInstance()->setInt(selectFreecellStr, selectFreecellCount);
        }
    }
    
    
    if(_hasWon)
    {
        oldWins++;
        GameData::getInstance()->setInt(winStr, oldWins);
        
        int totalScore = GameData::getInstance()->getInt(totalScoreStr, 0);
        totalScore += getScore();
        
        GameData::getInstance()->setInt(totalScoreStr, totalScore);
        
        
        if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE && GameData::getInstance()->isVegasMode())
        {
            int totalVegasScore =GameData::getInstance()->getInt(totalVegasStr, 0);
            totalVegasScore +=getScore();
            
            GameData::getInstance()->setInt(totalVegasStr, totalVegasScore);
        }
        
        
        if(GameData::getInstance()->getInt(totalMovesStr, 0) < _totalMoveCount)
            GameData::getInstance()->setInt(totalMovesStr, _totalMoveCount);
        
        if(GameData::getInstance()->getFloat(shortTimeStr, 0) == 0)
            GameData::getInstance()->setFloat(shortTimeStr, _stageTime);
        else if(GameData::getInstance()->getFloat(shortTimeStr, 0) > _stageTime)
            GameData::getInstance()->setFloat(shortTimeStr, _stageTime);
        
        if(GameData::getInstance()->getFloat(longTimeStr, 0) < _stageTime)
            GameData::getInstance()->setFloat(longTimeStr, _stageTime);
        
        if(_totalUndoCount == 0)
        {
            int winsWithoutCount = GameData::getInstance()->getInt(undoStr, 0);
            winsWithoutCount++;
            GameData::getInstance()->setInt(undoStr, winsWithoutCount);
        }
        
        if(!_isHint)
        {
            int winsWithoutHint = GameData::getInstance()->getInt(hintStr, 0);
            winsWithoutHint++;
            GameData::getInstance()->setInt(hintStr, winsWithoutHint);
        }
        
        float avgTime = (GameData::getInstance()->getFloat(avgTimeStr, 0) * (oldWins - 1) + _stageTime) / oldWins;
        GameData::getInstance()->setFloat(avgTimeStr, avgTime);
        
        int currentStreak = GameData::getInstance()->getInt(currentWinStreakStr, 0);
        if(GameData::getInstance()->getInt(prevGameResult, 0) == 1)
        {
            currentStreak++;
            GameData::getInstance()->setInt(currentWinStreakStr, currentStreak);
        }
        else
        {
            GameData::getInstance()->setInt(currentWinStreakStr, 1);
            currentStreak = 1;
        }
        
        int longStreak = GameData::getInstance()->getInt(longWinStreakStr, 0);
        if(currentStreak > longStreak)
        {
            longStreak = currentStreak;
            GameData::getInstance()->setInt(longWinStreakStr, longStreak);
        }
        
        GameData::getInstance()->setInt(prevGameResult, 1);
    }
    
    GameData::getInstance()->setInt(gameCountStr, totalGameCount + 1);
}

void BoardLayer::setGameInfo()
{
    _totalMoveCount = 0;
    _totalUndoCount = 0;
    _stageTime = 0.0f;
    _startTime = 0.0f;
    _tempTime = 0.0f;
    _tempTime1 = 0.0f;
    _cuttingScore = 0;
    
    _timeLabel->setString("TIME:00:00");
    
    _startedGameFlag = false;
    _hasWon = false;
    
    switch(GameData::getInstance()->getGameType())
    {
        case TYPE_SOLITAIRE:
            if(GameData::getInstance()->isVegasMode())
                _gameScore = -52;
            else
                _gameScore = 0;
            
            _maxPlayCards = 28;
            _dealsLeftCount = 1000;
            _playstackVerticalSpace = 12.0f;
            break;
        case TYPE_FREECELL:
            _gameScore = 0;
            _maxPlayCards = 52;
            _playstackVerticalSpace = 36.0f;
            break;
        case TYPE_FORTY_THIEVES:
            _gameScore = 0;
            _maxPlayCards = 40;
            _playstackVerticalSpace = 36.0f;
            _dealsLeftCount = 0;
            break;
        case TYPE_SPIDER:
            _gameScore = 0;
            _maxPlayCards = 54;
            _playstackVerticalSpace = 12.0f;
            break;
        default:
            break;
    }
}

void BoardLayer::initLayout()
{
    if(!_gameFirstStarted){
        _scoreLabel = LabelTTF::create("SCORE:0", "ClarendonBT-Roman", getSizeWithDevice(20));
        _scoreLabel->setColor(Color3B(255, 255, 255));
        //_scoreLabel->enableStroke(ccRED, 10);
        addChild(_scoreLabel, 0);
        
        _moveLabel = LabelTTF::create("MOVES:0", "ClarendonBT-Roman", getSizeWithDevice(20));
        _moveLabel->setColor(Color3B(255, 255, 255));
        addChild(_moveLabel, 0);
        
        _timeLabel = LabelTTF::create("TIME:00:00", "ClarendonBT-Roman", getSizeWithDevice(20));
        _timeLabel->setColor(Color3B(255, 255, 255));
        addChild(_timeLabel, 0);
    }else{
        _scoreLabel->setString("SCORE:0");
        _moveLabel->setString("MOVES:0");
        _timeLabel->setString("TIME:00:00");
    }
    
    if(dummy) removeChild(dummy);
    
    dummy = MenuItemSprite::create(Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                             Sprite::create(getNameWithResolution("hand_icon").c_str()),
                                             this, menu_selector(BoardLayer::onDummy));
    dummy->setScale(0.5);
    dummy->setAnchorPoint(Vec2(0.5, 1));
    dummy->setPosition(Vec2(960, 540));
    addChild(dummy, 1000);
}

void BoardLayer::onDummy(Ref* sender)
{
    
}

void BoardLayer::updateLayoutWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _scoreLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    _scoreLabel->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(230.0f), getSizeWithDevice(35.0f)));
    
    _moveLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    _moveLabel->setPosition(Vec2(winSize.width/2.0f - getSizeWithDevice(90.0f), getSizeWithDevice(35.0f)));
    
    _timeLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    _timeLabel->setPosition(Vec2(winSize.width/2.0f + getSizeWithDevice(55.0f), getSizeWithDevice(35.0f)));
    
    updateCardSizeWithLandscape();
    updatePlayCellsWithLandscape();
    updateFreeCellsWithLandscape();
    updateGoalCellsWithLandscape();
    updateDealerWithLandscape();
    
    if(_startedGameFlag) schedule(schedule_selector(BoardLayer::setTime), 1.0f);
    
    if(_congratulationLayer != NULL)
    {
        _congratulationLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
        _congratulationLayer->setVisible(true);
    }
}

void BoardLayer::updateCardSizeWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
            _cardwidth = (winSize.width - getSizeWithDevice(SOLITAIRE_MARGIN_LAND + SOLITAIRE_LARGEPADDING_LAND) * 2
                          - getSizeWithDevice(SOLITAIRE_SMALLPADDING_LAND) * (_stacks - 1)) / (_stacks + 2);
            break;
        case TYPE_FREECELL:
            _cardwidth = (winSize.width - getSizeWithDevice(FREECELL_LARGEPADDING_LAND + FREECELL_MARGIN_LAND) * 2
                          - getSizeWithDevice(FREECELL_SMALLPADDING_LAND) * (_stacks - 1)) / (_stacks + 2);
            break;
        case TYPE_FORTY_THIEVES:
            _cardwidth = (winSize.width - getSizeWithDevice(FORTY_MARGIN_LAND) * 2
                          - getSizeWithDevice(FORTY_PADDING_LAND) * (_stacks - 1)) / _stacks;
            break;
        case TYPE_SPIDER:
            _cardwidth = (winSize.width - getSizeWithDevice(SPIDER_MARGIN_LAND) * 2
                          - getSizeWithDevice(SPIDER_PADDING_LAND) * (_stacks - 1)) / _stacks;
            break;
        default:
            return;
    }
    
    _cardheight = _cardwidth * 120.0f / 85.0f;
}

void BoardLayer::createPlayCells()
{
    if(playCells->data)
        playCells->removeAllObjects();
    
    for(int i = 0; i < _stacks; i++)
    {
        Deck* deck = Deck::create();
        deck->init(this);
        deck->setCardSpaceY(_playstackVerticalSpace);
        deck->setMaxCardSpace(12); //15
        deck->createSprite(g_strOtherCardSprites[0]);
        deck->setType(DECK_PLAY);
        addChild(deck);
        playCells->addObject(deck);
    }
}


void BoardLayer::updatePlayCellsWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    float startPositionX = 0.0f;
    float startPositionY = 0.0f;
    
    switch(GameData::getInstance()->getGameType())
    {
        case TYPE_SOLITAIRE:
            startPositionX = getSizeWithDevice(SOLITAIRE_MARGIN_LAND + SOLITAIRE_LARGEPADDING_LAND) + _cardwidth * 1.5f;
            startPositionY = winSize.height - getSizeWithDevice(SOLITAIRE_MARGIN_LAND) - _cardheight * 0.5f;
            break;
        case TYPE_FREECELL:
            startPositionX = getSizeWithDevice(FREECELL_MARGIN_LAND + FREECELL_LARGEPADDING_LAND) + _cardwidth * 1.5f;
            startPositionY = winSize.height - getSizeWithDevice(FREECELL_MARGIN_LAND) - _cardheight * 0.5f;
            break;
        case TYPE_FORTY_THIEVES:
            startPositionX = getSizeWithDevice(FORTY_MARGIN_LAND) + _cardwidth * 0.5f;
            startPositionY = winSize.height - getSizeWithDevice(FORTY_MARGIN_LAND) * 2 - _cardheight * 1.5f;
            break;
        case TYPE_SPIDER:
            startPositionX = getSizeWithDevice(SPIDER_MARGIN_LAND) + _cardwidth * 0.5f;
            startPositionY = winSize.height - getSizeWithDevice(SPIDER_MARGIN_LAND) - _cardheight * 0.5f;
            break;
    }
    
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*) playCells->getObjectAtIndex(i);
        deck->updateSprite(startPositionX, startPositionY, _cardwidth);
        deck->updateCardSprites(startPositionX, startPositionY, _cardwidth);
        deck->updateCardsWithoutAnimation();
        
        switch (GameData::getInstance()->getGameType())
        {
            case TYPE_SOLITAIRE:
                startPositionX += (_cardwidth + getSizeWithDevice(SOLITAIRE_SMALLPADDING_LAND));
                break;
            case TYPE_FREECELL:
                startPositionX += (_cardwidth + getSizeWithDevice(FREECELL_SMALLPADDING_LAND));
                break;
            case TYPE_FORTY_THIEVES:
                startPositionX += (_cardwidth + getSizeWithDevice(FORTY_PADDING_LAND));
                break;
            case TYPE_SPIDER:
                startPositionX += (_cardwidth + getSizeWithDevice(SPIDER_PADDING_LAND));
                break;
            default:
                break;
        }
    }
}

void BoardLayer::createFreeCells()
{
    freeCells->removeAllObjects();
    
    for(int i = 0;  i < _cells; i++)
    {
        Deck* deck = Deck::create();
        deck->init(this);
        deck->setCardSpaceY(0.001f);
        deck->setMaxCardSpace(15);
        deck->createSprite(g_strOtherCardSprites[0]);
        deck->setType(DECK_FREE);
        addChild(deck);
        freeCells->addObject(deck);
    }
}

void BoardLayer::updateFreeCellsWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
    {
        float startPositionX = getSizeWithDevice(FREECELL_MARGIN_LAND) + _cardwidth * 0.5f;
        if(GameData::getInstance()->isRightHanded()){
            startPositionX=winSize.width-startPositionX;
        }
        float startPositionY = winSize.height / 2 + (_cardheight + getSizeWithDevice(FREECELL_SMALLPADDING_LAND)) * 1.5f;
        
        for(int i = 0; i < freeCells->count(); i++)
        {
            Deck* deck = (Deck*) freeCells->getObjectAtIndex(i);
            deck->updateSprite(startPositionX, startPositionY, _cardwidth);
            deck->updateCardSprites(startPositionX, startPositionY, _cardwidth);//insert by KHJ 03/19/2015
            startPositionY -= (_cardheight + getSizeWithDevice(FREECELL_SMALLPADDING_LAND));
        }
    }
}

void BoardLayer::createGoalCells()
{
    goalCells->removeAllObjects();
    
    int suitCount = 0;
    if(GameData::getInstance()->getGameType() == TYPE_SPIDER)
        suitCount = 8;
    else
        suitCount = _suits;
    
    for(int i = 0;  i < suitCount; i++)
    {
        Deck* deck = Deck::create();
        deck->init(this);
        deck->setCardSpaceY(0.001f);
        deck->setMaxCardSpace(15);
        deck->createSprite(g_strOtherCardSprites[1]);
        deck->setType(DECK_GOAL);
        deck->setIndex(i);
        addChild(deck);
        goalCells->addObject(deck);
    }
}

void BoardLayer::updateGoalCellsWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    float startPositionX = 0.0f;
    float startPositionY = 0.0f;
    
    switch(GameData::getInstance()->getGameType())
    {
        case TYPE_SOLITAIRE:
            startPositionX = winSize.width - getSizeWithDevice(SOLITAIRE_MARGIN_LAND) - _cardwidth * 0.5f;
            if(GameData::getInstance()->isRightHanded()){
                startPositionX=winSize.width-startPositionX;
            }
            startPositionY = winSize.height / 2 + (_cardheight + getSizeWithDevice(SOLITAIRE_SMALLPADDING_LAND)) * 1.5f;
            break;
        case TYPE_FREECELL:
            startPositionX = winSize.width - getSizeWithDevice(FREECELL_MARGIN_LAND) - _cardwidth * 0.5f;
            if(GameData::getInstance()->isRightHanded()){
                startPositionX=winSize.width-startPositionX;
            }
            startPositionY = winSize.height / 2 + (_cardheight + getSizeWithDevice(FREECELL_SMALLPADDING_LAND)) * 1.5f;
            break;
        case TYPE_FORTY_THIEVES:
            startPositionX = winSize.width - getSizeWithDevice(FORTY_MARGIN_LAND) - _cardwidth * 0.5f;
            if(GameData::getInstance()->isRightHanded()){
                startPositionX=winSize.width-startPositionX;
            }
            startPositionY = winSize.height - getSizeWithDevice(FORTY_MARGIN_LAND) - _cardheight * 0.5f;
            break;
        case TYPE_SPIDER:
            //startPositionX = getSizeWithDevice(SPIDER_MARGIN_LAND + SPIDER_PADDING_LAND) + _cardwidth * 1.5f;
            startPositionX = getSizeWithDevice(SPIDER_MARGIN_LAND + 2*SPIDER_PADDING_LAND) + _cardwidth * 2.5f;
            startPositionY = getSizeWithDevice(LABEL_HEIGHT) + _cardheight * 0.5f;
            if(GameData::getInstance()->isRightHanded()){
                //landscape
                //startPositionX += (getSizeWithDevice(SPIDER_PADDING_LAND)+_cardwidth);
                startPositionX -= 2*(getSizeWithDevice(SPIDER_PADDING_LAND)+_cardwidth);
            }
            break;
    }
    
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* deck = (Deck*) goalCells->getObjectAtIndex(i);
        deck->updateSprite(startPositionX, startPositionY, _cardwidth);
        if(!_hasWon) deck->updateCardSprites(startPositionX, startPositionY, _cardwidth); //inserted by KHJ 03/19/2015
        switch (GameData::getInstance()->getGameType())
        {
            case TYPE_SOLITAIRE:
                startPositionY -= (_cardheight + getSizeWithDevice(SOLITAIRE_SMALLPADDING_LAND));
                
                break;
            case TYPE_FREECELL:
                startPositionY -= (_cardheight + getSizeWithDevice(FREECELL_SMALLPADDING_LAND));
                break;
            case TYPE_FORTY_THIEVES:
                if(GameData::getInstance()->isRightHanded())
                    startPositionX += (_cardwidth + getSizeWithDevice(FORTY_PADDING_LAND));
                else startPositionX -= (_cardwidth + getSizeWithDevice(FORTY_PADDING_LAND));
                
                break;
            case TYPE_SPIDER:
                startPositionX += (_cardwidth + getSizeWithDevice(SPIDER_PADDING_LAND));
                break;
            default:
                break;
        }
        
    }
}

void BoardLayer::createDealer()
{
    _dealer = Deck::create();
    _dealer->init(this);
    _dealer->cards->removeAllObjects();
    
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
    {
        _dealer->createSprite(g_strOtherCardSprites[2]);
        _dealer->setCardSpaceX(0.0f);
        _dealer->setCardSpaceY(0.0f);
        _dealer->setMaxCardSpace(20);
        _dealer->createCards(_suits);
        
        switch (GameData::getInstance()->getNewGame()) {
            case RANDOM_DEAL:
            {
                GameData::getInstance()->getCardIndexArray()->removeAllObjects();
                _dealer->shuffle(3);
            }
                break;
            case WINNING_DEAL:
            {
                int idx = arc4random() % 100;
                GameData::getInstance()->setSelectedGame(freecell_WinningDeal[idx]);
                
                GameData::getInstance()->getCardIndexArray()->removeAllObjects();
                _dealer->selectedShuffle();
            }
                break;
            case REPLAY_DEAL:
            {
                _dealer->selectedShuffle();
            }
                break;
            case SELECT_DEAL:
            {
                GameData::getInstance()->getCardIndexArray()->removeAllObjects();
                _dealer->selectedShuffle();
            }
                break;
            
        }
        
        addChild(_dealer);
    }
    else
    {
        _dealer->createSprite(g_strOtherCardSprites[2]);
        _dealer->setMaxCardSpace(20);
        _dealer->createCards(_suits);
        
        if(GameData::getInstance()->getNewGame() == REPLAY_DEAL){
            //REPLAY_DEAL
            _dealer->selectedShuffle();

        }
        else if(GameData::getInstance()->getNewGame() == WINNING_DEAL){
            
            GameData::getInstance()->getCardIndexArray()->removeAllObjects();
            
            switch (GameData::getInstance()->getGameType()) {
                case TYPE_SOLITAIRE:
                    if(GameData::getInstance()->isDrawFlag()){
                        int idx = arc4random() % 2;
                        GameData::getInstance()->setSelectedGame(draw3_WinningDeal[idx]);
                    }
                    else{
                        int idx = arc4random() % 2;
                        GameData::getInstance()->setSelectedGame(draw1_WinningDeal[idx]);
                    }
                    break;
                    
                case TYPE_FORTY_THIEVES:
                {
                    int idx = arc4random() % 2;
                    GameData::getInstance()->setSelectedGame(forty_WinningDeal[idx]);
                }
                    break;
                    
                case TYPE_SPIDER:
                    
                    if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY){
                        int idx = arc4random() % 2;
                        GameData::getInstance()->setSelectedGame(suit1_WinningDeal[idx]);
                    }
                    else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL){
                        int idx = arc4random() % 2;
                        GameData::getInstance()->setSelectedGame(suit2_WinningDeal[idx]);
                    }
                    
                    else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT)
                    {
                        int idx = arc4random() % 2;
                        GameData::getInstance()->setSelectedGame(suit3_WinningDeal[idx]);
                    }
                    else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_HARD){
                        int idx = arc4random() % 2;
                        GameData::getInstance()->setSelectedGame(suit4_WinningDeal[idx]);
                    }
                    break;
                    
                default:
                    break;
            }
            
            _dealer->winShuffle();
            
        }
        else{
            
            //Random deal
            GameData::getInstance()->getCardIndexArray()->removeAllObjects();
            _dealer->shuffle(3);
        }
            
        
        
        _dealer->flipAllCards();
        addChild(_dealer);
        
        if(GameData::getInstance()->getGameType() != TYPE_SPIDER)
        {
            _dealTo = Deck::create();
            _dealTo->init(this);
            _dealTo->setCardSpaceX(0.0f);
            _dealTo->setCardSpaceY(0.0f);
            _dealTo->setMaxCardSpace(64);
            _dealTo->createSprite(g_strOtherCardSprites[0]);
            _dealTo->setType(DECK_DEALTO);
            addChild(_dealTo);
        }
    }
}

void BoardLayer::drawDealer(float dt)
{
    //static int count = 0;
    if(GameData::getInstance()->isSoundEnabled()){
        
        MyObjectDoSomethingWith(this, std::string("deal.wav"));
    }
    
    if(_dealer->cards->count() > 0)
    {
        _dealer->draw((Deck*)playCells->getObjectAtIndex(count % playCells->count()), 1);
        count++;
    }
    else
    {
        unschedule(schedule_selector(BoardLayer::drawDealer));
        calculateDragableCards();
        GameData::getInstance()->setDoingAction(false);
    }
}

void BoardLayer::addCardsToPlayCell(float dt)
{
    CCLOG("dealer cards total = %zd", _dealer->cards->count());
    if(GameData::getInstance()->isSoundEnabled()){
        MyObjectDoSomethingWith(this, std::string("deal.wav"));
    }
    
    if(_dealer->cards->count() > 0)
    {
        if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE)
        {
            if(stack < _stacks)
            {
                //update by KHJ 03.28.2015
                _dealer->draw((Deck*)(playCells->getObjectAtIndex(index % playCells->count())), 1);
                index++;
                if(index == _stacks){
                      stack++;
                      index = stack;
                }
                
            }
            else
            {
                showLastCards();
            }
        }
        else if(GameData::getInstance()->getGameType() == TYPE_SPIDER ||
                GameData::getInstance()->getGameType() == TYPE_FORTY_THIEVES)
        {
            if(index < _maxPlayCards)
            {
                _dealer->draw((Deck*)playCells->getObjectAtIndex(index % playCells->count()), 1);
                index++;
            }
            else
            {
                showLastCards();
            }
        }
    }
    else
    {
        showLastCards();
    }
}

void BoardLayer::showLastCards()
{
    unschedule(schedule_selector(BoardLayer::addCardsToPlayCell));
    
    float time = 0.0f;
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
            time = 0.3f;
            break;
        case TYPE_SPIDER:
            time = 0.4f;
            break;
        case TYPE_FORTY_THIEVES:
            time = 0.4f;
            break;
        default:
            return;
    }
    
    schedule(schedule_selector(BoardLayer::flipLastCards), time);
}

void BoardLayer::flipLastCards(float dt)
{
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*) playCells->getObjectAtIndex(i);
        if(GameData::getInstance()->getGameType() == TYPE_SPIDER ||
           GameData::getInstance()->getGameType() == TYPE_SOLITAIRE)
        {
            Card* card = (Card*)deck->cards->getObjectAtIndex(deck->cards->count() - 1);
            if(!card->getVisible())
                card->setVisible(true);
        }
        else if(GameData::getInstance()->getGameType() == TYPE_FORTY_THIEVES)
        {
            for(int i = 0; i < deck->cards->count(); i++)
            {
                Card* card = (Card*)deck->cards->getObjectAtIndex(i);
                card->setVisible(true);
            }
        }
    }

    unschedule(schedule_selector(BoardLayer::flipLastCards));
    
    for(int i = 0; i < _dealer->cards->count(); i++)
    {
        Card* card = (Card*) _dealer->cards->getObjectAtIndex(i);
        card->setDragable(false);
    }
    
    calculateDragableCards();
    showTaskbar();
    GameData::getInstance()->setDoingAction(false);
}

void BoardLayer::showTaskbar()
{
    if(_parentLayer == NULL)
        return;
    
    ((GameLayer*)_parentLayer)->showTaskbar();
    
}

void BoardLayer::updateDealerWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    float startPositionX = 0.0f;
    float startPositionY = 0.0f;
    float dealToPosX = 0.0f;
    float dealToPosY = 0.0f;
    
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
            startPositionX = getSizeWithDevice(SOLITAIRE_MARGIN_LAND) + _cardwidth * 0.5f;
            if(GameData::getInstance()->isRightHanded()){
                startPositionX=winSize.width-startPositionX;
            }
            
            startPositionY = winSize.height / 2.0f - getSizeWithDevice(SOLITAIRE_SMALLPADDING_LAND) / 2.0f - _cardheight * 0.5f;
            dealToPosX = startPositionX;            
            dealToPosY = startPositionY + getSizeWithDevice(SOLITAIRE_SMALLPADDING_LAND) + _cardheight;
            _dealTo->updateSprite(dealToPosX, dealToPosY, _cardwidth);
            _dealTo->updateCardSprites(dealToPosX, dealToPosY, _cardwidth);//inserted by KHJ 03/19/2015
            _dealTo->showSprite(false);
            
            break;
        case TYPE_FREECELL:
            startPositionX = winSize.width/2.0f;
            startPositionY = getSizeWithDevice(LABEL_HEIGHT) + _cardheight * 0.5f;
            _dealer->showSprite(false);
            break;
        case TYPE_FORTY_THIEVES:
            startPositionX = getSizeWithDevice(FORTY_MARGIN_LAND) + _cardwidth * 0.5f;
            if(GameData::getInstance()->isRightHanded()){
                startPositionX=winSize.width-startPositionX;
            }
            startPositionY = winSize.height - getSizeWithDevice(FORTY_MARGIN_LAND) - _cardheight * 0.5f;
            
            dealToPosX = startPositionX + getSizeWithDevice(FORTY_PADDING_LAND) + _cardwidth;
            if(GameData::getInstance()->isRightHanded()){
                dealToPosX=startPositionX-getSizeWithDevice(FORTY_PADDING_LAND)-_cardwidth;
            }
            dealToPosY = startPositionY;
            _dealTo->updateSprite(dealToPosX, dealToPosY, _cardwidth);
            _dealTo->updateCardSprites(dealToPosX, dealToPosY, _cardwidth);//inserted by KHJ 03/19/2015
            _dealTo->showSprite(false);
            
            break;
        case TYPE_SPIDER:
            startPositionX = getSizeWithDevice(SPIDER_MARGIN_LAND) + _cardwidth * 0.5f;
            if(GameData::getInstance()->isRightHanded()){
                startPositionX=winSize.width-startPositionX;
            }
            //startPositionY = winSize.height / 2.0f;
            startPositionY = getSizeWithDevice(LABEL_HEIGHT) + _cardheight * 0.5f;
            break;
        default:
            return;
    }
    
    _dealer->updateSprite(startPositionX, startPositionY, _cardwidth);
    _dealer->updateCardSprites(startPositionX, startPositionY, _cardwidth);
    CCLOG("%f, %f", startPositionX, startPositionY);
}

void BoardLayer::calculateDragableCards()
{
    int maxMovableStackLimit = movableStackLimit(false);
    
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* playCell = (Deck*)playCells->getObjectAtIndex(i);
        bool correctOrder = true;
        int correctCount = 0;
        
        for(int j = playCell->cards->count() - 1; j >= 0; j--)
        {
            ((Card*)playCell->cards->getObjectAtIndex(j))->setDragable(correctOrder);
            
            if(correctOrder)
            {
                if((j != 0) &&
                   (!((Card*)playCell->cards->getObjectAtIndex(j-1))->getVisible() ||
                    (isWrongPlacement((Card*)playCell->cards->getObjectAtIndex(j), (Card*)playCell->cards->getObjectAtIndex(j-1))) ||
                    (correctCount >= (maxMovableStackLimit - 1))))
                {
                    correctOrder = false;
                }
                
                correctCount++;
            }
        }
    }
    
    for(int i = 0; i < freeCells->count(); i++)
    {
        Deck* freecell = (Deck*) freeCells->getObjectAtIndex(i);
        Card* topcard = (Card*) freecell->getTopCard();
        if(topcard != NULL)
            topcard->setDragable(true);
    }
    
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* goalcell = (Deck*) goalCells->getObjectAtIndex(i);
        Card* topcard = (Card*) goalcell->getTopCard();
        if(topcard != NULL)
            topcard->setDragable(true);
    }
    
    _gameFirstStarted = true;
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
}

int BoardLayer::movableStackLimit(bool isTargetEmptyPlayCell)
{
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
        return (1 + countEmpty(freeCells)) * (int)pow(2, countEmpty(playCells) - (isTargetEmptyPlayCell ? 1 : 0));
    else
        return 104;
}

int BoardLayer::countEmpty(__Array* decks)
{
    int result = 0;
    for(int i = 0; i < decks->count(); i++)
    {
        Deck* deck = (Deck*)decks->getObjectAtIndex(i);
        if(deck->cards->count() == 0)
            result++;
    }
    
    return result;
}

bool BoardLayer::isWrongPlacement(Card* card1, Card* card2)
{
    int gameType = GameData::getInstance()->getGameType();
    if(gameType == TYPE_FREECELL || gameType == TYPE_SOLITAIRE)
    {
        if((card1->getColor() != card2->getColor()) && ((card1->getRank() + 1) == card2->getRank()))
            return false;
        else
            return true;
    }
    else if(gameType == TYPE_SPIDER)
    {
        if((card1->getSuit() == card2->getSuit()) && ((card1->getRank() + 1) == card2->getRank()))
            return false;
        else
            return true;
    }
    
    return true;
}

bool BoardLayer::pressesBegan()
{
    if(_isSetting)
        return false;
    
    bTouchBegan = !bTouchBegan;
    
    _draggingCard = getSelectedCard(lastMovedPoint);
    if(_draggingCard == NULL)
    {
        int width = ((GameLayer*)_parentLayer)->_taskbarLayer->getContentSize().width;
        int height = ((GameLayer*)_parentLayer)->_taskbarLayer->getContentSize().height;
        cocos2d::Rect taskbarRect = cocos2d::Rect(0, 0, width, height);
        if(taskbarRect.containsPoint(lastMovedPoint) && ((GameLayer*)_parentLayer)->_isShowTaskbar)
        {
            ((GameLayer*)_parentLayer)->_taskbarLayer->pressesBegan(lastMovedPoint);
        }
        else{
            showTaskbar();
        }
    }
    else
    {
        Deck* deck = _draggingCard->getDeck();
        for(long i = deck->cards->getIndexOfObject(_draggingCard); i < deck->cards->count(); i++)
        {
            Card* card = (Card*)deck->cards->getObjectAtIndex(i);
            card->touchBegan(lastMovedPoint);
        }
    }
    return true;
}

bool BoardLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    prevPoint = touch->getLocation();
    return true;
}

void BoardLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(_isSetting) return;
    
    Director* director = Director::getInstance();
    Point location = touch->getLocationInView();
    location = director->convertToGL(location);
    
    //added by ccl
    Vec2 delta = location - prevPoint;
    lastMovedPoint += delta;
    //lastMovedPoint = location;
    
    log("touch move: %f, %f", location.x, location.y);
    if(_draggingCard != NULL)
    {
        _draggingCard->touchMoved(lastMovedPoint);
    }
    
    dummy->setPosition(lastMovedPoint);
    prevPoint = location;//added ccl
}

void BoardLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
//    bTouchBegan = false;
//    
//    Director* director = Director::getInstance();
//    Point location = touch->getLocationInView();
//    location = director->convertToGL(location);

    
    if(_draggingCard != NULL)
    {
        Deck* deck = _draggingCard->getDeck();
        for(long i = deck->cards->getIndexOfObject(_draggingCard); i < deck->cards->count(); i++)
        {
            Card* card = (Card*)deck->cards->getObjectAtIndex(i);
            card->touchEnded(lastMovedPoint);
        }
        _draggingCard = NULL;
    }
}


Card* BoardLayer::getSelectedCard(Point touchPoint)
{
    Card* result = NULL;
    _isPlayCellTap=false;
    
    for(int i = 0; i < playCells->count(); i++)
    {
        int topOrder = -1;
        Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
        for(int j = 0; j < deck->cards->count(); j++)
        {
            Card* card = (Card*)deck->cards->getObjectAtIndex(j);
            Sprite* sprite = card->getSprite();
            if(sprite->getBoundingBox().containsPoint(touchPoint))
            {
                if(card->getLocalZOrder() > topOrder)
                {
                    _isPlayCellTap=true;
                    topOrder = sprite->getLocalZOrder();
                    result = card;
                }
            }
        }
        
        if(result != NULL)
            return result;
    }
    
    if(_dealer->hasCards()){
        Card* card = (Card*)_dealer->cards->getLastObject();
        Sprite* sprite = card->getSprite();
        if(sprite->getBoundingBox().containsPoint(touchPoint))
        {
            if(GameData::getInstance()->isSoundEnabled()){
                MyObjectDoSomethingWith(this, std::string("card_shuffle.mp3"));
            }
            result = card;
            return result;
        }
    }
    
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
    {
        for(int i = 0; i < freeCells->count(); i++)
            {
                Deck* deck = (Deck*)freeCells->getObjectAtIndex(i);
                if(deck->hasCards())
                {
                    Card* card=deck->getTopCard();
                    
                    Sprite* sprite = card->getSprite();
                    if(sprite->getBoundingBox().containsPoint(touchPoint))
                    {
                        result = card;
                        return result;
                    }
                }
            }
        
    }

    if(_dealTo!=NULL){
        
        if(_dealTo->hasCards()){//solitaire            
            Card* card=_dealTo->getTopCard();
            Sprite* sprite = card->getSprite();
            
            if(sprite->getBoundingBox().containsPoint(touchPoint))
            {
                result = card;
                return result;
            }
            
            if(!_dealer->hasCards()) {
                doDealToMove(_dealer);
            }

        }
    }
    
    return result;
}

Deck* BoardLayer::getNearDeck()
{
    Deck* result = NULL;
    float nearDistance = 0.0f;
    Point point = Vec2(0, 0);
    
    if(_draggingCard == NULL)
        return result;
    
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
        
        if(deck->getTopCard() == NULL)
        {
            point = deck->getSprite()->getPosition();
        }
        else
        {
            Card* topCard = (Card*)deck->getTopCard();
            point = topCard->getSprite()->getPosition();
            if(topCard == _draggingCard)
                continue;
        }
        
        float distance = point.getDistanceSq(_draggingCard->getSprite()->getPosition());
        if(nearDistance == 0.0f)
        {
            nearDistance = distance;
            result = deck;
        }
        else
        {
            if(distance < nearDistance)
            {
                nearDistance = distance;
                result = deck;
            }
        }
    }
    
    //---add by KHJ 03.28.2015---//
    if(GameData::getInstance()->getGameType()!=TYPE_SPIDER)
    {
        for(int i = 0; i<goalCells->count(); i++)
        {
            Deck* deck = (Deck*)goalCells->getObjectAtIndex(i);
            point = deck->getSprite()->getPosition();
            
            float distance = point.getDistanceSq(_draggingCard->getSprite()->getPosition());
            if(nearDistance == 0.0f)
            {
                nearDistance = distance;
                result = deck;
            }
            else
            {
                if(distance < nearDistance)
                {
                    nearDistance = distance;
                    result = deck;
                }
            }
            
        }
    }
    
    if(freeCells!=NULL)
    {
        for(int i = 0; i<freeCells->count(); i++)
        {
            Deck* deck = (Deck*)freeCells->getObjectAtIndex(i);
            point = deck->getSprite()->getPosition();
            
            float distance = point.getDistanceSq(_draggingCard->getSprite()->getPosition());
            if(nearDistance == 0.0f)
            {
                nearDistance = distance;
                result = deck;
            }
            else
            {
                if(distance < nearDistance)
                {
                    nearDistance = distance;
                    result = deck;
                }
            }

        }
    }
    return result;
}

bool BoardLayer::CardDrag(Card* card, Deck* targetDeck)
{
    int gameType = GameData::getInstance()->getGameType();
    
    if(card->getDeck() != targetDeck)
    {
        bool isSingleCard = (card->getDeck()->getTopCard() == card);
        
        if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
        {
            for(int i = 0; i < freeCells->count(); i++)
            {
                Deck* deck = (Deck*)freeCells->getObjectAtIndex(i);
                if(deck == targetDeck)
                {
                    if(isSingleCard && targetDeck->cards->count() == 0)
                    {
                        _actuallyCardMoved = true;
                        doMove(Move::single(card, targetDeck));
                        return true;
                    }
                }
            }
            
            if(_freecellOnlyKing && targetDeck->getType() == DECK_PLAY && !targetDeck->hasCards()){
                if(card->getRank() != CARDRANK_KING) _freecellOnlyKing = false;
            }
        }
        
        for(int i = 0; i < playCells->count(); i++)
        {
            Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
            if(deck == targetDeck)
            {
                if(gameType == TYPE_FREECELL)
                {
                    if(targetDeck->cards->count() == 0 ||
                       ((targetDeck->getTopCard()->getColor() != card->getColor()) &&
                        (card->getRank() + 1 == targetDeck->getTopCard()->getRank())))
                    {
                        if(doStackMove(card, targetDeck))
                            return true;
                    }
                    
                }
                else if(gameType == TYPE_SOLITAIRE)
                {
                    if(targetDeck->cards->count() == 0)
                    {
                        if(card->getRank() == CARDRANK_KING)
                        {
                            doStackMove(card, targetDeck);
                            return true;
                        }
                    }
                    else
                    {
                        if(targetDeck->getTopCard()->getColor() != card->getColor() &&
                           card->getRank() + 1 == targetDeck->getTopCard()->getRank())
                        {
                            doStackMove(card, targetDeck);
                            return true;
                        }
                    }
                }
                else if(gameType == TYPE_SPIDER)
                {
                    if(targetDeck->cards->count() == 0 || (card->getRank() + 1 == targetDeck->getTopCard()->getRank()))
                    {
                        if(doStackMove(card, targetDeck))
                            return true;
                    }
                }
                else if(gameType == TYPE_FORTY_THIEVES)
                {
                    if(targetDeck->cards->count() == 0 ||
                       (card->getSuit() == targetDeck->getTopCard()->getSuit() &&
                        card->getRank() + 1 == targetDeck->getTopCard()->getRank()))
                    {
                        if(doStackMove(card, targetDeck))
                            return true;
                    }
                }
            }
        }
        
        if(gameType != TYPE_SPIDER)
        {
            for(int i = 0; i < goalCells->count(); i++)
            {
                Deck* deck = (Deck*)goalCells->getObjectAtIndex(i);
                if(deck == targetDeck)
                {
                    if(isSingleCard)
                    {
                        if(targetDeck->cards->count() == 0)
                        {
                            if(card->getRank() == CARDRANK_ACE)
                            {
                                _actuallyCardMoved = true;
                                doMove(Move::single(card, targetDeck));
                                return true;
                            }
                        }
                        else
                        {
                            if(targetDeck->getTopCard()->getSuit() == card->getSuit() &&
                               card->getRank() - 1 == targetDeck->getTopCard()->getRank())
                            {
                                _actuallyCardMoved = true;
                                doMove(Move::single(card, targetDeck));
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

void BoardLayer::doMove(Move* move)
{
    if(GameData::getInstance()->isSoundEnabled()){
        
        MyObjectDoSomethingWith(this, std::string("card_tick.mp3"));
    }
    
    if(!_startedGameFlag)
    {
        _startTime = 0;//getCurrentTime();
        _tempTime = 0;//getCurrentTime();
        _stageTime = 0;//getCurrentTime();
        _tempTime1 = 0;//getCurrentTime();
        
        schedule(schedule_selector(BoardLayer::setTime), 1.0f);
    }
    
    //if(isScheduled(schedule_selector(BoardLayer::setTime))) CCLog("%s", "scheduled true");
  
    _startedGameFlag = true;
    
    GameData::getInstance()->setUndoMove(false);
    
    move->execute();
    moves->addObject(move);
    
    _totalMoveCount++;
    _tempTime1=_tempTime;
    
    if(GameData::getInstance()->getGameType() != TYPE_FREECELL)
        showCardFace();
    
    else
    {
        if(_freecellUseCount<4){
            
            int currentFreecell = 0;
            for(int i=0; i<freeCells->count();i++){
                Deck* freeDeck= (Deck*) freeCells->getObjectAtIndex(i);
                if(freeDeck->hasCards()) currentFreecell++;
            }
            
            if(currentFreecell >_freecellUseCount) _freecellUseCount = currentFreecell;
        }
        
        if(_freecellOneCard){
            //Move stack or Multi false
            if(move->getMoveType() == 1 || move->getMoveType() == 3) _freecellOneCard = false;
        }
    }
    
    //if(moves->count()>3){//Limit move history & undo count
    //    for(int i=0; i<moves->count()-3;i++){
    //        moves->removegetObjectAtIndex(i);
    //    }
   // }
    
    checkCompletePlaycells();//spider
    showScore();
    
    if(!_hasWon)
    {
        calculateDragableCards();
        if(GameData::getInstance()->getGameType() == TYPE_FREECELL && !_isAutocompleteRunning)
            checkForFoundationMoves(false);
        
        checkWin();
    }
    
}

bool BoardLayer::doStackMove(Card* card, Deck* targetDeck)
{
    long stackSize = card->getDeck()->cards->count() - card->getDeck()->cards->getIndexOfObject(card);
    int limit = movableStackLimit(targetDeck->cards->count() == 0);
    if(stackSize <= limit)
    {
        if(targetDeck != _dealTo)
        {
            Move* move = Move::stack(card->getDeck(), targetDeck);
            for(long i = card->getDeck()->cards->getIndexOfObject(card); i < card->getDeck()->cards->count(); i++)
                move->cards->addObject((Card*)card->getDeck()->cards->getObjectAtIndex(i));
            _actuallyCardMoved = true;
            doMove(move);
            return true;
        }
        else
        {
            if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE && _solitaireAllFace == 0){
                
                for(int i = 1; i<playCells->count(); i++){
                    Deck* playDeck = (Deck*) playCells->getObjectAtIndex(i);
                    
                    if(playDeck->hasCards() && !playDeck->getBottomCard()->getChangedVisible()){
                        _solitaireAllFace = 1;
                        break;
                    }
                }
                
                if(_solitaireAllFace == 0) _solitaireAllFace = 2;
                
                for(int i = 0; i<goalCells->count(); i++){
                    Deck* goalDeck = (Deck*)goalCells->getObjectAtIndex(i);
                    
                    if(!goalDeck->hasCards()){
                        _solitaireAllAces = false;
                        break;
                    }
                }
                
            }
            
            Move* move = Move::stack(card->getDeck(), targetDeck);
            int moveCount = GameData::getInstance()->isDrawFlag() ? 3 : 1;
            
            if(GameData::getInstance()->getGameType() == TYPE_FORTY_THIEVES)
                moveCount = 1;
            
            if(card->getDeck()->cards->count() < moveCount)
                moveCount = card->getDeck()->cards->count();
            
            ///////////////// update by khj 3.6            
            
            if(moveCount==1)
                    move->cards->addObject(card);
                
            else{
                long current;
                for(int i = 0; i < moveCount; i++){
                    current=card->getDeck()->cards->getIndexOfObject(card);
                    move->cards->addObject((Card*)_dealer->cards->getObjectAtIndex(current-i));
                }
            }
            
            doMove(move);
            if(_dealer->cards->count() == 0)
                _dealer->updateSpriteWithEmpty();
            
            
            //for(int i = card->getDeck()->cards->count() - 1; i >= card->getDeck()->cards->count() - moveCount; i--)
                //move->cards->addObject((Card*)card->getDeck()->cards->getObjectAtIndex(i));
            
            //doMove(move);
            
            //////////////////
            return true;
        }
    }
    
    return false;
}

void BoardLayer::doStackMove1(Card* card)
{
    //spider dealer
    
    //playcell is full?
    for(int i = 0; i<playCells->count();i++)
    {
        Deck* deck = (Deck*) playCells->getObjectAtIndex(i);
        if(!deck->hasCards())
        {
            MessageBox("You can't deal new cards while there is empty space", "Spider Solitaire");
            return;
        }
    }
    
    int index = 0;
    for(long i = _dealer->cards->count() - 1; ; i--)
    {
        if(index >= 10)
            break;
        
        doMove(Move::single((Card*)_dealer->cards->getObjectAtIndex(i), (Deck*)playCells->getObjectAtIndex(index)));
        index++;
    }
    
    //moves->removeAllObjects();
    
    if(_dealer->cards->count() == 0)
        _dealer->updateSpriteWithEmpty();
}

bool BoardLayer::doDealToMove(Deck* deck)// dealer reset
{
    if(_dealsLeftCount <= 0)
        return false;
    
    if(deck->getType() == DECK_DEALER && !deck->hasCards())
    {
        Move* move = Move::stack(_dealTo, deck);
        for(long i = _dealTo->cards->count() - 1; i >= 0; i--)
            move->cards->addObject((Card*)_dealTo->cards->getObjectAtIndex(i));
        doMove(move);
        return true;
    }
    
    return false;
}

void BoardLayer::doubleClick(Card* card)
{
    if(!GameData::getInstance()->isTapMove() && _isPlayCellTap) return;
    
    if(card->getDragable())
    {
        if(GameData::getInstance()->getGameType() != TYPE_SPIDER)
        {
            if(card->getDeck()->getTopCard() == card)
            {
                if(card->getRank() == CARDRANK_ACE)
                {
                    for(int i = 0; i < goalCells->count(); i++)
                    {
                        Deck* goalDeck = (Deck*)goalCells->getObjectAtIndex(i);
                        if(!goalDeck->hasCards())
                        {
                            _actuallyCardMoved = true;
                            doMove(Move::single(card, goalDeck));
                            return;
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < goalCells->count(); i++)
                    {
                        Deck* goalDeck = (Deck*)goalCells->getObjectAtIndex(i);
                        if(goalDeck->hasCards() && goalDeck->getTopCard()->getSuit() == card->getSuit() &&
                           goalDeck->getTopCard()->getRank() == card->getRank() - 1)
                        {
                            _actuallyCardMoved = true;
                            doMove(Move::single(card, goalDeck));
                            return;
                        }
                    }
                }
            }
        }
        
        int _spiderSuitGoal = 20;
        for(int i = 0; i < playCells->count(); i++)
        {
            Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
            
            if(GameData::getInstance()->getGameType() == TYPE_FREECELL ||
               GameData::getInstance()->getGameType() == TYPE_SOLITAIRE)
            {
                if(deck != card->getDeck() && deck->hasCards() &&
                   deck->getTopCard()->getRank() == card->getRank() + 1 &&
                   deck->getTopCard()->getColor() != card->getColor())
                {
                    if(doStackMove(card, deck))
                        return;
                }
            }
            else if(GameData::getInstance()->getGameType() == TYPE_SPIDER)
            {
                if(deck != card->getDeck() && deck->hasCards() && deck->getTopCard()->getRank() == card->getRank() + 1)
                {
                    //updated by KHJ 04/08/2015
                    if(card->getSuit()==deck->getTopCard()->getSuit())
                    {
                        if(doStackMove(card, deck))
                            return;
                    }
                    else
                    {
                        _spiderSuitGoal = i;
                    }
                    //
                }
            }
            else
            {
                if(deck != card->getDeck() && deck->hasCards() &&
                   deck->getTopCard()->getRank() == card->getRank() + 1 &&
                   deck->getTopCard()->getSuit() == card->getSuit())
                {
                    if(doStackMove(card, deck))
                        return;
                }
            }
        }
        
        //added by KHJ 04/08/2015
        if(_spiderSuitGoal<20)
        {
            Deck* deck = (Deck*)playCells->getObjectAtIndex(_spiderSuitGoal);
            if(doStackMove(card, deck))
                return;
        }
        //
   
        for(int i = 0; i < playCells->count(); i++)
        {
            Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
            if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE)
            {
                if(!deck->hasCards() && card->getRank() == CARDRANK_KING)
                {
                    if(doStackMove(card, deck))
                        return;
                }
            }
            else
            {
                if(!deck->hasCards())
                {
                    if(GameData::getInstance()->getGameType() == TYPE_FREECELL && _freecellOnlyKing){
                        if(card->getRank() != CARDRANK_KING) _freecellOnlyKing = false;
                    }
                    
                    if(doStackMove(card, deck))
                        return;
                }
            }
        }
        
        if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
        {
            if(card->getDeck()->getTopCard() == card && card->getDeck()->getType() != DECK_FREE)
            {
                for(int i = 0; i < freeCells->count(); i++)
                {
                    Deck* deck = (Deck*)freeCells->getObjectAtIndex(i);
                    if(!deck->hasCards())
                    {
                        _actuallyCardMoved = true;
                        doMove(Move::single(card, deck));
                        return;
                    }
                }
            }
        }
    }
}

void BoardLayer::showCardFace()
{
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
        if(deck->cards->count() >= 1)
        {
            if(!deck->getTopCard()->getVisible())
            {
                deck->getTopCard()->setVisible(true);
                deck->getTopCard()->setChangedVisible(true);
            }
        }
        deck->updateCardsWithAnimation();
    }
    
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* deck = (Deck*)goalCells->getObjectAtIndex(i);
        for(int j = 0; j < deck->cards->count(); j++)
        {
            Card* card = (Card*)deck->cards->getObjectAtIndex(j);
            if(!card->getVisible())
            {
                card->setVisible(true);
                if(GameData::getInstance()->getGameType() != TYPE_SPIDER)
                    card->setDragable(true);
                else
                    card->setDragable(false);
            }
        }
    }
    
    if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE ||
       GameData::getInstance()->getGameType() == TYPE_FORTY_THIEVES)
    {
        if(_dealTo->cards->count() > 0)
        {
            if(!_dealTo->getTopCard()->getDragable())
                _dealTo->getTopCard()->setDragable(true);
            _dealTo->updateCardsWithAnimation();
        }
        
        for(int i = 0; i < _dealTo->cards->count(); i++)
            ((Card*)_dealTo->cards->getObjectAtIndex(i))->setVisible(true);
    }
    
    for(int i = 0; i < _dealer->cards->count(); i++)
    {
        ((Card*)_dealer->cards->getObjectAtIndex(i))->setVisible(false);
        ((Card*)_dealer->cards->getObjectAtIndex(i))->setDragable(false);
    }
}

void BoardLayer::showScore()
{
    if(!GameData::getInstance()->isVegasMode())
    {
        _gameScore = 0;
    }
    else
    {
        if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE)
            _gameScore = -52;
    }
    
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* deck = (Deck*)goalCells->getObjectAtIndex(i);
        if(deck->cards->count() > 0)
            _gameScore = _gameScore + 5 * deck->cards->count();
    }
    
    _gameScore = _gameScore - _cuttingScore;
    
    //add by khj 3.9.2015
    std::string temp="SCORE:"+to_string((int)_gameScore);
    _scoreLabel->setString(temp.c_str());
    
    if(GameData::getInstance()->getTimeMove()){
        std::string temp="MOVES:"+to_string(_totalMoveCount);
        const char *label=temp.c_str();
        _moveLabel->setString(label);
        
        temp="TIME:" + getTime();        
        _timeLabel->setString(temp.c_str());
    }
}

void BoardLayer::checkCompletePlaycells()
{    
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
        
        if(checkPlayCell(deck))
        {
            doCompleteDeckMove(deck);
        }
        
    }
}

bool BoardLayer::checkPlayCell(Deck* deck)
{
    if(deck->hasCards())
    {
        if(deck->cards->count() >= 13 && deck->getTopCard()->getRank() == CARDRANK_ACE)
        {
            for(long i = deck->cards->count() - 1; i > deck->cards->count() - 13; i--)
            {
                Card* card = (Card*)deck->cards->getObjectAtIndex(i);
                Card* prevCard = (Card*)deck->cards->getObjectAtIndex(i-1);
                if(!prevCard->getVisible() || isWrongPlacement(card, prevCard))
                    return false;
            }
            return true;
        }
    }
    
    return false;
}

bool BoardLayer::doCompleteDeckMove(Deck* deck)//Exception
{
    //Deck* targetDeck = NULL;
    
    int goalDeckIndex = -1;
    
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* goalDeck = (Deck*)goalCells->getObjectAtIndex(i);
        if(goalDeck->cards->count() == 0)
        {
            goalDeckIndex=i;
            //targetDeck = goalDeck;//Exception
            break;
        }
    }
    
    if(goalDeckIndex < 0)
        return false;
    
    Move* move = Move::stack(deck, ((Deck*)goalCells->getObjectAtIndex(goalDeckIndex)));
    //Move* move = Move::stack(deck, targetDeck));
    
    for(long i = deck->cards->count() - 1; i >= deck->cards->count() - 13; i--)
    {
        if(i<0) break;
        move->cards->addObject((Card*)deck->cards->getObjectAtIndex(i));
    }
    
    if(move->cards->count()==0) return false;
    
    doMove(move);
    
    move->release();
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* deck1 = (Deck*)goalCells->getObjectAtIndex(i);
        for(int i = 0; i < deck1->cards->count(); i++)
            ((Card*)deck1->cards->getObjectAtIndex(i))->setDragable(false);
    }
    
    moves->removeAllObjects();
    
    return true;
}

void BoardLayer::checkForFoundationMoves(bool onlySafe)
{
    _isAutocompleteRunning = true;
    bool recurse = false;
    
    if(freeCells != NULL){
        for(int i = 0; i < freeCells->count(); i++)
        {
            Deck* deck = (Deck*)freeCells->getObjectAtIndex(i);
            if(checkDeck(deck, onlySafe))
                recurse = true;
        }
    }
    
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
        if(checkDeck(deck, onlySafe))
            recurse = true;
    }
    
    if(recurse && !_hasWon)
        checkForFoundationMoves(onlySafe);
    else
        _isAutocompleteRunning = false;
}

bool BoardLayer::checkDeck(Deck* deck, bool onlySafe)
{
    if(deck->hasCards())
    {
        Card* cardToMove = (Card*)deck->getTopCard();
        Deck* goalDeck = getGoalDeckForCard(cardToMove);
        if(goalDeck != NULL)
        {
            if(!onlySafe || isCardSafeToMove(cardToMove))
            {
                _actuallyCardMoved = true;
                doMove(Move::single(deck->getTopCard(), goalDeck));
                return true;
            }
        }
    }
    
    return false;
}

bool BoardLayer::isCardSafeToMove(Card* cardToMove)
{
    int rank = cardToMove->getRank() - 1;
    int color = (cardToMove->getColor() == CARDCOLOR_BLACK) ? CARDCOLOR_RED : CARDCOLOR_BLACK;
    
    for(int i = 0; i < playCells->count(); i++)
    {
        Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
        if(deck->hasColor(rank, color))
            return false;
    }
    
    for(int i = 0; i < freeCells->count(); i++)
    {
        Deck* deck = (Deck*)freeCells->getObjectAtIndex(i);
        if(deck->hasColor(rank, color))
            return false;
    }
    
    return true;
}

Deck* BoardLayer::getGoalDeckForCard(Card* card)
{
    if(GameData::getInstance()->getGameType() != TYPE_SPIDER)
    {
        
        for(int i = 0; i < goalCells->count(); i++)
        {
            Deck* goalDeck = (Deck*)goalCells->getObjectAtIndex(i);
            if(!goalDeck->hasCards() && card->getRank() == CARDRANK_ACE)
                return goalDeck;
            
            if(goalDeck->hasCards() && goalDeck->getTopCard()->getSuit() == card->getSuit() &&
               goalDeck->getTopCard()->getRank() == card->getRank() - 1)
                return goalDeck;
        }
        
        
        //---Update by KHJ 03.27.2015---//
        int goalDeckIdx = 0;
        
        for(int i = 0; i< goalCells->count();i++){
            Deck* goalDeck = (Deck*)goalCells->getObjectAtIndex(i);
            if(!goalDeck->hasCards() && card->getRank() == CARDRANK_ACE)
                return goalDeck;
            
            if(goalDeck->hasCards() && goalDeck->getTopCard()->getSuit() == card->getSuit() &&
               goalDeck->getTopCard()->getRank() == card->getRank() - 1){
                
                if(GameData::getInstance()->getGameType()==TYPE_FORTY_THIEVES) return goalDeck;
                
                goalDeckIdx =10 + i;
                break;
            }
        }
        
        if(goalDeckIdx == 0)  return NULL;
        
        for(int i = 0; i< goalCells->count();i++){
            Deck* goalDeck = (Deck*)goalCells->getObjectAtIndex(i);
            if(!goalDeck->hasCards()) return NULL;
            
            if(goalDeck->getTopCard()->getRank() < card->getRank() - 1){
                return NULL;
            }
        }
        
        return (Deck*)goalCells->getObjectAtIndex(goalDeckIdx-10);
        //--------------//
    }
    
    return NULL;
}

bool BoardLayer::checkWin()
{
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* deck = (Deck*)goalCells->getObjectAtIndex(i);
        if(deck->cards->count() < 13)
            return false;
    }
    
    win();
    
    return true;
}

void BoardLayer::win()
{
    if(_hasWon) return;
    
    _hasWon = true;
    unschedule(schedule_selector(BoardLayer::setTime));
    
    _isSetting = true; //taskbar disable
    
    for(int i = 0; i < goalCells->count(); i++)
    {
        Deck* deck = (Deck*)goalCells->getObjectAtIndex(i);
        for(int j = 0; j < deck->cards->count(); j++)
            ((Card*)deck->cards->getObjectAtIndex(j))->setDragable(false);
    }
    
    moves->removeAllObjects();
    
    _gameScore = _gameScore + 5000/_totalMoveCount + 5000/_stageTime;
    
    if(_totalUndoCount == 0)
        _gameScore +=500;
    else _gameScore += 400/_totalUndoCount;
    
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL){
        if(_freecellUseCount == 0)
            _gameScore += 500;
        else if(_freecellUseCount<4) _gameScore += 300/_freecellUseCount;
    }
    
    if(GameData::getInstance()->getNewGame() == RANDOM_DEAL)
        _gameScore += 50;
    
    std::string temp="SCORE:"+to_string(_gameScore);
    _scoreLabel->setString(temp.c_str());
    
    saveGameStatus();
    submitScore();
    submitAchieve();
    
    ////added by amr
//    switch (GameData::getInstance()->getGameType()) {
//        case TYPE_SOLITAIRE:
//        {
//            if(GameData::getInstance()->isDrawFlag()){
//                AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Solitaire Draw 3 Win Screen", 1);
//            }else{
//                AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Solitaire Draw 1 Win Screen", 1);
//            }
//            
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "Solitaire Win", 1);//added by amr
//        }
//            break;
//            
//        case TYPE_FREECELL:
//        {
//            AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Freecell Win Screen", 1);
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "FreeCell Win", 1);//added by amr
//        }
//            break;
//            
//        case TYPE_FORTY_THIEVES:
//        {
//            AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Forty Thieves Win Screen", 1);
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "Forty Thieves Win", 1);//added by amr
//        }
//            break;
//            
//        case TYPE_SPIDER:
//        {
//            if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY){
//                AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Spider Solitaire 1 Suit Win Screen", 1);
//            }
//            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL){
//                AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Spider Solitaire 2 Suit Win Screen", 1);
//            }
//            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT){
//                AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Spider Solitaire 3 Suit Win Screen", 1);
//            }
//            else{
//                AppDelegate::get()->sendMessageToNative(MSG_GOOGLE_ANALYTICS, "Spider Solitaire 4 Suit Win Screen", 1);
//            }
//            AppDelegate::get()->sendMessageToNative(MSG_ASKINGPOINT, "Spider Solitaire Win", 1);//added by amr
//        }
//            break;
//    }
    ////added by amr
    
    //AppDelegate::get()->sendMessageToNative(MSG_APPIRATER, getGameString().c_str(), 1);
    
    //Card Animation Position
    _winAnimationCount = 0;
    
    Size winSize = Director::getInstance()->getWinSize();
    
    float length = winSize.width < winSize.height ? winSize.width : winSize.height;
    length = length/2.0f - getSizeWithDevice(90.0f);
    
    long num = cards->count() / 6 ;
    Point targetPosition;
    
    //GameData::getInstance()->setDoingAction(true);
    
    for(int i=0; i<cards->count();i++)
    {
        Card* card=(Card*)cards->getObjectAtIndex(i);
        card->setOrder(i);
        
        switch (i/num) {//root(3)/2=0.8686
            case 0:
                targetPosition = getTargetPositon(Vec2(-length/2, 0.8686*length), Vec2(length/2, 0.8686*length), i% num, num);
                break;
            case 1:
                targetPosition = getTargetPositon(Vec2(length/2, 0.8686*length), Vec2(length, 0), i % num, num);
                break;
            case 2:
                targetPosition = getTargetPositon(Vec2(length, 0), Vec2(length/2, -0.8686*length), i % num, num);
                break;
            case 3:
                targetPosition = getTargetPositon(Vec2(length/2, -0.8686*length), Vec2(-length/2, -0.8686*length), i % num, num);
                break;
            
            case 4:
                targetPosition = getTargetPositon(Vec2(-length/2, -0.8686*length), Vec2(-length, 0), i % num, num);
                break;
                
            case 5:
                targetPosition = getTargetPositon(Vec2(-length, 0), Vec2(-length/2, 0.8686*length), i % num, num);
                break;
                
            default:
                card->setLocalZOrder(0);
                break;
        }
        
        card->setOrder(i);
        card->getSprite()->stopAllActions();
        
        if(GameData::getInstance()->getGameType() != TYPE_SOLITAIRE){
            MoveTo* action = MoveTo::create(0.25f, targetPosition);
            //card->getSprite()->runAction(Sequence::create(action, CC_CALLBACK_2(BoardLayer::didWinAnimation, this, card), NULL));
            card->getSprite()->runAction(Sequence::create(action, __CCCallFuncND::create(this, callfuncND_selector(BoardLayer::didWinAnimation), card), nullptr));
        }
        else{
            card->getSprite()->setPosition(targetPosition);
            didWinAnimation(NULL, card);
        }
    }
    
}

Point BoardLayer::getTargetPositon(Point first, Point second, int i, int num)
{
    float x1, y1, x2, y2, x, y;
    x1=first.x;
    y1=first.y;
    x2=second.x;
    y2=second.y;
    
    x = x1 + (x2-x1)*i/num;
    y = y1 + (y2-y1)*i/num;
    
    Size winSize = Director::getInstance()->getWinSize();
    
    return Vec2(winSize.width/2.0f+x, winSize.height/2.0f+y);
}

void BoardLayer::didWinAnimation(Node* sender, void* card1)
{
    Card* card = (Card*)card1;
    card->setLocalZOrder(card->getLocalZOrder());
    if(card->getOrder()==cards->count()-1)
    {
        schedule(schedule_selector(BoardLayer::doWinAnimation), 0.03f);
    }
    
}

void BoardLayer::doWinAnimation(float dt)
{
    if(_winAnimationCount==50){
        unschedule(schedule_selector(BoardLayer::doWinAnimation));
        _winAnimationCount = 0;
        
        if(GameData::getInstance()->isSoundEnabled()){
        
            MyObjectDoSomethingWith(this, std::string("congratulation.mp3"));
        }
        
        //Do you want Replay? Show Dialog!
        for(int i=0; i<cards->count();i++)
        {
            Card* card=(Card*) cards->getObjectAtIndex(i);
            card->getSprite()->setPosition(Vec2(-getSizeWithDevice(100.0f),-getSizeWithDevice(100.0f)));
        }
        cards->removeAllObjects();
        
        Size winSize = Director::getInstance()->getWinSize();
        _congratulationLayer = CongratulationLayer::create();
        _congratulationLayer->init(this);
        _congratulationLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
        _congratulationLayer->setPosition(Vec2(0.0f, 0.0f));
        addChild(_congratulationLayer, 3);
        
        MoveTo* action = MoveTo::create(0.3f, Vec2(winSize.width/2.0f,winSize.height/2.0f));
        EaseIn *_easein = EaseIn::create(action,0.3f);
        Sequence *_sequence  =  Sequence::create( _easein, NULL ,NULL);
        
        _congratulationLayer->runAction(_sequence);

    }
    else
    {
        if(GameData::getInstance()->isSoundEnabled()){

            MyObjectDoSomethingWith(this, std::string("card_shuffle.mp3"));
        }
        
        _winAnimationCount++;
    
        Point targetPosition;
        Card* card =(Card*) cards->getObjectAtIndex(0);
        targetPosition = card->getSprite()->getPosition();
    
        for(int i=0; i<cards->count();i++)
        {
            Card* card1=(Card*)cards->getObjectAtIndex(i);
        
            if(i<cards->count()-1){
                Card* card2=(Card*)cards->getObjectAtIndex(i+1);
                card1->getSprite()->setPosition(card2->getSprite()->getPosition());
            
            }else{
                card1->getSprite()->setPosition(targetPosition);
            }
        }
    }
}

void BoardLayer::didCongratulationDialog(bool isReplay)
{
    _congratulationLayer->removeAllChildrenWithCleanup(true);
    _congratulationLayer = NULL;
    
    _isSetting = false;
    
    if(isReplay)
    {
        GameData::getInstance()->setNewGame(RANDOM_DEAL);
        replayGame();
    }
    else
    {
        showTaskbar();
    }
}

std::string BoardLayer::getTime()
{
    std::string temp="";
    int minute=_stageTime/60;
    if(minute>9)  temp+=to_string(minute);
    else temp+="0"+to_string(minute);
    
    int second=(int)_stageTime-minute*60;
    if(second>9)  temp+=":"+to_string(second);
    else temp+=":0"+to_string(second);
    
    return temp;
}

void BoardLayer::undo()
{
    if (moves->count() > 0)
    {
        Move* move = (Move*)moves-> getLastObject(); //Moves.Pop();
        moves->removeLastObject();
       
        //add by khj 3.5
        if(move->getSourceDeck()->getType() == DECK_PLAY)
        {
            if(move->getSourceDeck()->cards->count()  == 1)
            {
                if(move->getSourceDeck()->getTopCard()->getChangedVisible())
                    move->getSourceDeck()->getTopCard()->setVisible(!move->getSourceDeck()->getTopCard()->getVisible());
            }else if(move->getSourceDeck()->cards->count() > 1)
            {
                
                Card* card2=(Card*)move->getSourceDeck()->cards->getObjectAtIndex(move->getSourceDeck()->cards->count()-2);
                if(move->getSourceDeck()->getTopCard()->getChangedVisible() && !card2->getVisible())
                {
                    
                    Card* card1=move->getSourceDeck()->getTopCard();
                    Card* card0=(Card*)move->cards->getObjectAtIndex(0);
                    
                    if(!(card0->getSuit()==card1->getSuit() && card0->getRank()==card1->getRank()-1))
                        move->getSourceDeck()->getTopCard()->setVisible(!move->getSourceDeck()->getTopCard()->getVisible());
                }
                
            }
        }
        //
        
        GameData::getInstance()->setUndoMove(true);
        move->undo();
        
        //increase move count
        _totalMoveCount++;
        _totalUndoCount++;
        
        //calculate game current score
        showScore();
        
        showCardFace();
        
        calculateDragableCards();
        //redoMoves->addObject(move);
        
        if(GameData::getInstance()->getGameType()==TYPE_SPIDER && move->getSourceDeck()->getType()==DECK_DEALER)
        {            
            undo();
        }
    }
}

void BoardLayer::hint()
{
    _actuallyCardMoved=false;    
    _isHint = true;
    
    for(int i = 0; i < playCells->count(); i++)
    {
        int topOrder = -1;
        Deck* deck = (Deck*)playCells->getObjectAtIndex(i);
        for(int j = 0; j < deck->cards->count(); j++)
        {
            Card* card = (Card*)deck->cards->getObjectAtIndex(j);
            Sprite* sprite = card->getSprite();
            
            if(card->getLocalZOrder() > topOrder)
            {
                topOrder = sprite->getLocalZOrder();
                if(!_actuallyCardMoved) checkHint(card);
                else return;
            }
        }
        
        if(_actuallyCardMoved) return;
    }
    
    if(GameData::getInstance()->getGameType() == TYPE_FREECELL)
    {
        for(int i = 0; i < freeCells->count(); i++)
        {
            Deck* deck = (Deck*)freeCells->getObjectAtIndex(i);
            if(deck->hasCards())
            {
                Card* card=deck->getTopCard();
                
                if(!_actuallyCardMoved) checkHint(card);
                else return ;
            }
        }
        
    }
    
    if(_dealTo!=NULL){
        
        if(_dealTo->hasCards()){//solitaire
            Card* card=_dealTo->getTopCard();
            if(!_actuallyCardMoved) checkHint(card);
            else return;
        }
    }
}

void BoardLayer::checkHint(Card* _hintCard){
    Deck* deck = _hintCard->getDeck();
    for(long i = deck->cards->getIndexOfObject(_hintCard); i < deck->cards->count(); i++)
    {
        Card* card = (Card*)deck->cards->getObjectAtIndex(i);        
        doubleClick(card); //card->touchBegan(location);
    }
    
}

void BoardLayer::setSetting(bool isSetting){
    _isSetting = isSetting;
}

bool BoardLayer::getSetting(){
    return _isSetting;
}

void BoardLayer:: setTime(float dt)
{
    if(_isSetting) _startTime++;
    
    _tempTime++;
    _stageTime=_tempTime-_startTime;
        
    if(_tempTime - _tempTime1 >= 10)
    {
       _gameScore--;
       _cuttingScore ++;
       _tempTime1 = _tempTime;
    }
    showScore ();
    
    if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE && !_isAutocompleteRunning)
        checkForFoundationMoves(false);
    
    if(GameData::getInstance()->getGameType() == TYPE_SPIDER)
    {
        for(int i=0; i<goalCells->count();i++)
        {
            Deck* goalDeck = (Deck*) goalCells->getObjectAtIndex(i);
            if(goalDeck->hasCards())
            {
                if(goalDeck->getTopCard()->getLocalZOrder()!=12)
                {
                    //CCLog("%s","error");
                    goalDeck->getTopCard()->setLocalZOrder(12);
                }
            }
        }
    }
}

void BoardLayer::updateRightHanded(){

    updateDealerWithLandscape();
    updateGoalCellsWithLandscape();
    updatePlayCellsWithLandscape();
    updateFreeCellsWithLandscape();
    
}

void BoardLayer::setPreviousMode(){
    if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE){
        GameData::getInstance()->setDrawFlag(_isCurrentDrawFlag);
        GameData::getInstance()->setVegasMode(_isCurrentVegas);
    }
    
    if(GameData::getInstance()->getGameType() == TYPE_SPIDER){
        GameData::getInstance()->setSpiderMode(_currentSpiderMode);
    }
}

void BoardLayer::submitScore(){
    
    AppDelegate* app = AppDelegate::get();
    
    std::string winStr = getGameString() + "Wins";
    int totalWins = GameData::getInstance()->getInt(winStr, 0);//comment715
    
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
        {
            if(GameData::getInstance()->isDrawFlag()){
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.sDraw3Score", getScore());
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.sDraw3Wins", totalWins);
                
            }else{
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.sDraw1Score", getScore());
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.sDraw1Wins", totalWins);
                
            }
            
            if(GameData::getInstance()->isVegasMode()){
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.sVegasStyleScore", getScore());                
                
            }
            
        }
            break;
            
        case TYPE_FREECELL:
            app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.FCHighScores", getScore());
            app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.FCTotalWins", totalWins);
            break;
            
        case TYPE_FORTY_THIEVES:
            app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.FTHighScores", getScore());
            app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.FTTotalWins", totalWins);
            break;
            
        case TYPE_SPIDER:
            if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY){
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss1suitscore", getScore());
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss1suitwins", totalWins);
            }
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL){
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss2suitscore", getScore());
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss2suitwins", totalWins);
            }
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT){
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss3suitscore", getScore());
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss3suitwins", totalWins);
            }
            else{
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss4suitscore", getScore());
                app->sendMessageToNative(MSG_SUBMIT_SCORE, "com.cobraclip.cardgames.ss4suitwins", totalWins);
            }
            break;
    }
}

void BoardLayer::submitAchieve(){
    
    AppDelegate* app = AppDelegate::get();
    
    std::string winStr = getGameString() + "Wins";
    int totalWins = GameData::getInstance()->getInt(winStr, 0);
    
    std::string totalScoreStr = getGameString() + "totalScore";
    int totalScore = GameData::getInstance()->getInt(totalScoreStr, 0);
    
    std::string gameCountStr = getGameString() + "gameCount";
    int totalGameCount = GameData::getInstance()->getInt(gameCountStr, 0);
    
    std::string undoStr = getGameString() + "withoutUndo";
    int withoutUndoCount = GameData::getInstance()->getInt(undoStr, 0);
    
    std::string hintStr = getGameString() + "withoutHint";
    int withoutHintCount = GameData::getInstance()->getInt(hintStr, 0);
    
    std::string longWinStreakStr = getGameString() + "longStreak";
    int longWinStreakCount = GameData::getInstance()->getInt(longWinStreakStr, 0);
    
    std::string totalVegasStr = getGameString() + "totalVegasScore";
    int totalVegasScore = GameData::getInstance()->getInt(totalScoreStr, 0);
    
    std::string selectFreecellStr = getGameString() + "selectFreecell";
    int selectFreecellCount = GameData::getInstance()->getInt(selectFreecellStr, 0);//comment715
    
    switch (GameData::getInstance()->getGameType()) {
        case TYPE_SOLITAIRE:
        {
            if(GameData::getInstance()->isDrawFlag()){
                //Percent value
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWindraw3game.ach", 100);
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWin50draw3game.ach", 2*totalWins);
                
                app->sendMessageToNative(MSG_RANK_ACHIEVE, "com.cobraclip.cardgames.sDraw3Score", TYPE_SOLITAIRE);
                
            }else{
                
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWindraw1game.ach", 100);
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWin100draw1game.ach", totalWins);
            }
            
            if(GameData::getInstance()->isVegasMode()){
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sPlayVegas.ach", 100);
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sVegasScore.ach", totalVegasScore/10);
            }
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sPlay1000Games.ach", totalGameCount/10);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sPlay5000Games.ach", totalGameCount/50);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sPlay10000Games.ach", totalGameCount/100);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWin5gameswithoutUndo.ach", withoutUndoCount*20);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWin10gameswithoutHints.ach", withoutHintCount*10);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWin500games.ach", totalWins/5);
            
            if(_totalMoveCount < 96)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWinaGameIn95Moves.ach", 100);
            
            if(_totalMoveCount < 106)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWinaGameIn105Moves.ach", 100);
            
            if(_stageTime < 121)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWinaGamein2Min.ach", 100);
            
            if(_stageTime < 181)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWinaGamein3Min.ach", 100);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sScore5000over.ach", totalScore/50);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sScore7000over.ach", totalScore/70);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sScore10000Over.ach", totalScore/100);
            
            if(longWinStreakCount>1)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWin2InARow.ach", 100);
            if(longWinStreakCount>2)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sWin3GamesInARow.ach", 100);
            
            if(_solitaireAllAces)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sMoveAllAces.ach", 100);
            
            //app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sTop10ScoreWiningDeal.ach", topScoreCount * 10);
            
            if(_solitaireAllFace == 2)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.sPlaceallCardsTableaus.ach", 100);
            
        }
            break;
            
        case TYPE_FREECELL:
        {
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWinAGame.ach", 100);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWin100Games.ach", totalWins);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWin500Games.ach", totalWins/5);
            
            if(longWinStreakCount>1)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWin2gamesInARow.ach", 100);
            if(longWinStreakCount>2)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWin3gamesInARow.ach", 100);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWin5GamesNoneUndo.ach", withoutUndoCount*20);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWin10GamesNoneHint.ach", withoutHintCount*10);
            
            if(_totalMoveCount < 86)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWinAGameIn85Move.ach", 100);
            
            if(_totalMoveCount < 101)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWinAGameIn100Move.ach", 100);
            
            if(_stageTime < 121)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWinAGameIn2Min.ach", 100);
            
            if(_stageTime < 61)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWinAGameIn1Min.ach", 100);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fPlay1000Games.ach", totalGameCount/10);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fPlay5000Games.ach", totalGameCount/50);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fPlay10000Games.ach", totalGameCount/100);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fPlay100selectedgames.ach", selectFreecellCount);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fPlay1000selectedgames.ach", selectFreecellCount/10);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fScore1000.ach", totalScore/100);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fScore20000Over.ach", totalScore/200);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fScore20000Over.ach", totalScore/300);
            
            switch (_freecellUseCount) {
                case 0:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fUseNoFreeCell.ach", 100);
                    break;
                    
                case 1:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fUseOnly1FreeCell.ach", 100);
                    break;
                    
                case 2:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fUseOnly2FreeCell.ach", 100);
                    break;
                case 3:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fUseOnly3FreeCell.ach", 100);
                    break;
                    
                default:
                    break;
            }
            
            //app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fTop5ScoreWiningDeal.ach", topScoreCount * 20);
            app->sendMessageToNative(MSG_RANK_ACHIEVE, "com.cobraclip.cardgames.FCHighScores", TYPE_FREECELL);
            
            if(_freecellOneCard)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fFinishOneCardAtATime.ach", 100);
            
            if(_freecellOnlyKing)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fWinMovingOnlyKings.ach", 100);
            
            int gameNumber = GameData::getInstance()->getSelectedGame();
            
            switch (gameNumber) {
                case 164:
                case 7058:
                case 15196:
                case 27835:
                case 31316:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fEasyRoute.ach", 100);
                    break;
                    
                case 169:
                case 4368:
                case 7700:
                case 21278:
                case 31945:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fNotSoSimple.ach", 100);
                    break;
                    
                case 454:
                case 661:
                case 718:
                case 1941:
                case 6182:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fAmbitiousOne.ach", 100);
                    break;
                 
                case 11982:
                case 146692:
                    app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.fMissionImposs.ach", 100);
                    break;
                    
                default:
                    break;
            }
            
            
        }
            break;
            
        case TYPE_FORTY_THIEVES:
            break;
            
        case TYPE_SPIDER:
        {
            if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EASY){
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin1SuitGame.ach", 100);
            }
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_NORMAL){
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin2SuitGame.ach", 100);
            }
            else if(GameData::getInstance()->getSpiderMode() == SPIDER_MODE_EXPERT){
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin3SuitGame.ach", 100);
            }
            else{
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin4SuitGame.ach", 100);
            }
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin100games.ach", totalWins);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin500games.ach", totalWins/5);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssPlay1000Games.ach", totalGameCount/10);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssPlay5000Games.ach", totalGameCount/50);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssPlay10000Games.ach", totalGameCount/100);
            
            if(longWinStreakCount>7)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin8GamesInARow.ach", 100);
            
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin5GamesNoneUndo.ach", withoutUndoCount*20);
            app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssWin10GamesNoneHints.ach", withoutHintCount*10);
            
            std::string suit1prevGameResult = "Suit1prevGameResult";
            std::string suit2prevGameResult = "Suit2prevGameResult";
            std::string suit3prevGameResult = "Suit3prevGameResult";
            std::string suit4prevGameResult = "Suit4prevGameResult";
            
            int suit1prevWin = GameData::getInstance()->getInt(suit1prevGameResult, 0);
            int suit2prevWin = GameData::getInstance()->getInt(suit2prevGameResult, 0);
            int suit3prevWin = GameData::getInstance()->getInt(suit3prevGameResult, 0);
            int suit4prevWin = GameData::getInstance()->getInt(suit4prevGameResult, 0);
            
            if(suit1prevWin ==1 && suit2prevWin ==1 && suit3prevWin ==1 && suit4prevWin ==1)
                app->sendMessageToNative(MSG_SUBMIT_ACHIEVE, "com.cobraclip.cardgames.ssGrandSlam.ach", 100);
            
        }
            break;
    }
}
