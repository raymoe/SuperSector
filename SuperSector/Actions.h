//
//  Actions.h
//  SuperSector
//
//  Created by ZhouRui on 13-6-19.
//
//

#ifndef __SuperSector__Actions__
#define __SuperSector__Actions__

#include <iostream>
#include <stdlib.h>
#include "cocos2d.h"
using namespace cocos2d;


class RandomRotateAction : public CCRepeatForever
{
public:
    virtual bool init();
    virtual void step(float dt);
    
    static RandomRotateAction* create();
};


#endif /* defined(__SuperSector__Actions__) */
