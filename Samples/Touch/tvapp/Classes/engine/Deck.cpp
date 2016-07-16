//
//  Deck.cpp
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "Deck.h"
#include "Card.h"
#include "CardSprite.h"
#include "GameData.h"
#include "BoardLayer.h"

bool Deck::updatesDisabled = false;

bool Deck::init()
{
    if(!Node::init())
        return false;
    
    return true;
}

void Deck::init(Layer* parent)
{
    _parentLayer = parent;
    cards = new Array;
    
    _cardSpaceX = 0.0f;
    _cardSpaceY = 0.0f;
    _maxCardSpace = 0;
}

void Deck::setType(int type)
{
    _type = type;
}

int Deck::getType()
{
    return _type;
}

void Deck::setIndex(int index)
{
    _index = index;
}

int Deck::getIndex()
{
    return _index;
}

float Deck::getCardSpaceX()
{
    return _cardSpaceX;
}

void Deck::setCardSpaceX(float value)
{
    _cardSpaceX = value;
}

float Deck::getCardSpaceY()
{
    return _cardSpaceY;
}

void Deck::setCardSpaceY(float value)
{
    _cardSpaceY = value;
}

int Deck::getMaxCardSpace()
{
    return _maxCardSpace;
}

void Deck::setMaxCardSpace(int value)
{
    _maxCardSpace = value;
}

bool Deck::hasCards()
{
    if(cards->count() > 0)
        return true;
    else
        return false;
}

bool Deck::hasSuit(int rank, int suit)
{
    if(getCard(rank, suit) != NULL)
        return true;
    else
        return false;
}

bool Deck::hasColor(int rank, int color)
{
    if(color == CARDCOLOR_BLACK)
        return hasSuit(rank, CARDSUIT_CLUBS) || hasSuit(rank, CARDSUIT_SPADES);
    else
        return hasSuit(rank, CARDSUIT_HEARTS) || hasSuit(rank, CARDSUIT_DIAMONDS);
}

Card* Deck::getTopCard()
{
    if(cards->count() > 0)
        return (Card*) cards->getObjectAtIndex(cards->count() - 1);
    else
        return NULL;
}

Card* Deck::getBottomCard()
{
    if(cards->count() > 0)
        return (Card*)cards->getObjectAtIndex(0);
    else
        return NULL;
}

void Deck::createCards(int numberOfSuits)
{
    updatesDisabled = true;
    
    if(GameData::getInstance()->getGameType() == TYPE_SPIDER)
    {
        for(int suit = 0; suit < 8; suit++)
        {
            for(int number = 1; number <= 13; number++)
            {
                Card* card = Card::create();
                card->init(_parentLayer);
                card->setRank(number);
                
                if(numberOfSuits == 1)
                    card->setSuit(1);
                else if(numberOfSuits == 2)
                    card->setSuit(suit % 2 + 1);
                else if(numberOfSuits == 3)
                    card->setSuit(suit % 3 + 1);
                else
                    card->setSuit(suit % 4 + 1);
                
                card->createSprite();
                card->setDeck(this);
                addChild(card);
            }
        }
    }
    else
    {
        for(int number = 13; number >= 1; number--)
        {
            for(int suit = 0; suit <numberOfSuits; suit++)
            {
                int realSuit = suit % 4 + 1;
            
                Card* card = Card::create();
                card->init(_parentLayer);
                card->setRank(number);
                card->setSuit(realSuit);
                card->createSprite();
                card->setDeck(this);
                addChild(card);
            }
        }
    }
    
    updatesDisabled = false;
}

