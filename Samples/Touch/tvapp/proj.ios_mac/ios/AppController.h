#import <UIKit/UIKit.h>
#import "ALSdk.h"
#import "ALInterstitialAd.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;


-(void)loadFirebaseParameters;

@end

