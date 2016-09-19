/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_TVOS
#import "platform/tvos/CCEAGLView-tvos.h"
#else
#import "platform/ios/CCEAGLView-ios.h"
#endif
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import <Firebase/Firebase.h>

@interface TCocosParam : NSObject
{
    
}
@property (nonatomic)           int nType;
@property (nonatomic, retain)   NSString* strParam;
@property (nonatomic)           int nParam;
@end
@implementation TCocosParam
@synthesize nType;
@synthesize strParam;
@synthesize nParam;
@end

@implementation AppController
{
    BOOL admobBannerEnabled;
    BOOL isRemoveAds;
    BOOL AppLovinHomeScreenEnabled;
    BOOL AppLovinGameStartEnabled;
    BOOL AppLovinNewGameEnabled;
    
    int MESSAGE_ALERT_TYPE;
}

@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    [self loadFirebaseParameters];
    
//    [rootref authUser:@"iospro0712@gmail.com" password:@"iospro0123" withCompletionBlock:^(NSError *error, FAuthData *authData) {
//        if(error == nil){
//            
//        }
//        else {
//            NSLog(@"%@", error.description);
//        }
//    }];
    
    
    [ALSdk initializeSdk];
    
    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
#if CC_TARGET_PLATFORM != CC_PLATFORM_TVOS
    [eaglView setMultipleTouchEnabled:NO];
#endif

    // Use RootViewController manage CCEAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
#if CC_TARGET_PLATFORM != CC_PLATFORM_TVOS
    _viewController.wantsFullScreenLayout = YES;
#endif
    viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    

    [window makeKeyAndVisible];

#if CC_TARGET_PLATFORM != CC_PLATFORM_TVOS
    [[UIApplication sharedApplication] setStatusBarHidden:true];
#endif

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    app->run();

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}

-(bool) receivedFromCocos2dx:(int) nType strParam:(NSString*) strParam intParam:(int) nParam
{
    TCocosParam* cocosParam = [[TCocosParam alloc] init];
    [cocosParam setNType:nType];
    [cocosParam setStrParam:strParam];
    [cocosParam setNParam:nParam];
    [self performSelectorOnMainThread:@selector(receivedFromCocos2dxOnMain:) withObject:cocosParam waitUntilDone:YES];
    
    return YES;
}

