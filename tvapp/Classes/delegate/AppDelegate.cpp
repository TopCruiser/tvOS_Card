//
//  AppDelegate.cpp
//  cardgame
//
//  Created by Pink on 2/2/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#include "AppDelegate.h"

#include "Common.h"
#include "LoadLayer.h"
#include "GameData.h"
#include "BoardLayer.h"
#include "GameLayer.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "LJniMediator.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
    /*
     * Class:     com_tumen_LJniMediator
     * Method:    sendToCocos
     * Signature: (Ljava/lang/String;I)V
     */
    JNIEXPORT void JNICALL Java_com_tumen_LJniMediator_sendToCocos
    (JNIEnv *env, jobject obj, jint nType, jstring strParam, jint nParam)
    {
        jboolean isCopy = false;
        const char* chsParam = env->GetStringUTFChars(strParam, &isCopy);
        AppDelegate::get()->receivedFromNative(nType, std::string(chsParam), nParam);
    }
    
#ifdef __cplusplus
}

#endif //__cplusplus
#endif //CC_TARGET_PLATFORM
USING_NS_CC;




AppDelegate::AppDelegate()
{
    _isBanner = false;
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    Director *pDirector = Director::getInstance();
    
    //pDirector->setOpenGLView(CCEGLView::getEAGLView());
    //pDirector->setOpenGLView(GLView::getEAGLView());

    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 60);
    
    //SimpleAudioEngine::sharedEngine()->preloadEffect("card_shuffle.mp3");
    
    GameData::getInstance()->setCustomOrientation(0);
    GameData::getInstance()->setSoundEnabled(true);
    GameData::getInstance()->setEffectEnabled(false);
    GameData::getInstance()->setTimeMove(true);
        
    GameData::getInstance()->setRightHanded(false);
    GameData::getInstance()->setTapMove(true);
    GameData::getInstance()->setDoingAction(false);
    //GameData::getInstance()->setBackgroundIndex(0);
    
    if(GameData::getInstance()->isRemoveAds()) sendMessageToNative(MSG_REMOVE_ALL_ADS, "Remove All Ads!", REMOVE_ADMOB);
    else sendMessageToNative(MSG_REMOVE_ALL_ADS, "Show All Ads!", SHOW_ADMOB);
    
    pDirector->runWithScene(LoadLayer::scene());
    
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
}

void AppDelegate::onOrientationChanged(int orientation) {
    
    if(GameData::getInstance()->isDoingAction()) return;
    
    if(g_nOrientation == orientation) return;//added by khj 04.07.2015
    
    g_nOrientation = orientation;
    
    CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();
    if(currentScene != NULL)
        CCDirector::sharedDirector()->replaceScene(currentScene);
    
}

void AppDelegate::receivedFromNative(int nType, std::string strParam, int nParam)
{
    CCLOG("receivedFromNative %s, %d", strParam.c_str(), nParam);
    
    switch (nType) {
        case MSG_SELECTFREECELL:
        {
            //Select Freecell
            double selectedValue=nParam;
            GameData::getInstance()->setNewGame(3);
            GameData::getInstance()->setSelectedGame(selectedValue);
            BoardLayer::getInstance()->replayGame();
        }
            break;
            
        case MSG_ADMOB_BANNER:
            
            if(GameData::getInstance()->isRemoveAds()){
                GameData::getInstance()->setBannerHeight(0);
                sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", REMOVE_ADMOB);
            }
            else if(GameData::getInstance()->isShowSetting()){
                sendMessageToNative(MSG_ADMOB_BANNER, "GoogleMobileAds", REMOVE_ADMOB);
                
            }else{
                
                CCSize winSize  = CCDirector::sharedDirector()->getWinSize();
                int nativeScreenHeight = atoi(strParam.c_str());
                
                GameData::getInstance()->setBannerHeight(nParam);
                if(nativeScreenHeight > 0)
                    GameData::getInstance()->setBannerHeight(nParam * winSize.height / nativeScreenHeight);
                else{
                    CCLog("Error!, BannerView, Content Height 0");
                }
            }
        
            break;
            
        case MSG_REMOVE_ADS:
            if(nParam ==REMOVE_ADMOB){
                
                GameData::getInstance()->setRemoveAds(true);
                sendMessageToNative(MSG_ADMOB_BANNER, "Remove AdMob Banner", REMOVE_ADMOB);
                
                if(BoardLayer::getInstance() != NULL && GameData::getInstance()->getBannerHeight()>0){
                    ((GameLayer*) BoardLayer::getInstance()->_parentLayer)->upTaskbar(-GameData::getInstance()->getBannerHeight());
                }
                
                ((GameLayer*) BoardLayer::getInstance()->_parentLayer)->getTaskbarLayer()->removeStoreButton();
                GameData::getInstance()->setBannerHeight(0);
                
            }else{
                if(GameData::getInstance()->getBannerHeight() == 0)
                    sendMessageToNative(MSG_ADMOB_BANNER, "Show AdMob Banner", SHOW_ADMOB);
                
                GameData::getInstance()->setRemoveAds(false);
            }
            
            break;
        
    }
}

bool AppDelegate::sendMessageToNative(int nType, const char* msg, int nParam)
{
    CCLOG("send to message %s, %d", msg, nParam);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    {
        CCLOG("send to message2 %s, %d", msg, nParam);
        const char* recvCls = "com/tumen/LJniMediator";
        
        JniMethodInfo methodInfo;
        bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
                                                     recvCls,
                                                     "receivedFromCocos2dx",
                                                     "(ILjava/lang/String;I)Z");
        if(isHave){
            CCLOG("the receivedFromCocos2dx method is exits");
            jstring StringArg = methodInfo.env->NewStringUTF(msg);
            return methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, nType, StringArg, nParam);
        }else{
            CCLOG("the receivedFromCocos2dx method is not exits");
        }
    }
    return false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return LJniMediator::sharedInstance()->receivedFromCocos2dx(nType, msg, nParam);
#else
    return false;
#endif //CC_TARGET_PLATFORM
}
