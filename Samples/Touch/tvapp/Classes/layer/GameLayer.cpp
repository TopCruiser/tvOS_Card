//
//  GameLayer.c
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "GameLayer.h"
#include "GameData.h"
#include "AppDelegate.h"

enum LAYER_ORDER {
    ORDER_BACKGROUND = 0,
    ORDER_BOARD = 1,
    ORDER_TASKBAR = 2,
    ORDER_OPTION = 3,
    ORDER_SET = 4,
    BACKGROUND_NATIVE = 7
};

cocos2d::Scene* GameLayer::scene()
{
    Scene* scene = cocos2d::Scene::create();
    GameLayer* layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if(!Layer::init())
        return false;
    
    _isFirstLunch = true;
    _isShowTaskbar = false;       
    
    _background = Sprite::create();
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));
    _background->setScale(getScaleWithDevice());
    _background->setVisible(false);
    addChild(_background, ORDER_BACKGROUND);
    
    _blankBanner = Sprite::create();
    _blankBanner->setAnchorPoint(Vec2(0.5f, 0.5f));
    _blankBanner->setScale(getScaleWithDevice());
    _blankBanner->setContentSize(getContentSize());
    _blankBanner->setVisible(false);
    _blankBanner->initWithFile("banner_ads.png");
    addChild(_blankBanner, ORDER_BOARD);
    
    if(GameData::getInstance()->getBackgroundIndex()<BACKGROUND_NATIVE)
    {
        setBackground(GameData::getInstance()->getBackgroundIndex());
    }
    else {
        setBackground(0);
        ImagePicker::getInstance()->setDelegate(this);
        //AppDelegate::get()->sendMessageToNative(MSG_NATIVE_BACKGROUND, "Set Native Background", 1);comment715
    }
    
    _taskbarLayer = TaskbarLayer::create();
    _taskbarLayer->init(this);
    _taskbarLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _taskbarLayer->setVisible(false);
    addChild(_taskbarLayer, ORDER_TASKBAR);
    
    
    Size winSize = Director::getInstance()->getWinSize();
    _settingLayer = (SettingLayer*)SettingLayer::create();
    _settingLayer->init(this);
    _settingLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _settingLayer->setVisible(false);
    _settingLayer->setPosition(Vec2(-winSize.width, 0));
    addChild(_settingLayer, ORDER_OPTION);
    
    _cardBackLayer = CardBackLayer::create();
    _cardBackLayer->init(this);
    _cardBackLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _cardBackLayer->setVisible(false);
    addChild(_cardBackLayer, ORDER_SET);
    
    _backgroundLayer = BackgroundLayer::create();
    _backgroundLayer->init(this);
    _backgroundLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _backgroundLayer->setVisible(false);
    addChild(_backgroundLayer, ORDER_SET);
    
    _cardFaceLayer = CardFaceLayer::create();
    _cardFaceLayer->init(this);
    _cardFaceLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _cardFaceLayer->setVisible(false);
    addChild(_cardFaceLayer, ORDER_SET);
    
    _statisticsLayer = (StatisticsLayer*)StatisticsLayer::create();
    _statisticsLayer->init(this);
    _statisticsLayer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _statisticsLayer->setVisible(false);
    _statisticsLayer->setPosition(Vec2(winSize.width*2,0));
    addChild(_statisticsLayer, ORDER_SET);
    
    _helpLayer = (HelpLayer*)HelpLayer::create();
    _helpLayer->init(this);
    _helpLayer->setAnchorPoint(Vec2(0.5, 0.5));
    _helpLayer->setVisible(false);
    _helpLayer->setPosition(Vec2(winSize.width*2,0));
    
    addChild(_helpLayer, ORDER_SET);
    
    setTag(101);
    
    return true;
}

void GameLayer::onEnterTransitionDidFinish()
{
    //if(g_nOrientation == ORIENTATION_PORTRAIT || g_nOrientation == ORIENTATION_PORTRAIT_UPSIDEDOWN)
        //updateLayoutWithPortrait();
//    else if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)comment715
        updateLayoutWithLandscape();
    
    if(_isFirstLunch)
    {
        switch (GameData::getInstance()->getGameType()) {
            case TYPE_SOLITAIRE:
                showSolitaireOptionLayer();
                break;
            case TYPE_FREECELL:
                showBoardLayerWithFreecell();
                break;
            case TYPE_FORTY_THIEVES:
                showBoardLayerWithFortythieves();
                break;
            case TYPE_SPIDER:
                showSpiderOptionLayer();
                break;
            default:
                break;
        }

        _isFirstLunch = false;
    }
}

