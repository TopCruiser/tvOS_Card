//
//  SettingLayer.cpp
//  cardgame
//
//  Created by khj on 3/6/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//
#include "SettingLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "MenuLayer.h"
#include "BoardLayer.h"
#include "AppDelegate.h"

CCScene* SettingLayer::scene()
{
    CCScene *scene = CCScene::create();
    SettingLayer *layer = SettingLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SettingLayer::init()
{
    if(!CCLayer::init()) return false;
    
    return true;
}

void SettingLayer::init(CCLayer* parent)
{
    _parentLayer = parent;
    _isEnabled=true;
    
    //_background = CCSprite::create(getNameWithDevice("settingback").c_str());
    _background = CCSprite::create(getNameWithDeviceJpg("settingback").c_str());
    _background->setAnchorPoint(ccp(0.5f, 0.5f));
    _background->setScale(getScaleWithDevice());
    _background->setVisible(false);
    addChild(_background);
    
    _header = CCSprite::create(getNameWithDevice("setting_titlebar").c_str());
    _header->setScale(getScaleWithDevice());
    _header->setAnchorPoint(ccp(0.5f, 0.0f));
    addChild(_header);
    
    _footer = CCSprite::create(getNameWithDevice("bg_taskbar").c_str());
    _footer->setScale(getScaleWithDevice());
    _footer->setAnchorPoint(ccp(0.5f, 0.0f));
    _footer->setPosition(ccp(0.0f, 0.0f));
    addChild(_footer);
    
    _buttonbackground = CCSprite::create(getNameWithResolution("setting_buttonback").c_str());
    _buttonbackground->setAnchorPoint(ccp(0.5, 0.5));
    _buttonbackground->setScale(getScaleWithDevice());
    addChild(_buttonbackground);
    
    _title=CCSprite::create(getNameWithResolution("setting").c_str());
    _title->setAnchorPoint(ccp(0.5f, 0.5f));
    _title->setScale(getScaleWithDevice());
    addChild(_title);
        
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    tableView=CCTableView::create(this, CCSizeMake(winSize.width, winSize.height-getSizeWithDevice(190.0f)));
    
    tableView->setDirection(kCCScrollViewDirectionVertical);
    //tableView->setPosition(ccp(-525, -275));
    tableView->setAnchorPoint(ccp(0, 0));
    tableView->setPosition(ccp(0.0f, getSizeWithDevice(95.0f)));
    
    
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    
    this->addChild(tableView,1);
    tableView->reloadData();
    
    btnDone = CCMenuItemSprite::create(CCSprite::create(getNameWithResolution("btn_back_nor").c_str()),
                                       CCSprite::create(getNameWithResolution("btn_back_act").c_str()),
                                       this, menu_selector(SettingLayer::onDone));
    
    btnDone->setAnchorPoint(ccp(0.5f, 0.0f));
    btnDone->setScale(getScaleWithDevice());
    
    CCMenu* _menu = CCMenu::create();
    _menu->addChild(btnDone);
    
    _menu->setPosition(ccp(0.0f, 0.0f));
    addChild(_menu);
}

void SettingLayer::updateLayoutWithPortrait(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _background->setRotation(0.0f);
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(ccp(winSize.width/2.0f, winSize.height-getSizeWithDevice(117)));
    _footer->setPosition(ccp(winSize.width/2.0f, 0));
    
    _title->setPosition(ccp(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    
    tableView->setPosition(ccp(0, getSizeWithDevice(95.0f)));
    
    tableView->setViewSize( CCSizeMake(winSize.width, winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _buttonbackground->setPosition(ccp(winSize.width/2.0f,  getSizeWithDevice(42.0f)));
    btnDone->setPosition(ccp(winSize.width/2.0f,  getSizeWithDevice(20.0f)));
    
    if(_orientationLayer != NULL)
    {
        _orientationLayer->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
        //_orientationLayer->setVisible(true);
    }
    
    //if(_helpLayer != NULL)
    //{
    //    _helpLayer->setPosition(ccp(0.0f, 0.0f));
    //    _helpLayer->updateLayoutWithPortrait();
    //}
    
}

void SettingLayer::updateLayoutWithLandscape(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _background->setRotation(90.0f);
    _background->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(ccp(winSize.width/2.0f, winSize.height - getSizeWithDevice(117)));
    _footer->setPosition(ccp(winSize.width/2.0f, 0));
                         
    _title->setPosition(ccp(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    
    tableView->setPosition(ccp(0, getSizeWithDevice(95.0f)));
    tableView->setViewSize( CCSizeMake(winSize.width, winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _buttonbackground->setPosition(ccp(winSize.width/2.0f,  getSizeWithDevice(42.0f)));
    btnDone->setPosition(ccp(winSize.width/2.0f,  getSizeWithDevice(20.0f)));
    
    if(_orientationLayer != NULL)
    {
        _orientationLayer->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
        //_orientationLayer->setVisible(true);
    }
    
    //if(_helpLayer != NULL)
    //{
    //    _helpLayer->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
    //    _helpLayer->updateLayoutWithLandscape();
    //}
    
}

void SettingLayer::onDone(CCObject* sender)
{
    if(!_isEnabled) return;
    
    GameData::getInstance()->setShowSetting(false);
    
    GameData::getInstance()->playSoundEffect();
    
    BoardLayer::getInstance()->setSetting(false);
    ((GameLayer*)_parentLayer)->hideSettingLayer();
    
    AppDelegate::get()->sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", SHOW_ADMOB);
}

//The number of cell
unsigned int SettingLayer::numberOfCellsInTableView(CCTableView *table)
{
    return 17;
}

//Generate cell
CCTableViewCell* SettingLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    
    //if(!cell)
    //{
        //CCLog("if no cell %d", idx);
        cell = new CCTableViewCell();
        cell->autorelease();
    
    
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite* titleSprite;
        titleSprite= CCSprite::create();
      
        titleSprite->setAnchorPoint(CCPointZero);
        titleSprite->setPosition(ccp(winSize.width/2, getSizeWithDevice(20)));
        titleSprite->setTag(123);
    
        CCLabelTTF* _cellLabel = CCLabelTTF::create("", "ClarendonBT-Roman", getSizeWithDevice(30));
    
        _cellLabel->setColor(ccc3(255, 255, 255));
        _cellLabel->setAnchorPoint(CCPointZero);
        _cellLabel->setPosition(ccp(getSizeWithDevice(100),0));
    
    
    
        float iconX=winSize.width-getSizeWithDevice(142.0f);
    
    CCSprite* _iconSprite = CCSprite::create(getNameWithResolution("btn_go").c_str());
    _iconSprite->setAnchorPoint(CCPointZero);
    _iconSprite->setPosition(ccp(iconX, 0));
    _iconSprite->setTag(456);
    
    switch (idx) {
        case 0://Controlsbar
            titleSprite->setPosition(ccp(winSize.width/2, getSizeWithDevice(28)));
            titleSprite->initWithFile(getNameWithDevice("setting_controlsbar").c_str());
            cell->addChild(titleSprite);
            break;
            
        case 1:
            _cellLabel->setString("Orientation");
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 2:
            _cellLabel->setString("Sound Effect");
            _iconSprite->setPosition(ccp(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            //Sound
            if(GameData::getInstance()->isSoundEnabled())
                _iconSprite->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 3:
            _cellLabel->setString("Background Music");
            _iconSprite->setPosition(ccp(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            if(GameData::getInstance()->isEffectEnabled())
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 4:
            _cellLabel->setString("Time/Moves");
            _iconSprite->setPosition(ccp(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            if(GameData::getInstance()->getTimeMove())
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 5:
            _cellLabel->setString("Tap To Move");
            _iconSprite->setPosition(ccp(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            if(GameData::getInstance()->isTapMove())
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 6:
            _cellLabel->setString("Right Handed");
            _iconSprite->setPosition(ccp(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            if(GameData::getInstance()->isRightHanded())
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 7:
            //VisualStyle
            titleSprite->initWithFile(getNameWithDevice("setting_visualstylebar").c_str());
            cell->addChild(titleSprite);
            break;
            
        case 8:
        case 9:
        case 10:
            ////////////////////////////
        {
            _iconSprite->setPosition(ccp(iconX, getSizeWithDevice(20)));
            
            CCString* nameString;
            CCSprite* selectedSprite =CCSprite::create();
            
            if (idx == 8) {
                nameString=CCString::createWithFormat("spade%d_13",GameData::getInstance()->getCardFaceIndex()+1);
                selectedSprite->initWithFile(getNameWithResolution(nameString->m_sString).c_str());
                
                _cellLabel->setString("Card Faces");
            }
            else if(idx == 9){
                //Card Back
                if(GameData::getInstance()->getCardBackIndex()<9)
                    nameString=CCString::createWithFormat("card0%d",GameData::getInstance()->getCardBackIndex()+1);
                else
                    nameString=CCString::createWithFormat("card%d",GameData::getInstance()->getCardBackIndex()+1);
                
                selectedSprite->initWithFile(getNameWithResolution(nameString->m_sString).c_str());
                _cellLabel->setString("Card Backs");
            }else {
                //Background
                if(GameData::getInstance()->getBackgroundIndex()<7)
                {
                    nameString=CCString::createWithFormat("background0%d",GameData::getInstance()->getBackgroundIndex()+1);
                    //selectedSprite->initWithFile(getNameWithDevice(nameString->m_sString).c_str());
                    selectedSprite->initWithFile(getNameWithDeviceIpad(nameString->m_sString).c_str());//added by amr
                }
                else{
                    selectedSprite->initWithFile(getNameWithResolution("native_gallery").c_str());
                }
                
                _cellLabel->setString("Backgrounds");
            }
            
            CCSize bgSize= selectedSprite->getContentSize();
            
            float scaleX=getSizeWithDevice(57.0f)/bgSize.width;
            float scaleY=getSizeWithDevice(80.0f)/bgSize.height;
            
            selectedSprite->cocos2d::CCNode::setScale(scaleX, scaleY);
            selectedSprite->setContentSize(CCSizeMake(getSizeWithDevice(57.0f), getSizeWithDevice(80.0f)));
            
            selectedSprite->setAnchorPoint(CCPointZero);
            selectedSprite->setPosition(ccp(getSizeWithDevice(100.0f),getSizeWithDevice(5.0f)));
            selectedSprite->setTag(789);
            
            _cellLabel->setPosition(ccp(getSizeWithDevice(165), getSizeWithDevice(30)));
                                    
            cell->addChild(selectedSprite);
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
        }
            ////////////////////////////
            break;
            
            
        case 11:
            titleSprite->initWithFile(getNameWithDevice("setting_informationbar").c_str());
            cell->addChild(titleSprite);
            break;
        
        case 12:
            _cellLabel->setString("Statistics");
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 13:
            _cellLabel->setString("Tell a Friend");
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
        
        
        case 14:
            _cellLabel->setString("Feedback Email");
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 15:
            _cellLabel->setString("Restore");
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 16:
            _cellLabel->setString("Help");
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
            
                ////////////////////////////////////////////
        
        }
    
    
        
       
    //}
    //else
    //{
    //    CCLog("else  %d", idx);
        //Create and would not need to re create, or you'll find out the picture with the words wrong
    //    CCTexture2D *aTexture=CCTextureCache::sharedTextureCache()->addImage(getNameWithResolution(nameString->m_sString).c_str());
    //    CCSprite *pSprite=(CCSprite *)cell->getChildByTag(123);
    //    pSprite->setTexture(aTexture);
    //}
     
    return cell;
    
}


//CCSize SettingLayer::cellSizeForTable(CCTableView *table)
//{
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    return CCSizeMake(winSize.width-getSizeWithDevice(250.0f), getSizeWithDevice(80.0f));
//    //return CCSizeMake(605, 105);
//}

CCSize SettingLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(idx>7 && idx<11) return CCSizeMake(getSizeWithDevice(250.0f), getSizeWithDevice(120.0f));
    else if(idx== 0) return CCSizeMake(winSize.width-getSizeWithDevice(250.0f), getSizeWithDevice(50.0f));
    else return CCSizeMake(winSize.width-getSizeWithDevice(250.0f), getSizeWithDevice(80.0f));
}

void SettingLayer::tableCellHighlight(CCTableView *table, CCTableViewCell *cell)
{
    
}

void SettingLayer::tableCellUnhighlight(CCTableView *table, CCTableViewCell *cell)
{
    
}

void SettingLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
    if(BoardLayer::getInstance()==NULL) return;
    if(!BoardLayer::getInstance()->getSetting()) return;
    if(!_isEnabled) return;
    
    int idx = cell->getIdx();
    if(idx == 0 || idx == 7 || idx == 11) return;
    
    CCBlink *blink_ = CCBlink::create(0.1f, 1);
    cell->runAction(blink_);
    
    GameData::getInstance()->playSoundEffect();
    
    CCSprite* _iconSprite=(CCSprite *)cell->getChildByTag(456);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float iconX=winSize.width-getSizeWithDevice(142.0f);
    
    switch (idx) {
        case 1:
            //Orientation
            _isEnabled=false;
            
            _orientationLayer = OrientationLayer::create();
            _orientationLayer->init(this);
            _orientationLayer->setAnchorPoint(ccp(0.5f, 0.5f));
            _orientationLayer->setPosition(ccp(winSize.width/2.0f, winSize.height/2.0f));
            addChild(_orientationLayer, 2);
        break;
        
        case 2:
        {
            //Sound
            bool isSound= !GameData::getInstance()->isSoundEnabled();
            GameData::getInstance()->setSoundEnabled(isSound);
            
            if(isSound) _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else _iconSprite->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            _iconSprite->setPosition(ccp(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
        }
        break;
            
        case 3:
        {
            //Animation
            bool isEffect=!GameData::getInstance()->isEffectEnabled();
            GameData::getInstance()->setEffectEnabled(isEffect);
            
            if(isEffect){
                SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            }
            else{
                SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            }
            
            _iconSprite->setPosition(ccp(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
        }
        break;
            
        case 4:
        {
            //Time/Move
            bool isTimeMoves=!GameData::getInstance()->getTimeMove();
            GameData::getInstance()->setTimeMove(isTimeMoves);
            
            if(isTimeMoves){
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
                std::string temp="MOVES:"+to_string(BoardLayer::getInstance()->_totalMoveCount);
                const char *label=temp.c_str();
                BoardLayer::getInstance()->_moveLabel->setString(label);
                //time
                BoardLayer::getInstance()->_timeLabel->setString("TIME:00:00");
            }
            else{
                BoardLayer::getInstance()->_moveLabel->setString("MOVES:0");
                BoardLayer::getInstance()->_timeLabel->setString("TIME:00:00");
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            }
            
            _iconSprite->setPosition(ccp(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
        }
        break;
        
        case 5:
        {
            //TapToMove
            bool tapMove=!GameData::getInstance()->isTapMove();
            GameData::getInstance()->setTapMove(tapMove);
            
            if(tapMove){
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            }
            else{
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            }
            
            _iconSprite->setPosition(ccp(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
            
        }
            break;
            
        case 6:
        {
            //Right Hand
            bool isRightHand=!GameData::getInstance()->isRightHanded();
            GameData::getInstance()->setRightHanded(isRightHand);
            BoardLayer::getInstance()->updateRightHanded();
            if(isRightHand){
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            }
            else{
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            }
            _iconSprite->setPosition(ccp(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
        }
            break;
            
        case 8:
        {
            //change card face
            _isEnabled=false;
            ((GameLayer*)_parentLayer)->showCardFaceLayer();
        }
            break;
            
        case 9:
        {
            //change card back
            _isEnabled=false;
            ((GameLayer*)_parentLayer)->showCardBackLayer();
        }
            break;
            
        case 10:
        {
            //change background
            _isEnabled=false;
            ((GameLayer*)_parentLayer)->showBackgroundLayer();
        }
            break;
            
        case 12:
        {
            //statistics
            _isEnabled=false;
            ((GameLayer*)_parentLayer)->showStatisticsLayer();
        }
            break;
        
        case 13:
        {
            //Tell a Friend
            AppDelegate::get()->sendMessageToNative(MSG_TELL_A_FRIEND, "Tell a Friend", 1);
        }
            break;
            
        case 14:
        {
            //Feedback Email
            AppDelegate::get()->sendMessageToNative(MSG_FEEDBACK_EMAIL, "Feedback Email", 1);
            
        }
            break;
            
        case 15:
        {
            //Feedback Email
            AppDelegate::get()->sendMessageToNative(MSG_RESTORE_REQUEST, "Restore", 1);
            
        }
            break;
            
        case 16:
        {
            //Help
            _isEnabled=false;
            ((GameLayer*)_parentLayer)->showHelpLayer();
        }
            break;
            
        default:
            break;
    }
    
}

void SettingLayer::scrollViewDidScroll(cocos2d::extension::CCScrollView *view)
{
}

void SettingLayer::scrollViewDidZoom(cocos2d::extension::CCScrollView *view)
{
}

void SettingLayer::didFinishCell()
{
    _isEnabled=true;
    _orientationLayer=NULL;    
    tableView->reloadData();
}

bool SettingLayer::getEnabled()
{
    return _isEnabled;
}

void SettingLayer:: setEnabled(bool isEnabled)
{
    _isEnabled=isEnabled;
}