-(bool) receivedFromCocos2dxOnMain:(TCocosParam*) cocosParam
{
    int nType = [cocosParam nType];
    NSString* strParam = [cocosParam strParam];
    int nParam = [cocosParam nParam];
    
    MESSAGE_ALERT_TYPE = nType;
    
    bool bRet = true;
    switch (nType) {
//        case MSG_ORIENTATION:
//            [viewController setCocosOrientation:nParam];
//            break;
//            
//        case MSG_SELECTFREECELL:
//            [self showMessageBox:nParam];
//            break;
//            
//        case MSG_TELL_A_FRIEND:
//            //[self sendEMail];
//            [self showTellAFriend];
//            break;
//            
//        case MSG_FEEDBACK_EMAIL:
//            [self sendFeedback];
//            break;
//            
//        case MSG_SUBMIT_SCORE:
//            [self submitLeaderboard:nParam leaderboardID:strParam];
//            break;
//            
//        case MSG_SUBMIT_ACHIEVE:
//            [self submitAchieve:nParam achieveID:strParam];
//            break;
//            
//        case MSG_RANK_ACHIEVE:
//            [self rankAchieve:nParam leaderBoard_ID:strParam];
//            break;
//            
//        case MSG_GAMECENTER:
//            //[self showAchievements];
//            [MBProgressHUD showHUDAddedTo:window animated:YES];
//            [self showLeaderboard:strParam];
//            //[self leaderboardInfo:nParam];
//            break;
//            
//        case MSG_REMOVE_ADS:
//            [MBProgressHUD showHUDAddedTo:window animated:YES];
//            [NSTimer scheduledTimerWithTimeInterval:3
//                                             target:self
//                                           selector:@selector(delayTime)
//                                           userInfo:nil
//                                            repeats:NO];
//            
//            [[LStoreManagerIOS sharedInstance] buyProduct:strParam];
//            break;
//            
//        case MSG_ADMOB_BANNER:
//            if(nParam == 0) [self hideAdmobBanner];
//            else [self showAdmobBanner];
//            break;
            
        case MSG_SHOW_CHARTBOOST:
            [ALInterstitialAd show];
            break;
            
//        case MSG_SHOW_REWARDEDVIDEO:
//            [self showRewardedAdertiseVideo];
//            break;
//            
//        case MSG_GOOGLE_ANALYTICS:
//            [viewController setCurrentSceneWith:strParam];
//            break;
//            
//        case MSG_ADCOLONY_VIDEO:
//            if(!isRemoveAds)
//                [AdColony playVideoAdForZone:@"vz8eef5502199446a399" withDelegate:self withV4VCPrePopup:YES andV4VCPostPopup:YES];
//            break;
//            
//        case MSG_APPIRATER:
//            [self runAppirater];
//            break;
//            
//        case MSG_ASKINGPOINT:
//            [ASKPManager requestCommandsWithTag:strParam];
//            break;
//            
//        case MSG_NATIVE_BACKGROUND:
//            [self getNativeBackground];
//            break;
//            
//        case MSG_SHOW_FACEBOOK:
//            //[MBProgressHUD showHUDAddedTo:window animated:YES];
//            [self showFacebook:strParam];
//            break;
//            
//        case MSG_SHOW_TWITTER:
//            //[MBProgressHUD showHUDAddedTo:window animated:YES];
//            [self showTwitter:strParam];
//            break;
//            
//        case MSG_RESTORE_REQUEST:
//            [MBProgressHUD showHUDAddedTo:window animated:YES];
//            [NSTimer scheduledTimerWithTimeInterval:3
//                                             target:self
//                                           selector:@selector(delayTime)
//                                           userInfo:nil
//                                            repeats:NO];
//            [[LStoreManagerIOS sharedInstance] restore];
//            break;
//            
//        case MSG_SMS:
//            [self showSMS:strParam];
//            break;
//            
//        case MSG_EMAIL:
//            [self sendEMail:strParam];
//            break;
//            
//        case MSG_REMOVE_ALL_ADS:
//            
//            if(nParam == REMOVE_ADMOB){
//                isRemoveAds = true;
//                [self hideAdmobBanner];
//            }else{
//                isRemoveAds = false;
//                [self showAdmobBanner];
//                [self showInterstitialAdvertise:@"Startup"];
//            }
//            
//            break;
            
            
    }
    return bRet;
}

-(void) loadFirebaseParameters{
    
    NSLog(@"Getting the latest config...");
    
    Firebase *rootref = [[Firebase alloc] initWithUrl:@"https://test01-3e67f.firebaseio.com"];
    
    [rootref observeEventType:FEventTypeValue withBlock:^(FDataSnapshot *snapshot) {
        NSLog(@"Yay! Config was fetched from the server.");
        
        NSString *IsApprater = snapshot.value[@"AppRaterEnabled"];
        bool IsEnabled = [IsApprater boolValue];
        //self.AppRaterEnabled = IsEnabled;
        
        NSString *AppRaterUsesstr = snapshot.value[@"AppRaterUsers"];
        int AppRaterUses = [AppRaterUsesstr intValue];
        
        NSString *AppRaterDaysstr = snapshot.value[@"AppRaterDays"];
        int AppRaterDays = [AppRaterDaysstr intValue];
        
        NSString *IsAppLovinHomeScreenEnabledstr = snapshot.value[@"AppLovinHomeScreenEnabled"];
        AppLovinHomeScreenEnabled = [IsAppLovinHomeScreenEnabledstr boolValue];
        
        NSString *IsAppLovinGameStartEnabledstr = snapshot.value[@"AppLovinGameStartEnabled"];
        AppLovinGameStartEnabled = [IsAppLovinGameStartEnabledstr boolValue];
        
        NSString *IsAppLovinNewGameEnabledstr = snapshot.value[@"AppLovinNewGameEnabled"];
        AppLovinNewGameEnabled = [IsAppLovinNewGameEnabledstr boolValue];
        
        if (IsEnabled)
        {
            //Appirater
//            [Appirater setAppId:@"955521457"];
//            [Appirater setDaysUntilPrompt:AppRaterDays];
//            [Appirater setUsesUntilPrompt:AppRaterUses];
//            [Appirater setSignificantEventsUntilPrompt:-1];
//            [Appirater setTimeBeforeReminding:2];
//            [Appirater setDebug:NO];
//            [Appirater appLaunched:YES];
        }
        
    } withCancelBlock:^(NSError *error) {
        NSLog(@"Failed to fetch. Using Cached Config.");
    }];
}

@end