void GameLayer::showBoardLayerWithSolitaire()
{
    _solitaireOptionLayer->removeFromParentAndCleanup(true);
    _solitaireOptionLayer = NULL;
    
    _boardLayer = BoardLayer::create();
    _boardLayer->init(this);
    _boardLayer->setCells(0);
    _boardLayer->setSuits(4);
    _boardLayer->setStacks(7);
    _boardLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
    _boardLayer->setPosition(Vec2(0.0f, 0.0f));
    addChild(_boardLayer, ORDER_BOARD);
    
    _boardLayer->startNewGame();
}

void GameLayer::showBoardLayerWithFreecell()
{
    _boardLayer = BoardLayer::create();
    _boardLayer->init(this);
    _boardLayer->setCells(4);
    _boardLayer->setSuits(4);
    _boardLayer->setStacks(8);
    _boardLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
    _boardLayer->setPosition(Vec2(0.0f, 0.0f));
    addChild(_boardLayer, ORDER_BOARD);
    
    _boardLayer->startNewGame();
}

void GameLayer::showBoardLayerWithFortythieves()
{
    _boardLayer = BoardLayer::create();
    _boardLayer->init(this);
    _boardLayer->setCells(0);
    _boardLayer->setSuits(8);
    _boardLayer->setStacks(10);
    _boardLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
    _boardLayer->setPosition(Vec2(0.0f, 0.0f));
    addChild(_boardLayer, ORDER_BOARD);
    
    _boardLayer->startNewGame();
}

void GameLayer::showBoardLayerWithSpider()
{
    _spiderOptionLayer->removeFromParentAndCleanup(true);
    _spiderOptionLayer = NULL;
    
    _boardLayer = BoardLayer::create();
    _boardLayer->init(this);
    _boardLayer->setCells(0);
    
    switch (GameData::getInstance()->getSpiderMode()) {
        case SPIDER_MODE_EASY:
            _boardLayer->setSuits(1);
            break;
        case SPIDER_MODE_NORMAL:
            _boardLayer->setSuits(2);
            break;
        case SPIDER_MODE_EXPERT://You must add suit 3
            _boardLayer->setSuits(3);
            break;
        case SPIDER_MODE_HARD:
            _boardLayer->setSuits(8);
            break;
        default:
            break;
    }
    
    _boardLayer->setStacks(10);
    _boardLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
    _boardLayer->setPosition(Vec2(0.0f, 0.0f));
    addChild(_boardLayer, ORDER_BOARD);
    
    _boardLayer->startNewGame();    
}

void GameLayer::showTaskbar()
{
    if(_taskbarLayer == NULL)
        return;
    
    _isShowTaskbar = !_isShowTaskbar;
    
    Point position = Vec2(0.0f, 0.0f);
    Size winSize = Director::getInstance()->getWinSize();
    
    int bannerHeight = GameData::getInstance()->getBannerHeight();
    
    if(_isShowTaskbar){
        
        _boardLayer->setInstance(_boardLayer);
        
        position = Vec2(winSize.width/2.0f, bannerHeight);
        _blankBanner->setPosition(Vec2(winSize.width/2, -_blankBanner->getContentSize().height/2+ bannerHeight));
        
        //CCLog("%f", _blankBanner->getContentSize().height);
    }
    else{
        //position = Vec2(winSize.width/2.0f, -_taskbarLayer->getContentSize().height + bannerHeight);
        position = Vec2(winSize.width/2.0f, -_taskbarLayer->getContentSize().height);
        _blankBanner->setPosition(Vec2(winSize.width/2, -_blankBanner->getContentSize().height));
    }
    
    /*
    if(_isShowTaskbar){
     
        position = Vec2(_taskbarLayer->getPositionX(), _taskbarLayer->getPositionY() + _taskbarLayer->getContentSize().height);
    }
    else
        position = Vec2(_taskbarLayer->getPositionX(), _taskbarLayer->getPositionY() - _taskbarLayer->getContentSize().height);
    */
    
    Action* action = MoveTo::create(0.2f, position);
    _taskbarLayer->runAction(action);
}

