//
//  Deck.h
//  cardgame
//
//  Created by Pink on 2/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__Deck__
#define __cardgame__Deck__

#include "Common.h"

enum DECK_TYPE
{
    DECK_DEALER = 0,
    DECK_FREE,
    DECK_GOAL,
    DECK_PLAY,
    DECK_DEALFROM,
    DECK_DEALTO
};

class Card;

class Deck : public Node
{
public:
    virtual bool init();
    virtual void init(Layer* parent);
    
public:
    void setType(int type);
    int getType();
    void setIndex(int index);
    int getIndex();
    
    float getCardSpaceX();
    void setCardSpaceX(float value);
    
    float getCardSpaceY();
    void setCardSpaceY(float value);
    
    int getMaxCardSpace();
    void setMaxCardSpace(int value);
    
    bool hasCards();
    bool hasSuit(int rank, int suit);
    bool hasColor(int rank, int color);
    
    Card* getTopCard();
    Card* getBottomCard();
    
    void createCards(int numberOfSuits);
    void updateCardsWithAnimation();
    
    void updateCardsWithoutAnimation();
    Card* getCard(int rank, int suit);
    Sprite* getSprite();
    
    void shuffle(int time = 1);
    void selectedShuffle();
    void winShuffle();
    
    void flipAllCards();
    void draw(Deck* toDeck, int count);
    
    void createSprite(__String strSprite);
    void updateSpriteWithEmpty();
    void updateSprite(float posX, float posY, float realWidth);
    void updateCardSprites(float posX, float posY, float realWidth);
    void showSprite(bool bVisible);
    void doneAnimation(Node* sender, void* card1);
        
public:
    static bool updatesDisabled;
    
    __Array* cards;
    
private:
    int _type;
    int _index;
    int _maxCardSpace;
    
    float _cardSpaceX;
    float _cardSpaceY;
    
    Layer* _parentLayer;
    Sprite* _deckSprite;
    //CCArray* _goalArray;
    
public:
    CREATE_FUNC(Deck);
};

#endif
