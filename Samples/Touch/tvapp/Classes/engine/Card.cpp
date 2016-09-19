//
//  Card.cpp
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Card.h"
#include "Deck.h"
#include "BoardLayer.h"
#include "CardSprite.h"
#include "GameData.h"

bool Card::isAceBiggest = true;

bool Card::init()
{
    if(!Node::init())
        return false;
    
    return true;
}

void Card::init(Layer* parent)
{
    _parentLayer = parent;
    
    _visible = true;
    _dragable = true;
    _dragDisabled = false;
    _firstMove = true;
    _changedVisible = false;
    _dragging = false;
    
    _lastClickTime = 0.0f;
    
    ((BoardLayer*)_parentLayer)->cards->addObject(this);
}

void Card::init(int rank, int suit, Deck* deck, Layer* parent)
{
    _parentLayer = parent;
    
    _rank = rank;
    _suit = suit;
    _deck = deck;
    
    _visible = true;
    _dragable = true;
    _dragDisabled = false;
    _firstMove = true;
    _changedVisible = false;
    _dragging = false;
    
    _lastClickTime = 0.0f;
    
    ((BoardLayer*)_parentLayer)->cards->addObject(this);
}

void Card::touchBegan(Point position)
{
    if(_deck->getType() == DECK_DEALER)
        _clickedDealer = true;
    
    long long currentTime = getCurrentTime();
    if((currentTime - _lastClickTime) < 300.0f)
    {
        _dragDisabled = true;
        ////setZOrder(_sprite->getZOrder() + 1000);
        //setZOrder(getZOrder()+1000);//remove by KHJ 03.21.2015
        //((BoardLayer*)_parentLayer)->doubleClick(this);
        _lastClickTime = 0.0f;
    }
    else
    {
        _lastClickTime = currentTime;
        _clickedPosition = position;
        _lastMovePosition = position;
    }   
}

void Card::touchMoved(Point position)
{
    if(position.getDistanceSq(_clickedPosition) > _dragDeadDistance * _dragDeadDistance)
    {
        if(_dragDisabled)
            return;
        
        if(_dragable)
        {
            if(!_dragging)
                _dragging = true;
            
            Deck* deck = this->getDeck();
            for(long i = deck->cards->getIndexOfObject(this); i < deck->cards->count(); i++)
            {
                Card* card = (Card*)deck->cards->getObjectAtIndex(i);
                if(card->getLocalZOrder()<1000) card->setLocalZOrder(getLocalZOrder()+1000);
            }
            
            _firstMove = false;
            
            float deltaX = position.x - _lastMovePosition.x;
            float deltaY = position.y - _lastMovePosition.y;
            
            for(long i = deck->cards->getIndexOfObject(this); i < deck->cards->count(); i++)
            {
                Card* card = (Card*)deck->cards->getObjectAtIndex(i);
                Point pos = card->getSprite()->getPosition();
                card->getSprite()->setPosition(Vec2(pos.x+deltaX, pos.y+deltaY));
                
            }
            
            _lastMovePosition = position;
        }
    }
}

void Card::touchEnded(Point position)
{
    _dragDisabled = false;
    _firstMove = true;
    
    if(_clickedDealer)
    {
        if(GameData::getInstance()->getGameType() != TYPE_SPIDER)
            ((BoardLayer*)_parentLayer)->doStackMove(this, ((BoardLayer*)_parentLayer)->getDealTo());
        else
            ((BoardLayer*)_parentLayer)->doStackMove1(this);
        
        _clickedDealer = false;
    }
    else
    {
        if(_dragging)
        {
            _dragging = false;
            Deck* nearDeck = ((BoardLayer*)_parentLayer)->getNearDeck();
            if(nearDeck != NULL && ((BoardLayer*)_parentLayer)->CardDrag(this, nearDeck))
                return;
            
            _deck->updateCardsWithAnimation();
        }
        else
        {
            setLocalZOrder(getLocalZOrder()+1000);//update by KHJ 03.21.2015
            ((BoardLayer*)_parentLayer)->doubleClick(this);
        }
    }
    
}

int Card::getRank()
{
    return _rank;
}

void Card::setRank(int rank)
{
    _rank = rank;
}

int Card::getSuit()
{
    return _suit;
}

void Card::setSuit(int suit)
{
    _suit = suit;
}

int Card::getColor()
{
    if(_suit == CARDSUIT_SPADES || _suit == CARDSUIT_CLUBS)
        return CARDCOLOR_BLACK;
    else
        return CARDCOLOR_RED;
}

long Card::getIndex()
{
    return _deck->cards->getIndexOfObject(this);
}

