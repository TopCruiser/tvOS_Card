/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#import "RootViewController.h"
#import "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_TVOS
#import "platform/tvos/CCEAGLView-tvos.h"
#else
#import "platform/ios/CCEAGLView-ios.h"
#endif

USING_NS_CC;

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    
}


- (void)dealloc {
    [super dealloc];
}

-(void)pressesBegan:(NSSet*)presses withEvent:(UIPressesEvent *)event {
    
    UIPress* p = [presses anyObject];
    
    //if (p.type == UIPressTypeSelect)
    if(p.type == UIPressTypeSelect)
    {
        Scene *pScene = Director::getInstance()->getRunningScene();
        Layer *layer = (Layer*)(pScene->getChildren().at(1));
        long tag = layer->getTag();
        
        String* s = String::create(layer->getName().c_str());
        
        
        if(tag == 100)
        {
            MenuLayer* menuLayer = dynamic_cast<MenuLayer*>(layer);
            [self setNeedsFocusUpdate];
        }
        else if(tag == 101)
        {
            //BoardLayer* boardLayer = dynamic_cast<BoardLayer*>(layer);
        }
    }
}
//
//- (UIView *)preferredFocusedView
//{
//    Scene *pScene = Director::getInstance()->getRunningScene();
//    Layer *layer = (Layer*)(pScene->getChildren().at(1));
//    long tag = layer->getTag();
//    
//    if(tag == 100)
//    {
//        MenuLayer* menuLayer = dynamic_cast<MenuLayer*>(layer);
//    
//        cocos2d::Rect r = menuLayer->btnSolitaire->getBoundingBox();
//        Vec2 pos = menuLayer->btnSolitaire->getPosition();
//        UIView* view = [[UIView alloc]initWithFrame: CGRectMake(pos.x, pos.y, r.size.width , r.size.height)];
//        return view;
//    }
//    else{
//        return nil;
//    }
//    
//    return self.view.preferredFocusedView;
//    
//}

-(void)pressesEnded:(NSSet*)presses withEvent:(UIPressesEvent *)event {
    
    UIPress* p = [presses anyObject];
    
    if (p.type == UIPressTypeMenu)
    {
        if(cocos2d::Director::getInstance()->getRunningScene()->getName() == "MenuLayer"){
            [super pressesEnded:presses withEvent:event];
        }
    }
}

-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    Scene *pScene = Director::getInstance()->getRunningScene();
    Layer *layer = (Layer*)(pScene->getChildren().at(1));
    long tag = layer->getTag();
}
@end