void Deck::updateCardsWithAnimation()//Error, Bug, Exception!
{
    if(updatesDisabled)
        return;
    
    Point basePosition = Vec2(_deckSprite->getPositionX(), _deckSprite->getPositionY());
    Point deltaPosition = Vec2(0.0f, 0.0f);
    
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        //add by me!
        if(card->getDeck()->getType() == DECK_GOAL){
            if(i== cards->count()-1){
                //Log("goaldeck cards %d", i);
                MoveTo* action = MoveTo::create(0.01f, basePosition);
                card->setOrder(i);
                card->getSprite()->stopAllActions();
                card->getSprite()->runAction(Sequence::create(action, CC_CALLBACK_2(Deck::doneAnimation, this, card), NULL));
            }
        }
        else if(i != 0)
        {
            if(this != ((BoardLayer*)_parentLayer)->getDealTo())
            {
                Card* prevCard = (Card*)cards->getObjectAtIndex(i-1);
                if(card->getVisible() && prevCard->getVisible() && card->getDeck()->getType() == DECK_PLAY)
                {
                    deltaPosition.y -= getSizeWithDevice(36.0f);
                    if(_maxCardSpace > 0 && cards->count() > _maxCardSpace)
                    {
                        //if(getType() == DECK_PLAY)
                        //{
                            if(cards->count() <= 12) {//20
                                
                                deltaPosition.y += getSizeWithDevice(6.0f); // -30.0f
                            }
                            else if(cards->count() > 12){ //20                                
                                deltaPosition.y += getSizeWithDevice(12.0f); // -24.0f
                            }
                            //deltaPosition.x -= (getSizeWithDevice(_cardSpaceX) * _maxCardSpace) / cards->count();
                        //}
                        //else
                        //{
                          //  CCLog("where %d", _maxCardSpace);
                          //  deltaPosition.x -= (getSizeWithDevice(_cardSpaceX) * _maxCardSpace) / cards->count();
                          //  deltaPosition.y -= (getSizeWithDevice(_cardSpaceY) * _maxCardSpace) / cards->count();
                        //}
                    }
                }
                else
                {
                    //contains target of goalDeck
                    deltaPosition.y -= getSizeWithDevice(_cardSpaceY);
                }
                deltaPosition.x -= getSizeWithDevice(_cardSpaceX);
            }
            else
            {
                if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE &&
                   GameData::getInstance()->isDrawFlag())
                {
                    if(i > (cards->count() - 3))
                    {
                        //deltaPosition.x -= getSizeWithDevice(15.0f);
                        //Update by KHJ 03/19/2015
                        if(GameData::getInstance()->isRightHanded()){
                            deltaPosition.x -= getSizeWithDevice(15.0f);
                        }else{
                            deltaPosition.x += getSizeWithDevice(15.0f);
                        }//
                    }
                }
                else
                {
                    deltaPosition.x -= getSizeWithDevice(_cardSpaceX);
                }
                deltaPosition.x -= getSizeWithDevice(_cardSpaceY);
            }
        }
        
        Point targetPosition = Vec2(basePosition.x + deltaPosition.x, basePosition.y + deltaPosition.y);
        
        MoveTo* action;
         action = MoveTo::create(0.2f, targetPosition);
                                                                                     
        card->setOrder(i);
        card->getSprite()->stopAllActions();
        card->getSprite()->runAction(Sequence::create(action, CC_CALLBACK_2(Deck::doneAnimation, this, card), NULL));
    }
}

void Deck::updateCardsWithoutAnimation()
{
    Point basePosition = Vec2(_deckSprite->getPositionX(), _deckSprite->getPositionY());
    Point deltaPosition = Vec2(0.0f, 0.0f);
    
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        
        if(i != 0)
        {
            if(this != ((BoardLayer*)_parentLayer)->getDealTo())
            {
                Card* prevCard = (Card*)cards->getObjectAtIndex(i-1);
                if(card->getVisible() && prevCard->getVisible() && card->getDeck()->getType() == DECK_PLAY)
                {
                    deltaPosition.y -= getSizeWithDevice(36.0f);
                    if(_maxCardSpace > 0 && cards->count() > _maxCardSpace)
                    {
                        if(getType() == DECK_PLAY)
                        {
                        //    if(cards->count() <= 20)
                        //        deltaPosition.y -= getSizeWithDevice(30);
                        //    else if(cards->count() > 20)
                        //        deltaPosition.y -= getSizeWithDevice(24.0f);
                        //    deltaPosition.x -= (_cardSpaceX * _maxCardSpace) / cards->count();
                        }
                        else
                        {
                            deltaPosition.x -= (_cardSpaceX * _maxCardSpace) / cards->count();
                            deltaPosition.y -= (_cardSpaceY * _maxCardSpace) / cards->count();
                        }
                    }
                }
                else
                {
                    deltaPosition.y -= _cardSpaceY;
                }
                deltaPosition.x -= _cardSpaceX;
            }
            else
            {
                if(GameData::getInstance()->getGameType() == TYPE_SOLITAIRE &&
                   GameData::getInstance()->isDrawFlag())
                {
                    if(i > (cards->count() - 3))
                        deltaPosition.x -= getSizeWithDevice(15.0f);
                }
                else
                {
                    deltaPosition.x -= _cardSpaceX;
                }
                deltaPosition.x -= _cardSpaceY;
            }
        }
        
        Point targetPosition = Vec2(basePosition.x + deltaPosition.x, basePosition.y + deltaPosition.y);
        card->setLocalZOrder(i);
        card->getSprite()->setPosition(targetPosition);
    }
}

