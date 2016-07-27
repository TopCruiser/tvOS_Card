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

Scene* SettingLayer::scene()
{
    Scene *scene = Scene::create();
    SettingLayer *layer = (SettingLayer*)SettingLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SettingLayer::init()
{
    if(!Layer::init()) return false;
    
    return true;
}

void SettingLayer::init(Layer* parent)
{
    _parentLayer = parent;
    _isEnabled=true;
    
    //_background = Sprite::create(getNameWithDevice("settingback").c_str());
    _background = Sprite::create(getNameWithDeviceJpg("settingback").c_str());
    _background->setAnchorPoint(Vec2(0.5f, 0.5f));
    _background->setScale(getScaleWithDevice());
    _background->setVisible(false);
    addChild(_background);
    
    _header = Sprite::create(getNameWithDevice("setting_titlebar").c_str());
    _header->setScale(getScaleWithDevice());
    _header->setAnchorPoint(Vec2(0.5f, 0.0f));
    addChild(_header);
    
    _footer = Sprite::create(getNameWithDevice("bg_taskbar").c_str());
    _footer->setScale(getScaleWithDevice());
    _footer->setAnchorPoint(Vec2(0.5f, 0.0f));
    _footer->setPosition(Vec2(0.0f, 0.0f));
    addChild(_footer);
    
    _buttonbackground = Sprite::create(getNameWithResolution("setting_buttonback").c_str());
    _buttonbackground->setAnchorPoint(Vec2(0.5, 0.5));
    _buttonbackground->setScale(getScaleWithDevice());
    addChild(_buttonbackground);
    
    _title=Sprite::create(getNameWithResolution("setting").c_str());
    _title->setAnchorPoint(Vec2(0.5f, 0.5f));
    _title->setScale(getScaleWithDevice());
    addChild(_title);
        
    Size winSize = Director::getInstance()->getWinSize();

    tableView=TableView::create(this, Size(winSize.width, winSize.height-getSizeWithDevice(190.0f)));
    
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    //tableView->setPosition(Vec2(-525, -275));
    tableView->setAnchorPoint(Vec2(0, 0));
    tableView->setPosition(Vec2(0.0f, getSizeWithDevice(95.0f)));
    
    
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    
    this->addChild(tableView, 1);
    tableView->reloadData();
    
    btnDone = MenuItemSprite::create(Sprite::create(getNameWithResolution("btn_back_nor").c_str()),
                                       Sprite::create(getNameWithResolution("btn_back_act").c_str()),
                                       this, menu_selector(SettingLayer::onDone));
    
    btnDone->setAnchorPoint(Vec2(0.5f, 0.0f));
    btnDone->setScale(getScaleWithDevice());
    
    Menu* _menu = Menu::create();
    _menu->addChild(btnDone);
    
    _menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(_menu);
}

void SettingLayer::updateLayoutWithPortrait(){
    Size winSize = Director::getInstance()->getWinSize();
    _background->setRotation(0.0f);
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(Vec2(winSize.width/2.0f, winSize.height-getSizeWithDevice(117)));
    _footer->setPosition(Vec2(winSize.width/2.0f, 0));
    
    _title->setPosition(Vec2(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    
    tableView->setPosition(Vec2(0, getSizeWithDevice(95.0f)));
    
    tableView->setViewSize( Size(winSize.width, winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _buttonbackground->setPosition(Vec2(winSize.width/2.0f,  getSizeWithDevice(42.0f)));
    btnDone->setPosition(Vec2(winSize.width/2.0f,  getSizeWithDevice(20.0f)));
    
//    if(_orientationLayer != NULL)
//    {
//        _orientationLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
//        //_orientationLayer->setVisible(true);
//    }comment715
}

void SettingLayer::updateLayoutWithLandscape(){
    Size winSize = Director::getInstance()->getWinSize();
    _background->setRotation(90.0f);
    _background->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
    _background->setVisible(true);
    
    _header->setPosition(Vec2(winSize.width/2.0f, winSize.height - getSizeWithDevice(117)));
    _footer->setPosition(Vec2(winSize.width/2.0f, 0));
                         
    _title->setPosition(Vec2(winSize.width/2, winSize.height-getSizeWithDevice(50)));
    
    tableView->setPosition(Vec2(0, getSizeWithDevice(95.0f)));
    tableView->setViewSize( Size(winSize.width, winSize.height-getSizeWithDevice(190.0f)));
    tableView->reloadData();
    
    _buttonbackground->setPosition(Vec2(winSize.width/2.0f,  getSizeWithDevice(42.0f)));
    btnDone->setPosition(Vec2(winSize.width/2.0f,  getSizeWithDevice(20.0f)));
    
//    if(_orientationLayer != NULL)
//    {
//        _orientationLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
//        //_orientationLayer->setVisible(true);
//    }comment715
}

void SettingLayer::onDone(Ref* sender)
{
    if(!_isEnabled) return;
    
    GameData::getInstance()->setShowSetting(false);
    
    GameData::getInstance()->playSoundEffect();
    
    BoardLayer::getInstance()->setSetting(false);
    ((GameLayer*)_parentLayer)->hideSettingLayer();
    
    //AppDelegate::get()->sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", SHOW_ADMOB);
}

//The number of cell
ssize_t SettingLayer::numberOfCellsInTableView(TableView *table)
{
    return 17;
}

//Generate cell
TableViewCell* SettingLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    
    //if(!cell)
    //{
        //CCLog("if no cell %d", idx);
        cell = new TableViewCell();
        cell->autorelease();
    
    
        Size winSize = Director::getInstance()->getWinSize();
        Sprite* titleSprite;
        titleSprite= Sprite::create();
      
        titleSprite->setAnchorPoint(Vec2(0, 0));
        titleSprite->setPosition(Vec2(winSize.width/2, getSizeWithDevice(20)));
        titleSprite->setTag(123);
    
        CCLabelTTF* _cellLabel = CCLabelTTF::create("", "ClarendonBT-Roman", getSizeWithDevice(30));
    
        _cellLabel->setColor(Color3B(255, 255, 255));
        _cellLabel->setAnchorPoint(Vec2(0, 0));
        _cellLabel->setPosition(Vec2(getSizeWithDevice(100),0));
    
    
    
        float iconX=winSize.width-getSizeWithDevice(142.0f);
    
    Sprite* _iconSprite = Sprite::create(getNameWithResolution("btn_go").c_str());
    _iconSprite->setAnchorPoint(Vec2(0, 0));
    _iconSprite->setPosition(Vec2(iconX, 0));
    _iconSprite->setTag(456);
    
    switch (idx) {
        case 0://Controlsbar
            titleSprite->setPosition(Vec2(winSize.width/2, getSizeWithDevice(28)));
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
            _iconSprite->setPosition(Vec2(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
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
            _iconSprite->setPosition(Vec2(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            if(GameData::getInstance()->isEffectEnabled())
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 4:
            _cellLabel->setString("Time/Moves");
            _iconSprite->setPosition(Vec2(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            if(GameData::getInstance()->getTimeMove())
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 5:
            _cellLabel->setString("Tap To Move");
            _iconSprite->setPosition(Vec2(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
            if(GameData::getInstance()->isTapMove())
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            cell->addChild(_cellLabel);
            cell->addChild(_iconSprite);
            break;
            
        case 6:
            _cellLabel->setString("Right Handed");
            _iconSprite->setPosition(Vec2(iconX + getSizeWithDevice(20), getSizeWithDevice(20)));
            
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
            _iconSprite->setPosition(Vec2(iconX, getSizeWithDevice(20)));
            
            __String* nameString;
            Sprite* selectedSprite =Sprite::create();
            
            if (idx == 8) {
                nameString=__String::createWithFormat("spade%d_13",GameData::getInstance()->getCardFaceIndex()+1);
                selectedSprite->initWithFile(getNameWithResolution(nameString->_string).c_str());
                
                _cellLabel->setString("Card Faces");
            }
            else if(idx == 9){
                //Card Back
                if(GameData::getInstance()->getCardBackIndex()<9)
                    nameString=__String::createWithFormat("card0%d",GameData::getInstance()->getCardBackIndex()+1);
                else
                    nameString=__String::createWithFormat("card%d",GameData::getInstance()->getCardBackIndex()+1);
                
                selectedSprite->initWithFile(getNameWithResolution(nameString->_string).c_str());
                _cellLabel->setString("Card Backs");
            }else {
                //Background
                if(GameData::getInstance()->getBackgroundIndex()<7)
                {
                    nameString=__String::createWithFormat("background0%d",GameData::getInstance()->getBackgroundIndex()+1);
                    //selectedSprite->initWithFile(getNameWithDevice(nameString->m_sString).c_str());
                    selectedSprite->initWithFile(getNameWithDeviceIpad(nameString->_string).c_str());//added by amr
                }
                else{
                    selectedSprite->initWithFile(getNameWithResolution("native_gallery").c_str());
                }
                
                _cellLabel->setString("Backgrounds");
            }
            
            Size bgSize= selectedSprite->getContentSize();
            
            float scaleX=getSizeWithDevice(57.0f)/bgSize.width;
            float scaleY=getSizeWithDevice(80.0f)/bgSize.height;
            
            selectedSprite->cocos2d::Node::setScale(scaleX, scaleY);
            selectedSprite->setContentSize(Size(getSizeWithDevice(57.0f), getSizeWithDevice(80.0f)));
            
            selectedSprite->setAnchorPoint(Vec2(0, 0));
            selectedSprite->setPosition(Vec2(getSizeWithDevice(100.0f),getSizeWithDevice(5.0f)));
            selectedSprite->setTag(789);
            
            _cellLabel->setPosition(Vec2(getSizeWithDevice(165), getSizeWithDevice(30)));
                                    
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
    //    Sprite *pSprite=(Sprite *)cell->getChildByTag(123);
    //    pSprite->setTexture(aTexture);
    //}
     
    return cell;
    
}

cocos2d::Size SettingLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size winSize = Director::getInstance()->getWinSize();
    if(idx>7 && idx<11) return Size(getSizeWithDevice(250.0f), getSizeWithDevice(120.0f));
    else if(idx== 0) return Size(winSize.width-getSizeWithDevice(250.0f), getSizeWithDevice(50.0f));
    else return Size(winSize.width-getSizeWithDevice(250.0f), getSizeWithDevice(80.0f));
}

void SettingLayer::tableCellTouched(TableView *table, TableViewCell *cell)
{
    if(BoardLayer::getInstance()==NULL) return;
    if(!BoardLayer::getInstance()->getSetting()) return;
    if(!_isEnabled) return;
    
    long idx = cell->getIdx();
    if(idx == 0 || idx == 7 || idx == 11) return;
    
    Blink *blink_ = Blink::create(0.1f, 1);
    cell->runAction(blink_);
    
    GameData::getInstance()->playSoundEffect();
    
    Sprite* _iconSprite=(Sprite*)cell->getChildByTag(456);
    Size winSize = Director::getInstance()->getWinSize();
    float iconX=winSize.width-getSizeWithDevice(142.0f);
    
    switch (idx) {
        case 1:
            //Orientation
            _isEnabled=false;
            
//            _orientationLayer = OrientationLayer::create();
//            _orientationLayer->init(this);
//            _orientationLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
//            _orientationLayer->setPosition(Vec2(winSize.width/2.0f, winSize.height/2.0f));
//            addChild(_orientationLayer, 2);comment715
        break;
        
        case 2:
        {
            //Sound
            bool isSound= !GameData::getInstance()->isSoundEnabled();
            GameData::getInstance()->setSoundEnabled(isSound);
            
            if(isSound) _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            else _iconSprite->initWithFile(getNameWithResolution("setting_check_off").c_str());
            
            _iconSprite->setPosition(Vec2(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
        }
        break;
            
        case 3:
        {
            //Animation
            bool isEffect=!GameData::getInstance()->isEffectEnabled();
            GameData::getInstance()->setEffectEnabled(isEffect);
            
            if(isEffect){
                //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true); comment715
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_on").c_str());
            }
            else{
                //SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(); comment715
                _iconSprite ->initWithFile(getNameWithResolution("setting_check_off").c_str());
            }
            
            _iconSprite->setPosition(Vec2(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
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
            
            _iconSprite->setPosition(Vec2(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
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
            
            _iconSprite->setPosition(Vec2(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
            
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
            _iconSprite->setPosition(Vec2(iconX+_iconSprite->getContentSize().width/2, _iconSprite->getContentSize().height/2));
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
            //AppDelegate::get()->sendMessageToNative(MSG_TELL_A_FRIEND, "Tell a Friend", 1);comment715
        }
            break;
            
        case 14:
        {
            //Feedback Email
            //AppDelegate::get()->sendMessageToNative(MSG_FEEDBACK_EMAIL, "Feedback Email", 1);//comment715
            
        }
            break;
            
        case 15:
        {
            //Feedback Email
            //AppDelegate::get()->sendMessageToNative(MSG_RESTORE_REQUEST, "Restore", 1);comment715
            
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

void SettingLayer::didFinishCell()
{
    _isEnabled=true;
    //_orientationLayer=NULL;comment715
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

void SettingLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    
}
void SettingLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    
}
void SettingLayer::tableCellWillRecycle(TableView* table, TableViewCell* cell)
{
    
}

//Size SettingLayer::cellSizeForTable(TableView *table){return Size(100, 100);}

