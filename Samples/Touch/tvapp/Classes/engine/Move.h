//
//  Move.h
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__Move__
#define __cardgame__Move__


#include "Common.h"

enum MOVE_TYPE
{
    MOVETYPE_SINGLE = 0,
    MOVETYPE_STACK,
    MOVETYPE_SWAP,
    MOVETYPE_MULTI
};

class Deck;
class Card;

class Move : public CCObject
{
public:
    static Move* stack(Deck* source, Deck* target);
    static Move* single(Card* card, Deck* target, int targetIndex = -1);
    static Move* swap(Card* card1, Card* card2);
    static Move* multi();
    
    Move();
    Move(Card* card1, Card* card2);
    Move(Deck* source, Deck* target);
    Move(Card* card, Deck* target, int targetIndex);
    ~Move();
    
    Deck* getSourceDeck();
    void setSourceDeck(Deck* deck);
    
    Deck* getTargetDeck();
    void setTargetDeck(Deck* deck);
    
    int getIndex();
    void setIndex(int index);
    
    void addSubMove(Move* sub);
    void undo();
    void execute();
    
    int getMoveType();
    
public:
    CCArray* cards;
    
private:
    Deck* _sourceDeck;
    Deck* _targetDeck;
    
    int _cardIndex;
    int _oldIndex;
    int _moveType;
    
    CCArray* _subMoves;
};

#endif