void Deck::doneAnimation(Node* sender, Card* card)
{

    card->setLocalZOrder(card->getOrder());
    
    if(card->getDeck()->getType()==DECK_GOAL && !GameData::getInstance()->isUndoMove())
    {
        //FadeOut* fadeOut = FadeOut::create(2);
        //goalSprite->runAction(fadeOut);
        
        if(GameData::getInstance()->isSoundEnabled()){
            SimpleAudioEngine::getInstance()->playEffect("goal.mp3");
        }
        
        String *nameString = String::createWithFormat("particle_%d.png", card->getSuit());
        
        ParticleExplosion* _emitter = ParticleExplosion::create();
        
        //auto _emitter = ParticleFireworks::create();
        
        _emitter->setTexture( TextureCache::sharedTextureCache()->addImage(nameString->_string.c_str()) );
        _emitter->setDuration(1.0f);
        
        _emitter->setLife(1);
        _emitter->setLifeVar(1);
        
        // gravity
        _emitter->setGravity(Vec2(10, 10));
        
        
        // speed of particles
        _emitter->setSpeed(getSizeWithDevice(50));
        _emitter->setSpeedVar(getSizeWithDevice(20));
        
        Color4F startColor;
        if(card->getSuit()>1 && card->getSuit()<4)
            startColor = (Color4F){255, 0, 0, 1};
        else startColor = (Color4F){0,0,0,1};
        
        _emitter->setStartColor(startColor);
        _emitter->setStartColorVar(startColor);
        
        Color4F endColor = {255, 255, 255, 0};
        _emitter->setEndColor(endColor);
        _emitter->setEndColorVar(endColor);
        
        // size
        _emitter->setStartSize(getSizeWithDevice(30));
        _emitter->setStartSizeVar(getSizeWithDevice(2));
        _emitter->setEndSize(getSizeWithDevice(50));
        _emitter->setEndSizeVar(getSizeWithDevice(20));
        _emitter->setTotalParticles(5);
        
        _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());
        
        _emitter->setPosition(card->getSprite()->getPosition());
        
        ((BoardLayer*)_parentLayer)->addChild(_emitter);
    }
}

Card* Deck::getCard(int rank, int suit)
{
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*) cards->getObjectAtIndex(i);
        if(card->getRank() == rank && card->getSuit() == suit)
            return card;
    }
    
    return NULL;
}

Sprite* Deck::getSprite()
{
    return _deckSprite;
}

void Deck::shuffle(int time)
{
    for(int i = 0; i < time; i++)
    {        
        for(int j = 0; j < cards->count(); j++)
        {
            Card* card = (Card*)cards->getObjectAtIndex(j);
            card->shuffle();
        }
    }
    
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        card->setLocalZOrder(i);
        
        //get card number
        int suit, rank;
        suit= card->getSuit()-1;
        rank=card->getRank()-1;
        GameData::getInstance()->getCardIndexArray()->addObject(Integer::create(suit*13+rank));
    }
}

