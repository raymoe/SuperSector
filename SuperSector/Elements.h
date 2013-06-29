//
//  TriangleSprite.h
//  SuperSector
//
//  Created by ZhouRui on 13-6-17.
//
//

#ifndef __SuperSector__Elements__
#define __SuperSector__Elements__
#include "cocos2d.h"


using namespace cocos2d;

/*just for test*/
#define SpriteFather CCScene
#define SectorLayerFather CCScene
#define BarrierFather CCNode
#define BarrierGroupFather CCNode


class Sprite : public SpriteFather,public CCTargetedTouchDelegate
{
private:
    float _baseLength;
    float _height;
    float _directAngle;
    float _radius;
    bool _isTouch;
    CCPoint _touchPoint;
    CCPoint _currentPoint;
    CCPoint _fVec;
    bool isClockwise();
public:
    inline float getDirectAngle(){ return _directAngle; }
    inline float getRadius(){ return _radius; }
    inline float getBaseLength(){ return _baseLength; }
    inline float getHeight(){ return _height; }
    //Sprite();
    virtual bool init();
    virtual void draw();
    virtual void onEnter();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    CREATE_FUNC(Sprite);
};

//设法将此类抽象出一个接口
class SectorScene : public CCScene
{
private:
    CCTimer timer;
public:
    virtual bool init();
    virtual void draw();
    CREATE_FUNC(SectorScene);
};


class SectorLayer : public SectorLayerFather
{
private:
    void scheduleFunc();
public:
    virtual bool init();
    virtual void draw();
    CREATE_FUNC(SectorLayer);
};

struct BarrierParam
{
    float innerR;
    float outerR;
    int start;
    int end;
};

class BarrierParamList : public std::vector<BarrierParam>
{
public:
    float movedLength;
};

//typedef std::vector<BarrierParam> BarrierParamList;
typedef std::vector<BarrierParamList> BarrierParamLists;


//对于游戏节奏的控制有一些帮助作用
class BarrierGroup : public BarrierGroupFather
{
private:
    BarrierParamList* _paramList;
    int _liveChildrenCount;
public:
    BarrierGroup();
    //virtual bool init();
    virtual void draw();
    inline void decreaseLiveChildrenCount(){_liveChildrenCount--;}
    CREATE_FUNC(BarrierGroup);
};

class Barrier : public BarrierFather {
private:
    BarrierGroup* _parent;
    BarrierParam _parameter;
    ccColor4B _color;
    bool _isDisappear;
public:
    Barrier();
    Barrier(BarrierParam parameter);
    Barrier(float innerRadius,float outerRadius,int start,int end);
    virtual bool init();
    virtual void draw();
    bool detactCollision();
    void disappear();
    static Barrier* create()
    {
        Barrier *pRet = new Barrier();
        if (pRet && pRet->init()) 
        { 
            pRet->autorelease(); 
            return pRet; 
        } 
        else 
        { 
            delete pRet; 
            pRet = NULL; 
            return NULL; 
        } 
    }
    
    static Barrier* create(BarrierParam param)
    {
        Barrier *pRet = new Barrier(param);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
};






















#endif 
