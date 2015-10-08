// Admob Banner广告
#import "GADBannerView.h"
#import "GADBannerViewDelegate.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, GADBannerViewDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    
    // 将其中一个声明为实例变量
    GADBannerView *bannerView_;
}

@end