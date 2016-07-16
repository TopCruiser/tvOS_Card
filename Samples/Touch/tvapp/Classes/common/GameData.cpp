//
//  GameData.cpp
//  cardgame
//
//  Created by Pink on 2/3/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "GameData.h"

GameData* GameData::_instance = NULL;

GameData* GameData::getInstance()
{
    if(_instance == NULL)
        _instance = new GameData();
    
    return _instance;
}

GameData::GameData()
{
    init();
}

void GameData::init()
{
    _spiderMode = SPIDER_MODE_NORMAL;
    _gameType = TYPE_SOLITAIRE;
    _rightHanded = false;
    _drawFlag = true;
    _vegasMode = false;
    _effectEnabled = true;
    _bgmEnabled = false;
    _cardIndexArray = new Array;
}

int GameData::getSpiderMode()
{
    return _spiderMode;
}

void GameData::setSpiderMode(int mode)
{
    _spiderMode = mode;
}

int GameData::getGameType()
{
    return _gameType;
}

void GameData::setGameType(int type)
{
    _gameType = type;
}

int GameData::getCustomOrientation()
{
    return _customOrientation;
}

void GameData::setCustomOrientation(int customOrientation)
{
    _customOrientation = customOrientation;
}

bool GameData::getTimeMove()
{
    return _timeMove;
}
void GameData::setTimeMove(bool timeMove)
{
    _timeMove=timeMove;
}

int GameData::getCardBackIndex()
{
    return getInt("cardBackIndex", 1);//set default card back index
}

void GameData::setCardBackIndex(int cardBackIndex)
{
    setInt("cardBackIndex", cardBackIndex);
}

int GameData::getCardFaceIndex()
{
    return getInt("cardFaceIndex", 0);
}
void GameData::setCardFaceIndex(int cardFaceIndex)
{    
    setInt("cardFaceIndex", cardFaceIndex);
}

int GameData::getBackgroundIndex()
{
    return getInt("backgroundIndex", 0);
}
void GameData::setBackgroundIndex(int backgroundIndex)
{
    setInt("backgroundIndex", backgroundIndex);
}

bool GameData::isRightHanded()
{
    return _rightHanded;
}

void GameData::setRightHanded(bool rightHanded)
{
    _rightHanded = rightHanded;
}

bool GameData::isDrawFlag()
{
    return _drawFlag;
}

void GameData::setDrawFlag(bool drawFalg)
{
    _drawFlag = drawFalg;
}

bool GameData::isVegasMode()
{
    return _vegasMode;
}

void GameData::setVegasMode(bool vegasMode)
{
    _vegasMode = vegasMode;
}

bool GameData::isSoundEnabled()
{
    return _soundEnabled;
}

void GameData::setSoundEnabled(bool soundEnabled)
{
    _soundEnabled = soundEnabled;
}

void GameData::playSoundEffect()
{
    if(_soundEnabled){
        //SimpleAudioEngine::sharedEngine()->playEffect("jump.wav");  commented 716
    }
}


bool GameData::isEffectEnabled()
{
    return _effectEnabled;
}

void GameData::setEffectEnabled(bool effectEnabled)
{
    _effectEnabled = effectEnabled;
}

bool GameData::isBgmEnabled()
{
    return _bgmEnabled;
}

void GameData::setBgmEnabled(bool bgmEnabled)
{
    _bgmEnabled = bgmEnabled;
}

bool GameData::isTapMove()
{
    return _tapMove;
}

void GameData::setTapMove(bool tapMove)
{
    _tapMove = tapMove;
}

int GameData::getNewGame()
{
    return _newGame;
}

void GameData::setSelectedGame(double selectedGame)
{
    _selectedGame = selectedGame;
}

double GameData::getSelectedGame()
{
    return _selectedGame;
}

void GameData::setNewGame(int newGame)
{
    _newGame = newGame;
}

bool GameData::isDoingAction()
{
    return _isDoing;
}

void GameData::setDoingAction(bool isDoing)
{
    _isDoing = isDoing;
}

bool GameData::isUndoMove()
{
    return _isUndo;
}

void GameData::setUndoMove(bool isUndo)
{
    _isUndo = isUndo;
}

bool GameData::isMenuLayer()
{
    return _isMenu;
}

void GameData::setMenuLayer(bool isMenu)
{
    _isMenu = isMenu;
}

CCArray* GameData::getCardIndexArray()
{
    return _cardIndexArray;
}

int GameData::getInt(std::string key, int defaultValue)
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(key.c_str(), defaultValue);
}

void GameData::setInt(std::string key, int value)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey(key.c_str(), value);
}