void GameLayer::upTaskbar(int bannerHeight)
{
    if(_taskbarLayer == NULL)
        return;
    
    Point position = Vec2(0.0f, 0.0f);
    position = Vec2(_taskbarLayer->getPositionX(), _taskbarLayer->getPositionY() + bannerHeight);
    
    _blankBanner->setPosition(Vec2(_blankBanner->getPositionX(), _blankBanner->getPositionY()+bannerHeight));
    
    _taskbarLayer->setPosition(position);
}

void GameLayer::updateLayoutWithPortrait()
{
    Size winSize = Director::getInstance()->getWinSize();

    _background->setRotation(0.0f);
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    //added by KHJ 04/14/2015
    if(GameData::getInstance()->getBackgroundIndex() == BACKGROUND_NATIVE)
    {
        Size bgSize= _background->getContentSize();
        
        float scaleX=winSize.width/bgSize.width;
        float scaleY=winSize.height/bgSize.height;
        
        _background->setScaleX(scaleX);
        _background->setScaleY(scaleY);
        _background->setContentSize(_background->getContentSize());
    }
    //
    
    if(_solitaireOptionLayer != NULL)
    {
        _solitaireOptionLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
        _solitaireOptionLayer->setVisible(true);
    }
    
    if(_spiderOptionLayer != NULL)
    {
        _spiderOptionLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
        _spiderOptionLayer->setVisible(true);
    }
    
    if(_boardLayer != NULL)
        _boardLayer->updateLayoutWithPortrait();
    
    if(_taskbarLayer != NULL)
    {
        int bannerHeight = GameData::getInstance()->getBannerHeight();
        _blankBanner->setVisible(true);
        
        if(_isShowTaskbar){
            _taskbarLayer->setPosition(winSize.width/2.0f, bannerHeight);
            _blankBanner->setPosition(Vec2(winSize.width/2, -_blankBanner->getContentSize().height/2+bannerHeight));
        }
        else{
            _taskbarLayer->setPosition(winSize.width/2.0f, -_taskbarLayer->getContentSize().height);
            _blankBanner->setPosition(Vec2(winSize.width/2, -_blankBanner->getContentSize().height));
        }
        
        _taskbarLayer->updateLayoutWithPortrait();
        _taskbarLayer->setVisible(true);
    }
    
    if(_settingLayer!=NULL){
        _settingLayer->updateLayoutWithPortrait();
    }
    
    if(_cardBackLayer!=NULL){
        _cardBackLayer->updateLayoutWithPortrait();
    }
    
    
    if(_backgroundLayer!=NULL){
        _backgroundLayer->updateLayoutWithPortrait();
    }
    
    if(_cardFaceLayer!=NULL){
        _cardFaceLayer->updateLayoutWithPortrait();
    }
    
    if(_statisticsLayer!=NULL){
        _statisticsLayer->updateLayoutWithPortrait();
    }
    
    if(_helpLayer!=NULL){
        _helpLayer->updateLayoutWithPortrait();
    }
}

void GameLayer::updateLayoutWithLandscape()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _background->setRotation(90.0f);
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    //added by KHJ 04/14/2015
    if(GameData::getInstance()->getBackgroundIndex() == BACKGROUND_NATIVE)
    {
        _background->setRotation(0.0f);
        Size bgSize= _background->getContentSize();
        
        float scaleX=winSize.width/bgSize.width;
        float scaleY=winSize.height/bgSize.height;
        
        _background->setScaleX(scaleX);
        _background->setScaleY(scaleY);
        _background->setContentSize(_background->getContentSize());
    }
    //
    
    if(_solitaireOptionLayer != NULL)
        _solitaireOptionLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
    if(_spiderOptionLayer != NULL)
        _spiderOptionLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));

    if(_boardLayer != NULL)
        _boardLayer->updateLayoutWithLandscape();
    
    if(_taskbarLayer != NULL)
    {
        int bannerHeight = GameData::getInstance()->getBannerHeight();
        _blankBanner->setVisible(true);
        
        if(_isShowTaskbar){
            _taskbarLayer->setPosition(winSize.width/2.0f, bannerHeight);
            _blankBanner->setPosition(Vec2(winSize.width/2, -_blankBanner->getContentSize().height/2+bannerHeight));
        }
        else{
            _taskbarLayer->setPosition(winSize.width/2.0f, -_taskbarLayer->getContentSize().height);
            _blankBanner->setPosition(Vec2(winSize.width/2, -_blankBanner->getContentSize().height));
        }
        _taskbarLayer->updateLayoutWithLandscape();
        _taskbarLayer->setVisible(true);
    }
    
    if(_settingLayer!=NULL){
        _settingLayer->updateLayoutWithLandscape();
    }
    
    if(_cardBackLayer!=NULL){
        _cardBackLayer->updateLayoutWithLandscape();
    }
    
    if(_backgroundLayer!=NULL){
        _backgroundLayer->updateLayoutWithLandscape();
    }
    
    if(_cardFaceLayer!=NULL){
        _cardFaceLayer->updateLayoutWithLandscape();
    }
    
    if(_statisticsLayer!=NULL){
        _statisticsLayer->updateLayoutWithLandscape();
    }
    
    if(_helpLayer!=NULL){
        _helpLayer->updateLayoutWithLandscape();
    }
}