int Card::getOrder()
{
    return _order;
}

void Card::setOrder(int order)
{
    _order = order;
}

bool Card::getVisible()
{
    return _visible;
}

void Card::setVisible(bool visible)
{
    if(_visible != visible)
    {
        _visible = visible;
        
        int cardFaceIndex=GameData::getInstance()->getCardFaceIndex();
        int cardBackIndex=GameData::getInstance()->getCardBackIndex();
        
        setCardSprite(cardFaceIndex, cardBackIndex);
    }
}

bool Card::getDragable()
{
    return _dragable;
}

void Card::setDragable(bool dragable)
{
    _dragable = dragable;
}

bool Card::getChangedVisible()
{
    return _changedVisible;
}

void Card::setChangedVisible(bool visible)
{
    _changedVisible = visible;
}

Deck* Card::getDeck()
{
    return _deck;
}

void Card::setDeck(Deck* deck)
{
    if(_deck != deck)
    {
        if(_deck != NULL){
            if(_deck->getType()==DECK_GOAL) return;
            _deck->cards->removeObject(this);
        }
        
        if(getLocalZOrder()<1000) setLocalZOrder(getLocalZOrder()+1000);//add by KHJ 03.23.2015
        
        _deck = deck;
        _deck->cards->addObject(this);
        _deck->updateCardsWithAnimation();
    }
}

void Card::setDeck(int newPosition, Deck* deck)
{
    if(getLocalZOrder()<1000) setLocalZOrder(getLocalZOrder()+1000);//add by KHJ 03.23.2015
    
    _deck->cards->removeObject(this);
    if(deck != NULL)
    {
        _deck->updateCardsWithAnimation();
        _deck = deck;
    }
    _deck->cards->insertObject(this, newPosition);
    _deck->updateCardsWithAnimation();
}

void Card::shuffle()
{
    moveToIndex(arc4random() % _deck->cards->count());    
}

void Card::selectedShuffle(int j)
{
    moveToIndex(j);
}

void Card::moveToIndex(int index)
{
    _deck->cards->removeObject(this);
    _deck->cards->insertObject(this, index);
}

void Card::createSprite()
{
    _sprite = Sprite::create();
    switch (GameData::getInstance()->getCardFaceIndex()) {
        case 0:
            _sprite->initWithFile(getNameWithResolution(g_strCard1Sprites[getCardIndex()].getCString()).c_str());
            break;
        case 1:
            _sprite->initWithFile(getNameWithResolution(g_strCard2Sprites[getCardIndex()].getCString()).c_str());
            break;
        default:
            _sprite->initWithFile(getNameWithResolution(g_strCard3Sprites[getCardIndex()].getCString()).c_str());
            break;
    }
    _sprite->setVisible(false);
    addChild(_sprite);
}

void Card::updateSprite(int posX, int posY, float realWidth)
{
    CCLOG("-----------------updateSprite function called (%d, %d)----------------", posX, posY);
    float scale = realWidth / _sprite->getContentSize().width;
    _sprite->setScale(scale);
    _sprite->setPosition(Vec2(posX, posY));
    CCPoint cc = _sprite->convertToWorldSpace(_sprite->getPosition());
    _sprite->setVisible(true);
    setContentSize(_sprite->getContentSize());
}

void Card::setCardSprite(int cardFaceIndex, int cardBackIndex)
{
    if(_visible){
        switch (cardFaceIndex) {
            case 0:
                _sprite->initWithFile(getNameWithResolution(g_strCard1Sprites[getCardIndex()].getCString()).c_str());
                break;
            case 1:
                _sprite->initWithFile(getNameWithResolution(g_strCard2Sprites[getCardIndex()].getCString()).c_str());
                break;
            default:
                _sprite->initWithFile(getNameWithResolution(g_strCard3Sprites[getCardIndex()].getCString()).c_str());
                break;
        }
        
    }
    else
        _sprite->initWithFile(getNameWithResolution(g_strBackCardSprites[cardBackIndex].getCString()).c_str());
}

Sprite* Card::getSprite()
{
    return _sprite;
}

int Card::getCardIndex()
{
    return ((_suit - 1) * 13) + _rank - 1;
}

__String Card::getRankString()
{
    switch (_rank)
    {
        case CARDRANK_ACE:
            return "A";
        case CARDRANK_JACK:
            return "J";
        case CARDRANK_QUEEN:
            return "Q";
        case CARDRANK_KING:
            return "K";
        default:
            char str[32];
            sprintf(str, "%d", _rank);
            return str;
    }
}