#include "AppDelegate.h"
#include "LoadLayer.h"
#include "BoardLayer.h"
#include "GameLayer.h"
#include "GameData.h"
#include "LJniMediator.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("tvapp", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("tvapp");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    
//    SimpleAudioEngine::sharedEngine()->preloadEffect("card_shuffle.mp3");
    
    GameData::getInstance()->setCustomOrientation(0);
    GameData::getInstance()->setSoundEnabled(true);
    GameData::getInstance()->setEffectEnabled(false);
    GameData::getInstance()->setTimeMove(true);
    
    GameData::getInstance()->setRightHanded(false);
    GameData::getInstance()->setTapMove(true);
    GameData::getInstance()->setDoingAction(false);
    //GameData::getInstance()->setBackgroundIndex(0);
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();

    register_all_packages();
    // create a scene. it's an autorelease object
    auto scene = LoadLayer::scene();

    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
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
                
                CCSize winSize  = Director::getInstance()->getWinSize();
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
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_TVOS)
    return LJniMediator::sharedInstance()->receivedFromCocos2dx(nType, msg, nParam);
#else
    return false;
#endif //CC_TARGET_PLATFORM
}
