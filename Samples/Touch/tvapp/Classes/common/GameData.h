//
//  GameData.h
//  cardgame
//
//  Created by Pink on 2/3/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__GameData__
#define __cardgame__GameData__

#include "Common.h"

enum SPIDER_MODE {
    SPIDER_MODE_EASY = 0,
    SPIDER_MODE_NORMAL,
    SPIDER_MODE_EXPERT,
    SPIDER_MODE_HARD,
};

enum STATISTICS_ITEM_TYPE
{
    STATISTICS_ITEM1 = 0,
    STATISTICS_ITEM2,
    STATISTICS_ITEM3,
    STATISTICS_ITEM4,
    STATISTICS_ITEM5,
    STATISTICS_ITEM6,
    STATISTICS_ITEM7,
    STATISTICS_ITEM8,
    STATISTICS_ITEM9,
    STATISTICS_ITEM10    
};

class GameData
{
public:
    static GameData* getInstance();
    
protected:
    GameData();
    
private:
    void init();
    
public:
    int getSpiderMode();
    void setSpiderMode(int mode);
    
    int getGameType();
    void setGameType(int type);
    
    int getCustomOrientation();
    void setCustomOrientation(int customOrientation);
    
    bool getTimeMove();
    void setTimeMove(bool timeMove);
    
    int getCardBackIndex();
    void setCardBackIndex(int cardBackIndex);
    
    int getCardFaceIndex();
    void setCardFaceIndex(int cardFaceIndex);
    
    int getBackgroundIndex();
    void setBackgroundIndex(int backgroundIndex);    
    
    bool isRightHanded();
    void setRightHanded(bool rightHanded);
    
    bool isDrawFlag();
    void setDrawFlag(bool drawFalg);
    
    bool isVegasMode();
    void setVegasMode(bool vegasMode);
    
    bool isSoundEnabled();
    void setSoundEnabled(bool soundEnabled);
    void playSoundEffect();
    
    bool isEffectEnabled();
    void setEffectEnabled(bool effectEnabled);
    
    bool isBgmEnabled();
    void setBgmEnabled(bool bgmEnabled);
    
    bool isTapMove();
    void setTapMove(bool tapMove);
    
    int getNewGame();
    void setNewGame(int newGame);
    
    double getSelectedGame();
    void setSelectedGame(double selectedGame);
    
    bool isDoingAction();
    void setDoingAction(bool isDoing);
    
    bool isUndoMove();
    void setUndoMove(bool isUndo);
    
    bool isMenuLayer();//from menuLayer
    void setMenuLayer(bool isMenu);
    
    __Array* getCardIndexArray();
    int getInt(std::string key, int defaultValue);
    void setInt(std::string key, int value);
    
    float getFloat(std::string key, float defaultValue);
    void setFloat(std::string key, float value);
    
    std::string getStatisticsItem(std::string keyString, int itemType);
    void deleteStatisticsItem(std::string keyString, int itemType);
    
    int getBannerHeight();
    void setBannerHeight(int bannerHeight);
    
    bool isRemoveAds();
    void setRemoveAds(bool isAds);
    
    bool isShowSetting();
    void setShowSetting(bool isSetting);
    
private:
    static GameData* _instance;
    
    int _spiderMode;
    int _gameType;
    int _customOrientation;
    
    bool _soundEnabled;
    bool _effectEnabled;
    bool _bgmEnabled;
    bool _rightHanded;
    bool _drawFlag;
    bool _vegasMode;
    bool _timeMove;
    bool _tapMove;
    bool _isDoing;
    bool _isUndo;
    bool _isMenu;
    
    bool _isSetting = false;
    
    int _newGame;
    
    double _selectedGame;
    __Array* _cardIndexArray;
    
    int _bannerHeight = 0;    
};

#endif