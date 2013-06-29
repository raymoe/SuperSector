//
//  Strategy.h
//  SuperSector
//
//  Created by ZhouRui on 13-6-21.
//
//

#ifndef __SuperSector__Strategy__
#define __SuperSector__Strategy__

#include "Config.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

class BarrierParam;
class BarrierGroup;

class GameStrategy
{
public:
    virtual void reset() = 0;
    virtual BarrierParamList* getNextParamList() = 0;
    virtual float getNextRandomTime() = 0;
    virtual float getNextRandomSpeed() = 0;
    //virtual BarrierGroup* createBarrierGroup() = 0;
};

class SimpleGameStrategy : public GameStrategy
{
private:
    int _index;
    
public:
    virtual void reset();
    virtual BarrierParamList* getNextParamList();
    virtual float getNextRandomTime();
    virtual float getNextRandomSpeed();
    //virtual BarrierGroup* createBarrierGroup();
};

#endif /* defined(__SuperSector__Strategy__) */
