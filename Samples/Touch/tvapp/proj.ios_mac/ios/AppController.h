#import <GameKit/GameKit.h>
#import "GameCenterManager.h"
#import <UIKit/UIKit.h>
#import "ALSdk.h"
#import "ALInterstitialAd.h"
#import "LStoreManagerIOS.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, GKGameCenterControllerDelegate, GameCenterManagerDelegate, LPurchaseDelegateIOS> {
    UIWindow *window;
    GameCenterManager *gameCenterManager;
    
    BOOL adDisplaying;
}

@property(nonatomic, readonly) RootViewController* viewController;

-(void)loadFirebaseParameters;
//ProgressBar
-(void)delayTime;


@end

