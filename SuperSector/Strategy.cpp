//
//  Strategy.cpp
//  SuperSector
//
//  Created by ZhouRui on 13-6-21.
//
//

#include "Strategy.h"
#include "GameScene.h"
#include "Elements.h"

#define RAND_TIME_MAX 3

BarrierParamList* SimpleGameStrategy::getNextParamList()
{
    BarrierParamList* list;
    if(_index >= ConfigAndData::sharedInstance()->levelDatas[GameScene::sharedInstance()->getLevel()-1].barrierParamLists.size())
        _index = 0;
    list = &(ConfigAndData::sharedInstance()->levelDatas[GameScene::sharedInstance()->getLevel()-1].barrierParamLists[_index++]);
    GameScene::sharedInstance()->accumulateLength += list->movedLength;
    return list;
}

float SimpleGameStrategy::getNextRandomTime()
{
    float res = ( rand()/((float)RAND_MAX) ) * RAND_TIME_MAX;
    return res;
}

float SimpleGameStrategy::getNextRandomSpeed()
{
    return ( rand()/((float)RAND_MAX) - 0.5) * ConfigAndData::sharedInstance()->levelDatas[GameScene::sharedInstance()->getLevel()-1].maxRotateSpeed;
}

void SimpleGameStrategy::reset()
{
    _index = 0;
}

