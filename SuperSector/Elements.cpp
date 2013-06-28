//
//  TriangleSprite.cpp
//  SuperSector
//
//  Created by ZhouRui on 13-6-17.
//
//

#include "Elements.h"
#include "GameScene.h"
#include "Strategy.h"
#include "Actions.h"
#include "cocos2d.h"
#include <pthread.h>


bool Sprite::init()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    _directAngle = 0.0f;
    _radius = 0.15*size.width/2;
    _baseLength = 20;
    _height = 20;
    _isTouch = false;
    return SpriteFather::init();
}

bool Sprite::isClockwise()
{
    if (_touchPoint.x < CCDirector::sharedDirector()->getWinSize().width /2)
        return false;
    return true;
}
void Sprite::draw()
{
    ccDrawColor4F(1, 1, 1, 1);
    if(_isTouch)
    {
        if(isClockwise())
        {
            _directAngle -= 8;
        }
        else
        {
            _directAngle += 8;
        }
    }
    float cx,cy,tx,ty,cl;
    cx = _radius*cos(CC_DEGREES_TO_RADIANS(_directAngle));
    cy = _radius*sin(CC_DEGREES_TO_RADIANS(_directAngle));
    cl = sqrtf(cx*cx+cy*cy);
    
    tx = cy/cl;
    ty = -cx/cl;

    CCPoint points[] = { CCPoint(cx+_baseLength/2*tx,cy+_baseLength/2*ty), CCPoint(cx-ty*_height,cy+tx*_height), CCPoint(cx-_baseLength/2*tx,cy-_baseLength/2*ty) };
    ccDrawPoly(points, sizeof(points)/sizeof(points[0]), true);
}

void Sprite::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    SpriteFather::onEnter();
}

bool Sprite::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    _isTouch = true;
    _touchPoint = touch->getLocation();
    return true;
}

void Sprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void Sprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _isTouch = false;
}

void Sprite::updateTransform()
{
    
}

void SectorScene::setLevel(int level)
{
    
}

bool SectorScene::init()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(ccp(size.width/2,size.height/2));
    
    SectorLayer* pLayer = SectorLayer::create();
    this->addChild(pLayer);
    

    
    RandomRotateAction* action = RandomRotateAction::create();
    this->runAction(action);
    
    return CCScene::init();
}

void SectorScene::draw()
{
    float r = 0.1;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    ccDrawColor4F(1, 1, 1, 1);
    glLineWidth(2);
    ccDrawCircle(ccp(0,0), r*size.width/2, 360, 50, false);
    
    float l,w,h;
    w = size.width;
    h = size.height;
    l = sqrt(w*w + h*h);
    ccDrawColor4F(1.0,1.0,1.0,1.0);
    for(int i = 0;i < 6;i++)
    {
        ccDrawLine(ccp(r*size.width/2*cos(i*M_PI/3),r*size.width/2*sin(i*M_PI/3)), ccp(l*cos(i*M_PI/3),l*sin(i*M_PI/3)));
    }
    glLineWidth(1);
    
    CCScene::draw();
}

void SectorLayer::scheduleFunc()
{
//    CCActionInterval *jump1 = CCJumpBy::create(4, ccp(0,0), 100, 4);
//    CCActionInterval *jump2 = jump1->reverse();
//    CCSequence* seq = CCSequence::create(jump2, jump1, NULL);
    
    
    
//    while (1) {
//        sleep(3);
//    }
}

bool SectorLayer::init()
{
    Sprite* s = Sprite::create();
    this->addChild(s);
    GameScene::sharedInstance()->setSprite(s);
    
    for(int i = 0; i<=1; i++)
    {
        this->addChild(BarrierGroup::create());
    }
   
    this->schedule(schedule_selector(SectorLayer::scheduleFunc));
    return SectorLayerFather::init();
}

void SectorLayer::draw()
{
    GameScene::sharedInstance()->movedLength += 0.003;
}