void Deck::selectedShuffle()
{
    if(GameData::getInstance()->getNewGame() ==  2)
    {
        //Replay Deal
        int idx, iValue;
        for(int i=0; i<cards->count(); i++)
        {
            
            idx = ((Integer*)GameData::getInstance()->getCardIndexArray()->getObjectAtIndex(i))->getValue();
            
            for(int j=i; j<cards->count();j++){
                Card* card=(Card*)cards->getObjectAtIndex(j);
                iValue =(card->getSuit()-1)*13 +card->getRank() -1;
                if(idx == iValue){
                    card->selectedShuffle(i);
                    break;
                }
            }            
            
        }
    }
    else
    {
        //Select Deal - Freecell
        int seed = GameData::getInstance()->getSelectedGame();
        
        class Random {
        public:
            void init(uint32_t seed) { _seed = seed; }
            int roll() { return (_seed = (_seed * MULT + INCR) & MASK) >> 16; }
        private:
            int _seed;
            enum { MULT = 214013, INCR = 2531011, MASK = (1U << 31) - 1 };
        };
        
        Random _random;
        _random.init(seed);
        
        for (int i = 0; i < 51 ; i++) {
            
            int j = 51 - _random.roll() % (52 - i);
            
            Card* topCard =(Card*) cards->getObjectAtIndex(i);
            Card* randCard =(Card*) cards->getObjectAtIndex(j);
            
            cards->replaceObjectAtIndex(j, topCard);
            cards->replaceObjectAtIndex(i, randCard);
            
        }
        
        for(int i = 0; i<26; i++){
            
            Card* card1 =(Card*) cards->getObjectAtIndex(i);
            Card* card2 =(Card*) cards->getObjectAtIndex(51-i);
            
            cards->replaceObjectAtIndex(51-i, card1);
            cards->replaceObjectAtIndex(i, card2);
            
        }
        
        
    }
    
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        card->setLocalZOrder(i);
        
        //get card number
        int suit, rank;
        suit= card->getSuit()-1;
        rank=card->getRank()-1;
        GameData::getInstance()->getCardIndexArray()->addObject(Integer::create(suit*13+rank));
    }
}

void Deck::winShuffle()
{
    ////////////// Deal using Winning number
    double selectedGame=GameData::getInstance()->getSelectedGame();
    int j;
    
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        
        j=(int)selectedGame % cards->count();
        card->selectedShuffle(j);
        
        if(selectedGame<cards->count()) selectedGame = selectedGame * 104729 +j;
        else selectedGame /=1.01;
    }
    
    
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        card->setLocalZOrder(i);
    }
    ////////////////////////
    
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        card->setLocalZOrder(i);
        
        //get card number
        int suit, rank;
        suit= card->getSuit()-1;
        rank=card->getRank()-1;
        GameData::getInstance()->getCardIndexArray()->addObject(Integer::create(suit*13+rank));
    }
}


void Deck::flipAllCards()
{
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*) cards->getObjectAtIndex(i);
        card->setVisible(!card->getVisible());
    }
}

void Deck::draw(Deck* toDeck, int count)
{
    for(int i = 0; i < count; i++)
        getTopCard()->setDeck(toDeck);
}

void Deck::createSprite(String strSprite)
{
    _deckSprite = Sprite::create(getNameWithResolution(strSprite.getCString()).c_str());
    _deckSprite->setVisible(false);
    addChild(_deckSprite);
}

void Deck::updateSpriteWithEmpty()
{
    _deckSprite->initWithFile(getNameWithResolution(g_strOtherCardSprites[3].getCString()).c_str());
}

void Deck::updateSprite(float posX, float posY, float realWidth)
{
    float scale = realWidth / _deckSprite->getContentSize().width;
    _deckSprite->setScale(scale);
    _deckSprite->setPosition(Vec2(posX, posY));
    _deckSprite->setVisible(true);
    setContentSize(_deckSprite->getContentSize());
}

void Deck::updateCardSprites(float posX, float posY, float realWidth)
{
    for(int i = 0; i < cards->count(); i++)
    {
        Card* card = (Card*)cards->getObjectAtIndex(i);
        card->updateSprite(posX, posY, realWidth);
    }
}

void Deck::showSprite(bool bVisible)
{
    _deckSprite->setVisible(bVisible);
}

