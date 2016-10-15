//
//  MyObject.h
//  tvapp
//
//  Created by Foni Rewenig on 10/9/16.
//
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "MyObjective-C-Interface.h"

// An Objective-C class that needs to be accessed from C++
@interface MyObject : NSObject
{
    int someVar;
}

// The Objective-C member function you want to call from C++
//- (void) doSomethingWith:(void *) aParameter;
@end