Barrier::Barrier(BarrierParam parameter)
    : _parameter(parameter)
{
    //计算得到原始的实际半径长
    _parameter.innerR = _parameter.innerR + GameScene::sharedInstance()->accumulateLength;
    _parameter.outerR = _parameter.outerR + GameScene::sharedInstance()->accumulateLength;
    
    
    BarrierFather::BarrierFather();
}

Barrier::Barrier(float innerRadius,float outerRadius,int start,int end)
{
    _parameter.innerR = innerRadius;
    _parameter.outerR = outerRadius;
    _parameter.start = start;
    _parameter.end = end;
    BarrierFather::BarrierFather();
}


bool Barrier::init()
{
    this->setRotation(-_parameter.start*60);
    return BarrierFather::init();
}

float formatAngle(float angle)
{
    if( angle > 0 )
        return angle - ((int)(angle/360))*360;
    else if( angle < 0 )
        return (((int)((-angle)/360))+1)*360 + angle;
    else
        return angle;
}

bool Barrier::detactCollision()
{
    float innerR,outerR;
    innerR = _parameter.innerR - GameScene::sharedInstance()->movedLength;
    outerR = _parameter.outerR - GameScene::sharedInstance()->movedLength;
    Sprite* s = GameScene::sharedInstance()->getSprite();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if( s->getRadius() >= outerR*size.width/2 || s->getRadius() + s->getHeight() <= innerR*size.width/2 )
        return false;
    float fs = formatAngle(s->getDirectAngle());
    if( 60*_parameter.start <= fs && 60*_parameter.end >= fs )
        return true;
    return false;
}

void Barrier::draw()
{
    float innerR,outerR;
    innerR = _parameter.innerR - GameScene::sharedInstance()->movedLength;
    outerR = _parameter.outerR - GameScene::sharedInstance()->movedLength;
    if(innerR > 0.1)
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        ccDrawColor4B(146, 10, 36, 255);
        ccDrawAnnulus(ccp(0,0), innerR*size.width/2, outerR*size.width/2, CC_DEGREES_TO_RADIANS((_parameter.end-_parameter.start)*60), 20);
        if(detactCollision())
        {
            //GameScene::sharedInstance()->gameOver();
        }
        //在这里做碰撞检测
        
    }
    else if(outerR > 0.1)
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        if(_parameter.outerR > _parameter.innerR)
        {
            ccDrawColor4B(146, 10, 36, 255);
            ccDrawAnnulus(ccp(0,0), innerR*size.width/2, outerR*size.width/2, CC_DEGREES_TO_RADIANS((_parameter.end-_parameter.start)*60), 20);
        }
    }
    else
    {
        this->removeFromParent();
    }
    BarrierFather::draw();
    //glLineWidth(_outerRadius-_innerRadius);效果不好
    //ccDrawArc(ccp(0,0), _innerRadius, CC_DEGREES_TO_RADIANS((_end-_start)*60), 100, false);
    //ccDrawArc(ccp(0,0), _outerRadius, CC_DEGREES_TO_RADIANS((_end-_start)*60), 100, false);
    
}

BarrierGroup::BarrierGroup()
{
    _paramList = GameScene::sharedInstance()->getGameStrategy()->getNextParamList();
    for (BarrierParamList::iterator itr = _paramList->begin(); itr != _paramList->end(); itr++) {
        this->addChild(Barrier::create(*itr));
    }
    BarrierGroupFather::BarrierGroupFather();
}

void BarrierGroup::draw()
{
    if(this->getChildrenCount() == 0)
    {
        this->removeAllChildren();
        _paramList = GameScene::sharedInstance()->getGameStrategy()->getNextParamList();
        for (BarrierParamList::iterator itr = _paramList->begin(); itr != _paramList->end(); itr++) {
            this->addChild(Barrier::create(*itr));
        }
    }
    BarrierGroupFather::draw();
}


