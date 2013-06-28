//
//  Actions.cpp
//  SuperSector
//
//  Created by ZhouRui on 13-6-19.
//
//

#include "Actions.h"

bool RandomRotateAction::init()
{
    return this->initWithAction(CCRotateBy::create(createRandomTime(),createRandomAngle()));
}

void RandomRotateAction::step(float dt)
{
    m_pInnerAction->step(dt);
    if (m_pInnerAction->isDone())
    {
        m_pInnerAction->release();
        this->initWithAction(CCRotateBy::create(createRandomTime(),createRandomAngle()));
        m_pInnerAction->startWithTarget(m_pTarget);
//        float diff = m_pInnerAction->getElapsed() - m_pInnerAction->getDuration();
//        m_pInnerAction->startWithTarget(m_pTarget);
//        // to prevent jerk. issue #390, 1247
//        m_pInnerAction->step(0.0f);
//        m_pInnerAction->step(diff);
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