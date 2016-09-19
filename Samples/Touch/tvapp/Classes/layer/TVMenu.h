//
//  ExitLayer.h
//  cardgame
//
//  Created by lion on 3/25/15.
//  Copyright (c) 2015 Pink. All rights reserved.
//

#ifndef __cardgame__TVMenu__
#define __cardgame__TVMenu__

#include "Common.h"
#import <UIKit/UIKit.h>

class CCFocusableMenuItem
{
private:
    BOOL isEnabled;
    BOOL focused;
    BOOL wantsAngleOfTouch;
    
public:
    virtual BOOL wantsControlOfTouch() = 0;
    virtual void resetFocus() = 0;
    virtual void setAngleOfTouch(float angleInDegrees, BOOL firstAngle, BOOL lastAngle) = 0;
    virtual void activate() = 0;
};

class TVMenu : public cocos2d::Menu
{
public:
    
public:
};

#endif /* defined(__cardgame__TVMenu__) */