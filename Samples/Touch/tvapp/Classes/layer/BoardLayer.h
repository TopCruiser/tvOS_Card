//
//  BoardLayer.h
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__BoardLayer__
#define __cardgame__BoardLayer__

#include "Common.h"
#include "Card.h"
#include "Deck.h"
#include "Move.h"
#include "CongratulationLayer.h"

class BoardLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    static BoardLayer* getInstance();
    void setInstance(BoardLayer* _board);
    virtual bool init();
    virtual void init(Layer* parent);

    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void onDummy(Ref* sender);////////////
    
    void setCells(int cells);
    void setSuits(int suits);
    void setStacks(int stacks);
    
    long getScore();
    std::string getTime();
    void setTime(float dt);
    
    Deck* getDealTo();
    Deck* getNearDeck();
    
    void startNewGame();
    void replayGame();

    void updateLayoutWithLandscape();
    void updateRightHanded();
    
    bool CardDrag(Card* card, Deck* targetDeck);
    void doMove(Move* move);
    bool doStackMove(Card* card, Deck* targetDeck);
    void doStackMove1(Card* card);
    bool doDealToMove(Deck* deck);
    void doubleClick(Card* card);
    void undo();
    void hint();
    bool getSetting();
    void setSetting(bool isSetting);
    void didCongratulationDialog(bool isReplay);
    
    void setPreviousMode();
    
    bool pressesBegan();
    
private:
    std::string getGameString();    
        
    void saveGameStatus();
    void setGameInfo();
    
    void initLayout();
    void createPlayCells();
    void createFreeCells();
    void createGoalCells();
    void createDealer();
    void drawDealer(float dt);
    void addCardsToPlayCell(float dt);
    void showLastCards();
    void flipLastCards(float dt);
    void showTaskbar();

    void updateCardSizeWithLandscape();
    void updatePlayCellsWithLandscape();
    void updateFreeCellsWithLandscape();
    void updateGoalCellsWithLandscape();
    void updateDealerWithLandscape();
    
    void calculateDragableCards();
    
    int movableStackLimit(bool isTargetEmptyPlayCell);
    int countEmpty(__Array* decks);
    
    bool isWrongPlacement(Card* card1, Card* card2);
    Card* getSelectedCard(CCPoint touchPoint);
    
    void showCardFace();
    void showScore();
    void checkCompletePlaycells();
    bool checkPlayCell(Deck* deck);
    bool doCompleteDeckMove(Deck* deck);
    void checkForFoundationMoves(bool onlySafe);
    bool checkDeck(Deck* deck, bool onlySafe);
    bool isCardSafeToMove(Card* cardToMove);
    Deck* getGoalDeckForCard(Card* card);
    bool checkWin();
    
    void win();
    void doWinAnimation(float dt);
    void didWinAnimation(Node* sender, void* card);
    CCPoint getTargetPositon(CCPoint first, CCPoint second, int i, int num);
    
    void checkHint(Card*);
    
    void submitScore();
    void submitAchieve();
    
public:
    Layer* _parentLayer;
    __Array* cards;
    __Array* moves;
    //CCArray* redoMoves;
    __Array* playCells;
    __Array* goalCells;
    __Array* freeCells;
    LabelTTF* _timeLabel;
    LabelTTF* _moveLabel;
    int _totalMoveCount;
    bool _startedGameFlag;
    bool _hasWon;
    /////
    bool bTouchBegan;
    Vec2 lastMovedPoint;
    
    MenuItem* dummy;
    
private:
    static BoardLayer* _instance;
    
    //const int _maxFreeCells = 4;
    //const int _maxGoalCells = 8;
    //const int _maxStacks = 12;
    
    int _cells;
    int _suits;
    int _stacks;
    int _directMode;
    long _gameScore;
    int _cuttingScore;
    int _totalUndoCount;
    int _maxPlayCards;
    int _dealsLeftCount;
    int index, count, stack;    
    int _winAnimationCount;
    
    float _stageTime;
    float _startTime;
    float _tempTime;
    float _tempTime1;
    float _playstackVerticalSpace;
    float _cardwidth;
    float _cardheight;
    
    bool _gameFirstStarted;
    bool _actuallyCardMoved;
    
    bool _isAutocompleteRunning;
    bool _isSetting;
    bool _isPlayCellTap;
    
    LabelTTF* _scoreLabel;
    
    Deck* _dealer;
    Deck* _dealTo;
    //Deck* _dealFrom;
    Card* _draggingCard;
    __Array* allActions;
    CongratulationLayer* _congratulationLayer;
    
    bool _isCurrentDrawFlag;
    bool _isCurrentVegas;
    int _currentSpiderMode;
    
    bool _isHint;
    int _solitaireAllFace;
    bool _solitaireAllAces;
    
    int _freecellUseCount;
    bool _freecellOneCard;
    bool _freecellOnlyKing;
    
public:
    CREATE_FUNC(BoardLayer);
};

#endif