//
//  Card.h
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__Card__
#define __cardgame__Card__

#include "Common.h"

enum CARD_RANK
{
    CARDRANK_ACE = 1,
    CARDRANK_DEUCE,
    CARDRANK_THREE,
    CARDRANK_FOUR,
    CARDRANK_FIVE,
    CARDRANK_SIX,
    CARDRANK_SEVEN,
    CARDRANK_EIGHT,
    CARDRANK_NINE,
    CARDRANK_TEN,
    CARDRANK_JACK,
    CARDRANK_QUEEN,
    CARDRANK_KING
};

enum CARD_SUIT
{
    CARDSUIT_SPADES = 1,
    CARDSUIT_HEARTS,
    CARDSUIT_DIAMONDS,
    CARDSUIT_CLUBS
};

enum CARD_COLOR
{
    CARDCOLOR_BLACK = 0,
    CARDCOLOR_RED,
};

class Deck;

class Card : public CCNode
{
public:
    virtual bool init();
    virtual void init(CCLayer* parent);
    virtual void init(int rank, int suit, Deck* deck, CCLayer* parent);
    
    void touchBegan(CCPoint position);
    void touchMoved(CCPoint position);
    void touchEnded(CCPoint position);
    
    int getRank();
    void setRank(int rank);
    
    int getSuit();
    void setSuit(int suit);
    
    int getColor();
    int getIndex();
    
    int getOrder();
    void setOrder(int order);
    
    bool getVisible();
    void setVisible(bool visible);
    
    bool getDragable();
    void setDragable(bool dragable);
    
    bool getChangedVisible();
    void setChangedVisible(bool visible);
    
    Deck* getDeck();
    void setDeck(Deck* deck);
    void setDeck(int newPosition, Deck* deck = NULL);
    
    void shuffle();
    void selectedShuffle(int j);
    
    void createSprite();
    void updateSprite(int posX, int posY, float realWidth);
    CCSprite* getSprite();
    void setCardSprite(int cardFaceIndex, int cardBackIndex);
    
private:
    void moveToIndex(int index);
    int getCardIndex();
    CCString getRankString();
    
public:
    static bool isAceBiggest;
    
private:
    CCLayer* _parentLayer;
    CCSprite* _sprite;
    
    const float _dragDeadDistance = 10.0f;
    
    int _rank;
    int _suit;
    int _color;
    int _order;
    
    long long _lastClickTime;
    
    bool _visible;
    bool _dragable;
    bool _dragging;
    bool _dragDisabled;
    bool _clickedDealer;
    bool _firstMove;
    bool _changedVisible;
    
    Deck* _deck;
    
    CCPoint _clickedPosition;
    CCPoint _lastMovePosition;
    
public:
    CREATE_FUNC(Card);
};

#endif
