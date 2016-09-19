//
//  LJniMediator.m
//  CakeJump
//
//  Created by Chen on 9/1/13.
//
//

#include "LJniMediator.h"
#include "AppDelegate.h"
#import "AppController.h"

LJniMediator* LJniMediator::sharedInstance()
{
    static LJniMediator* _instance = NULL;
    if (_instance == NULL)
        _instance = new LJniMediator();
    return _instance;
}

LJniMediator::LJniMediator()
{
    
}
LJniMediator::~LJniMediator()
{
    
}

void LJniMediator::sendToCocos(int nType, const char* strParam, int nParam)
{
    AppDelegate::get()->receivedFromNative(nType, strParam, nParam);
}
bool LJniMediator::receivedFromCocos2dx(int nType, std::string strParam, int nParam)
{
    AppController* app = (AppController*) [UIApplication sharedApplication].delegate;
    return [app receivedFromCocos2dx:nType strParam:[NSString stringWithUTF8String:strParam.c_str()] intParam:nParam];
}
