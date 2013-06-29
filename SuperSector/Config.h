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



//关卡数据
class LevelData
{
public:
    int level;
    //场景随机旋转地最大旋转速度
    float maxRotateSpeed;
    BarrierParamLists barrierParamLists;
};

typedef std::vector<LevelData> LevelDataList;

//内容记录在ConfigAndData.xml中
class ConfigAndData
{
public:
    static ConfigAndData* sharedInstance();
    LevelDataList levelDatas;
};

#endif /* defined(__SuperSector__Config__) */
