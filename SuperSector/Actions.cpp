//
//  Actions.cpp
//  SuperSector
//
//  Created by ZhouRui on 13-6-19.
//
//

#include "Actions.h"
#include "Strategy.h"
#include "GameScene.h"

bool RandomRotateAction::init()
{
    float time,speed;
    time = GameScene::sharedInstance()->getGameStrategy()->getNextRandomTime();
    speed = GameScene::sharedInstance()->getGameStrategy()->getNextRandomSpeed();
    return this->initWithAction(CCRotateBy::create(time,time*speed));
}

void RandomRotateAction::step(float dt)
{
    m_pInnerAction->step(dt);
    if (m_pInnerAction->isDone())
    {
        m_pInnerAction->release();
        float time,speed;
        time = GameScene::sharedInstance()->getGameStrategy()->getNextRandomTime();
        speed = GameScene::sharedInstance()->getGameStrategy()->getNextRandomSpeed();
        this->initWithAction(CCRotateBy::create(time,time*speed));
        m_pInnerAction->startWithTarget(m_pTarget);
    }

}

RandomRotateAction* RandomRotateAction::create()
{
    RandomRotateAction *pRet = new RandomRotateAction();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}