void GameLayer::showSolitaireOptionLayer()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _solitaireOptionLayer = SolitaireOptionLayer::create();
    _solitaireOptionLayer->init(this);
    _solitaireOptionLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
    _solitaireOptionLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    addChild(_solitaireOptionLayer, ORDER_OPTION);
}

void GameLayer::showSpiderOptionLayer()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    _spiderOptionLayer = SpiderOptionLayer::create();
    _spiderOptionLayer->init(this);
    _spiderOptionLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
    _spiderOptionLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    addChild(_spiderOptionLayer, ORDER_OPTION);
}

void GameLayer::showSettingLayer()
{
    GameData::getInstance()->setDoingAction(true);
    
    _settingLayer->setVisible(true);
    MoveTo* action = MoveTo::create(0.3f, Vec2(0,0));
    EaseIn *_easein = EaseIn::create(action,0.3f);
    //Sequence *_sequence  =  Sequence::create(_easein, CCCallFuncND::create(this, callfuncND_selector(GameLayer::doneSettingAnimation), NULL), NULL);
    Sequence *_sequence  =  Sequence::create(_easein, CC_CALLBACK_0(GameLayer::doneSettingAnimation, NULL), NULL);
    _settingLayer->runAction(_sequence);
}

void GameLayer::hideSettingLayer()
{
    GameData::getInstance()->setDoingAction(true);
    
    Size winSize= Director::getInstance()->getWinSize();
    float disappear;
    disappear = winSize.width > winSize.height ? winSize.width : winSize.height;
    
    //CCMoveTo* action = CCMoveTo::create(0.3f, Vec2(-disappear,0));
    MoveTo* action = MoveTo::create(0.3f, Vec2(-1.25 * disappear,0));
    EaseIn *_easein = EaseIn::create(action,0.3f);
    //CCSequence *_sequence  =  CCSequence::create( _easein, CCCallFuncND::create(this, callfuncND_selector(GameLayer::doneSettingAnimation), NULL), NULL);
    Sequence *_sequence  =  Sequence::create(_easein, CC_CALLBACK_0(GameLayer::doneSettingAnimation, NULL), NULL);
    _settingLayer->runAction(_sequence);
}

void GameLayer::doneSettingAnimation()
{
    GameData::getInstance()->setDoingAction(false);
}

void GameLayer::showCardBackLayer(){
    _cardBackLayer->setVisible(true);
}

void GameLayer::showBackgroundLayer(){
    _backgroundLayer->setVisible(true);
}

void GameLayer::showCardFaceLayer(){
    _cardFaceLayer->setVisible(true);
}

void GameLayer::showStatisticsLayer(){
    GameData::getInstance()->setDoingAction(true);
    
    _statisticsLayer->getTableView()->reloadData();
    
    _statisticsLayer->setVisible(true);
    MoveTo* action = MoveTo::create(0.3f, Vec2(0,0));
    EaseIn *_easein = EaseIn::create(action,0.3f);
    Sequence *_sequence  =  Sequence::create(_easein, CC_CALLBACK_0(GameLayer::doneSettingAnimation, NULL), NULL);
    
    _statisticsLayer->runAction(_sequence);
}

