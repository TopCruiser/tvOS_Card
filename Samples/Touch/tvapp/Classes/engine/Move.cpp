//
//  Move.cpp
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Move.h"
#include "Card.h"
#include "Deck.h"
#include "BoardLayer.h"
#include "GameData.h"

Move* Move::stack(Deck* source, Deck* target)
{
    return new Move(source, target);
}

Move* Move::single(Card* card, Deck* target, int targetIndex)
{
    Move* move = new Move(card, target, targetIndex);
    move->cards->addObject(card);
    return move;
}

Move* Move::swap(Card* card1, Card* card2)
{
    Move* move = new Move(card1, card2);
    move->cards->addObject(card1);
    move->cards->addObject(card2);
    return move;
}

Move* Move::multi()
{
    Deck::updatesDisabled = true;
    return new Move();
}

Move::Move(Card* card1, Card* card2)
{
    cards = __Array::create();
    cards->retain();
    _sourceDeck = card1->getDeck();
    _targetDeck = card2->getDeck();
    _moveType = MOVETYPE_SWAP;
}

Move::Move(Deck* source, Deck* target)
{
    cards = __Array::create();
    cards->retain();
    _sourceDeck = source;
    _targetDeck = target;
    _moveType = MOVETYPE_STACK;
}

Move::Move(Card* card, Deck* target, int targetIndex)
{
    cards = __Array::create();
    cards->retain();
    _sourceDeck = card->getDeck();
    _targetDeck = target;
    _cardIndex = targetIndex;
    _moveType = MOVETYPE_SINGLE;
}

Move::Move()
{
    _subMoves = __Array::create();
    _subMoves->retain();
    _moveType = MOVETYPE_MULTI;
}

Move::~Move()
{
    
}

Deck* Move::getSourceDeck()
{
    return _sourceDeck;
}

void Move::setSourceDeck(Deck* deck)
{
    _sourceDeck = deck;
}

Deck* Move::getTargetDeck()
{
    return _targetDeck;
}

void Move::setTargetDeck(Deck* deck)
{
    _targetDeck = deck;
}

int Move::getIndex()
{
    return _cardIndex;
}

void Move::setIndex(int index)
{
    _cardIndex = index;
}

void Move::addSubMove(Move* sub)
{
    sub->execute();
    _subMoves->addObject(sub);
}

void Move::execute()
{
    switch (_moveType) {
        case MOVETYPE_STACK:
            
            for (int i=0; i<cards->count();i++) {
                Card* card=(Card*)cards->objectAtIndex(i);
                card->setDeck(_targetDeck);
            }
            
            break;
            
        case MOVETYPE_SINGLE:
            for(int i = 0; i < cards->count(); i++)
            {
                Card* card = (Card*)cards->objectAtIndex(i);
                
                _oldIndex = card->getIndex();
                    
                if(_sourceDeck != _targetDeck)
                {
                        _cardIndex = card->getIndex();
                        card->getDeck()->cards->removeObject(card);
                        card->getDeck()->updateCardsWithAnimation();
                        card->setDeck(_targetDeck);
                }
                else
                {
                        if(_oldIndex != _cardIndex)
                        {
                            card->getDeck()->cards->removeObject(card);
                            _sourceDeck->cards->insertObject(card, _cardIndex);
                            card->getDeck()->updateCardsWithAnimation();
                        }
                }
                
            }
            break;
            
        case MOVETYPE_SWAP:
        {
            Card* card1 = (Card*)cards->objectAtIndex(0);
            Card* card2 = (Card*)cards->objectAtIndex(1);
            int card1Index = card1->getIndex();
            Deck* card1Deck = card1->getDeck();
            card1->setDeck(card2->getIndex(), card2->getDeck());
            card2->setDeck(card1Index, card1Deck);
        }
            break;
        case MOVETYPE_MULTI:
            Deck::updatesDisabled = false;
            break;
    }
}

void Move::undo()
{
    switch (_moveType)
    {
        case MOVETYPE_STACK:
        case MOVETYPE_SINGLE:
            for(int i=0; i < cards->count(); i++)
            {
                Card* card = (Card*)cards->objectAtIndex(i);
                
                if (_moveType == MOVETYPE_SINGLE)
                {
                    card->setDeck(_oldIndex, _sourceDeck);
                }
                else
                    card->setDeck(_sourceDeck);
            }
            //foreach (var deck in GameObject.FindObjectsOfType<Deck>())
              //  deck.UpdateCards();
            break;
            
        case MOVETYPE_SWAP:
        {
            Card* card1 = (Card*)cards->objectAtIndex(0);
            Card* card2 = (Card*)cards->objectAtIndex(1);
            int card1Index = card1->getIndex();
            Deck* card1Deck = card1->getDeck();
            card1->setDeck(card2->getIndex(), card2->getDeck());
            card2->setDeck(card1Index, card1Deck);
        }
            break;
            
        case MOVETYPE_MULTI:
            Deck::updatesDisabled = true;
            
            for(int i=0; i<_subMoves->count();i++){// foreach(var sub in submoves.Reverse<Move>())
                Move* move;
                move=(Move*) _subMoves->objectAtIndex(i);
                move->undo();//sub.Undo();
            }
            Deck::updatesDisabled = false;
            //foreach (var deck in GameObject.FindObjectsOfType<Deck>())
            //deck.UpdateCards();
            break;
      
    }

}

int Move::getMoveType(){
    
    return _moveType;
    
}
