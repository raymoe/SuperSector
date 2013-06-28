#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Strategy.h"

using namespace cocos2d;

class SectorScene;

class SelectLevelUI : public cocos2d::CCLayer
{
private:
    class GameTitle : public CCNode
    {
    private:
        CCLabelTTF* _pLabel;
    public:
        virtual bool init();
        CREATE_FUNC(GameTitle);
    };
    class LevelBanner : public CCNode
    {
    private:
        CCLabelTTF* _pLabel;
    public:
        void setLevel(int i);
        virtual bool init();
        CREATE_FUNC(LevelBanner);
    };
    GameTitle* _pTitle;
    LevelBanner* _pBanner;
    
public:
    //static SelectLevelUI* sharedInstance();
    
    virtual bool init();
    
    void menuPlayCallback(CCObject* pSender);
    void menuBackCallback(CCObject* pSender);
    void menuNextCallback(CCObject* pSender);
    CREATE_FUNC(SelectLevelUI);
};

class GameScene : public cocos2d::CCLayer
{
public:
    static GameScene* sharedInstance();
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    virtual void draw();
    
    virtual void onEnter();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    CREATE_FUNC(GameScene);
    
    void menuCloseCallback(CCObject* pSender);
    void gameOver();
public:
    void setSectorScene(SectorScene* scene);
    inline int getLevel() { return _level; }
    inline void setLevel(int level) { _level = level; }
    inline GameStrategy* getGameStrategy(){return _pGameStrategy;}
    inline Sprite* getSprite(){return _pSprite;}
    inline void setSprite(Sprite* sprite){_pSprite = sprite;}
    void startGame();
    float movedLength;
    float accumulateLength;
private:
    SelectLevelUI* _pSelectLevelUI;
    SectorScene* _pSectorScene;
    GameStrategy* _pGameStrategy;
    Sprite* _pSprite;
    int _level;
    bool _isGameOver;
    
};



#endif // __HELLOWORLD_SCENE_H__
