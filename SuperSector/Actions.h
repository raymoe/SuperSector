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

#define RAND_TIME_MAX 1
#define RAND_ANGLE_MAX 360

class RandomRotateAction : public CCRepeatForever
{
public:
    virtual bool init();
    virtual void step(float dt);
    
    static RandomRotateAction* create();
    
private:
    //inline float createRandomNumber(float max){ srand( (unsigned)time( NULL ) ); int tmp = rand(); return tem-(tem/max)*max}
    inline float createRandomTime()
    {
        //srand( (unsigned)time( NULL ) );
        return (rand()/((float)RAND_MAX)) * RAND_TIME_MAX;
        //return createRandomNumber(RAND_TIME_MAX);
    }
    inline float createRandomAngle()
    {
        //srand( (unsigned)time( NULL ) );
        float res = (rand()/((float)RAND_MAX)-0.5) * RAND_ANGLE_MAX;
        return res;
        //return createRandomNumber(RAND_ANGLE_MAX);
    }
};


#endif /* defined(__SuperSector__Actions__) */