void GameLayer::hideStatisticsLayer()
{
    GameData::getInstance()->setDoingAction(true);
    
    Size winSize= Director::getInstance()->getWinSize();
    float disappear;
    disappear = winSize.width > winSize.height ? winSize.width : winSize.height;
    
    MoveTo* action = MoveTo::create(0.3f, Vec2(disappear,0));
    EaseIn *_easein = EaseIn::create(action,0.3f);
    Sequence *_sequence  =  Sequence::create(_easein, CC_CALLBACK_0(GameLayer::doneSettingAnimation, NULL), NULL);
    
    _statisticsLayer->runAction(_sequence);
}

void GameLayer::showHelpLayer(){
    
    GameData::getInstance()->setDoingAction(true);
    
    _helpLayer->setVisible(true);
    MoveTo* action = MoveTo::create(0.3f, Vec2(0,0));
    EaseIn *_easein = EaseIn::create(action,0.3f);
    Sequence *_sequence  =  Sequence::create(_easein, CC_CALLBACK_0(GameLayer::doneSettingAnimation, NULL), NULL);
    
    _helpLayer->runAction(_sequence);    
}

void GameLayer::hideHelpLayer()
{
    GameData::getInstance()->setDoingAction(true);
    
    Size winSize= Director::getInstance()->getWinSize();
    float disappear;
    disappear = winSize.width > winSize.height ? winSize.width : winSize.height;
    
    MoveTo* action = MoveTo::create(0.3f, Vec2(disappear,0));
    EaseIn *_easein = EaseIn::create(action,0.3f);
    Sequence *_sequence  =  Sequence::create(_easein, CC_CALLBACK_0(GameLayer::doneSettingAnimation, NULL), NULL);
    
    _helpLayer->runAction(_sequence);
}

void GameLayer::setBackground(int backgroundIndex){
    
    __String *nameString;
    if(backgroundIndex<9) nameString=__String::createWithFormat("background0%d",backgroundIndex+1);
    else nameString=__String::createWithFormat("background%d",backgroundIndex+1);
    
    //_background->initWithFile(getNameWithDevice(nameString->m_sString).c_str());
    ////_background->setScale(getScaleWithDevice());
    if (backgroundIndex+1 == 8) //added by amr
    {
        _background->initWithFile(getNameWithDevice(nameString->_string).c_str());
    }
    else
    {
        _background->initWithFile(getNameWithDeviceIpad(nameString->_string).c_str()); //added by amr
    }
    
    //////added by amr
    Size wSize = Director::getInstance()->getWinSize();
    float scaleX=0;
    float scaleY=0;
//    if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)
//    {
        scaleX = wSize.width / 2048;
        scaleY = wSize.height / 1536;
        _background->setScaleY(scaleX);
        _background->setScaleX(scaleY);
//    }
//    else
//    {
//        scaleX = wSize.width / 1536;
//        scaleY = wSize.height / 2048;
//        _background->setScaleX(scaleX);
//        _background->setScaleY(scaleY);
//    }comment715
    
    
    //////added by amr
    
    //added by khj 04/14/2015
//    if(g_nOrientation == ORIENTATION_PORTRAIT || g_nOrientation == ORIENTATION_PORTRAIT_UPSIDEDOWN)
//        _background->setRotation(0.0f);
//    else if(g_nOrientation == ORIENTATION_LANDSCAPE_LEFT || g_nOrientation == ORIENTATION_LANDSCAPE_RIGHT)//comment715
        _background->setRotation(90.0f);
    
    Size winSize = Director::getInstance()->getWinSize();
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    
}

void GameLayer::setBackground(Texture2D* result){
    
    //_background->initWithTexture(result);
    _background->setRotation(0.0f);
    _background->setTexture(result);
    Size winSize = Director::getInstance()->getWinSize();
    Size bgSize= _background->getContentSize();
    
    float scaleX=winSize.width/bgSize.width;
    float scaleY=winSize.height/bgSize.height;
        
    _background->setScaleX(scaleX);
    _background->setScaleY(scaleY);
    _background->setContentSize(_background->getContentSize());
}

SettingLayer* GameLayer::getSettingLayer(){
    return _settingLayer;
}

TaskbarLayer* GameLayer::getTaskbarLayer(){
    return _taskbarLayer;
}

void GameLayer::removeOptionLayers(){
    _spiderOptionLayer = NULL;
    _solitaireOptionLayer = NULL;
}

void GameLayer::didFinishPickingWithResult(cocos2d::Texture2D* result){
    CCLog("%s", "GameLayer didFinishPickingWithResult");
    if(result==NULL) return;
    
    setBackground(result);
}