float GameData::getFloat(std::string key, float defaultValue)
{
    return CCUserDefault::sharedUserDefault()->getFloatForKey(key.c_str(), defaultValue);
}

void GameData::setFloat(std::string key, float value)
{
    CCUserDefault::sharedUserDefault()->setFloatForKey(key.c_str(), value);
}

std::string GameData::getStatisticsItem(std::string keyString, int itemType)
{
    char tempStr[32] = "";
    switch(itemType)
    {
        case STATISTICS_ITEM1:
        {
            int Wins = getInt(keyString + "Wins", 0);// Winds? Wins?
            sprintf(tempStr, "%d", Wins);
            break;
        }
        case STATISTICS_ITEM2:
        {
            int Lost = getInt(keyString + "lost", 0);
            sprintf(tempStr, "%d", Lost);
            break;
        }
        case STATISTICS_ITEM3:
        {
            int shortTime = (int)getFloat(keyString + "shortTime", 0);
            sprintf(tempStr, "%2d:%2d", shortTime/60, shortTime%60);
            break;
        }
        case STATISTICS_ITEM4:
        {
            int avgTime = (int)getFloat(keyString + "averageTime", 0);
            sprintf(tempStr, "%2d:%2d", avgTime/60, avgTime%60);
            break;
        }
        case STATISTICS_ITEM5:
        {
            int longTime = (int)getFloat(keyString + "longTime", 0);
            sprintf(tempStr, "%2d:%2d", longTime/60, longTime%60);
            break;
        }
        case STATISTICS_ITEM6:
        {
            int withoutUndo = getInt(keyString + "withoutUndo", 0);
            sprintf(tempStr, "%d", withoutUndo);
            break;
        }
        case STATISTICS_ITEM7:
        {
            int highScore = getInt(keyString + "highscore", 0);
            sprintf(tempStr, "%d", highScore);
            break;
        }
        case STATISTICS_ITEM8:
        {
            if(keyString == "Draw3" || keyString == "Draw1")
            {
                int vegasScore = getInt(keyString + "VegasScore", 0);
                sprintf(tempStr, "%d", vegasScore);
            }
            else
            {
                int winningMoves = getInt(keyString + "winningMoves", 0);
                sprintf(tempStr, "%d", winningMoves);
            }
            break;
        }
        case STATISTICS_ITEM9:
        {
            int currentStreak = getInt(keyString + "currentStreak", 0);
            sprintf(tempStr, "%d", currentStreak);
            break;
        }
        case STATISTICS_ITEM10:
        {
            int LongStreak = getInt(keyString + "longStreak", 0);
            sprintf(tempStr, "%d", LongStreak);
            break;
        }
        default:
            break;
    }
    
    return tempStr;
}

void GameData::deleteStatisticsItem(std::string keyString, int itemType)
{
    switch(itemType)
    {
        case STATISTICS_ITEM1:
            setInt(keyString + "Wins", 0);
            break;
        case STATISTICS_ITEM2:
            setInt(keyString + "lost", 0);
            break;
        case STATISTICS_ITEM3:
            setFloat(keyString + "shortTime", 0);
            break;
        case STATISTICS_ITEM4:
            setFloat(keyString + "averageTime", 0);
            break;
        case STATISTICS_ITEM5:
            setFloat(keyString + "longTime", 0);
            break;
        case STATISTICS_ITEM6:
            setInt(keyString + "withoutUndo", 0);
            break;
        case STATISTICS_ITEM7:
            setInt(keyString + "highscore", 0);
            break;
        case STATISTICS_ITEM8:
            if(keyString == "Draw3" || keyString == "Draw1")
                setInt(keyString + "VegasScore", 0);
            else
                setInt(keyString + "winningMoves", 0);
            break;
        case STATISTICS_ITEM9:
            setInt(keyString + "currentStreak", 0);
            break;
        case STATISTICS_ITEM10:
            setInt(keyString + "longStreak", 0);
            break;
        default:
            break;
    }
}

int GameData::getBannerHeight()
{
    return _bannerHeight;
}

void GameData::setBannerHeight(int bannerHeight)
{
    _bannerHeight = bannerHeight;
}

bool GameData::isRemoveAds(){
    
    int i = getInt("removeAds", 0);
    
    if(i==0) return false;
    else return true;
}

void GameData::setRemoveAds(bool isAds){
    
    if(isAds) setInt("removeAds", 1);
    else setInt("removeAds", 0);    
}

bool GameData::isShowSetting(){
    return _isSetting;
}

void GameData::setShowSetting(bool isSetting){
    _isSetting = isSetting;
}