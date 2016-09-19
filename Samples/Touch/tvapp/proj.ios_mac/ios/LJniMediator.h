//
//  LJniMediator.h
//  CakeJump
//
//  Created by Chen on 9/1/13.
//
//
#ifndef __LJNIMEDIATOR_H__
#define __LJNIMEDIATOR_H__

#include <string>

class LJniMediator
{
public:
	void sendToCocos(int nType, const char* strParam, int nParam);
	bool receivedFromCocos2dx(int nType, std::string strParam, int nParam);
    
    static LJniMediator* sharedInstance();
private:
    LJniMediator();
    ~LJniMediator();
};

#endif //__LJNIMEDIATOR_H__