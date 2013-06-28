//
//  Config.h
//  SuperSector
//
//  Created by ZhouRui on 13-6-24.
//
//

#ifndef __SuperSector__Config__
#define __SuperSector__Config__

#include "Elements.h"
#include <vector>




class LevelData
{
public:
    int level;
    BarrierParamLists barrierParamLists;
};

typedef std::vector<LevelData> LevelDataList;

class ConfigAndData
{
public:
    static ConfigAndData* sharedInstance();
    LevelDataList levelDatas;
};

#endif /* defined(__SuperSector__Config__) */
