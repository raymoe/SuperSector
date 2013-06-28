#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Elements.h"

using namespace cocos2d;
using namespace CocosDenshion;

static GameScene* s_GameScene = NULL;

GameScene* GameScene::sharedInstance()
{
    if(s_GameScene == NULL)
        s_GameScene = GameScene::create();
    return s_GameScene;
}

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(GameScene::sharedInstance());
    return scene;
}

bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    _level = 1;
    
    _pGameStrategy = new SimpleGameStrategy();
    _pSelectLevelUI = SelectLevelUI::create();
    if(_pSelectLevelUI->getParent() == NULL)
        this->addChild(_pSelectLevelUI);

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    

    return true;
}

void GameScene::draw()
{
    movedLength += 0.01;
    if(_isGameOver)
    {
        movedLength = 0.0f;
        this->removeChild(_pSectorScene, true);
        _pSelectLevelUI->setVisible(true);
    }
}

void GameScene::gameOver()
{
    _isGameOver = true;
}
void GameScene::startGame()
{
    _isGameOver = false;
    movedLength = accumulateLength = 0.0f;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    this->removeChild(_pSectorScene, true);
    _pSelectLevelUI->setVisible(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}



void GameScene::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLayer::ccTouchEnded(pTouch, pEvent);
}

void GameScene::setSectorScene(SectorScene *scene)
{
    _pSectorScene = scene;
    this->addChild(_pSectorScene);
}


bool SelectLevelUI::GameTitle::init()
{
    _pLabel = CCLabelTTF::create("Super Sector", "Georgia-Bold", 34);
    _pLabel->setColor(ccc3(0xA3,0x44,0xBB));
    this->addChild(_pLabel);
    return CCNode::init();
}

bool SelectLevelUI::LevelBanner::init()
{
    _pLabel = CCLabelTTF::create("Level : 1", "Georgia-Bold", 34);
    _pLabel->setColor(ccc3(0xA3,0x44,0xBB));
    this->addChild(_pLabel);
    return CCNode::init();
}



void SelectLevelUI::LevelBanner::setLevel(int i)
{
    _pLabel->setString(CCString::createWithFormat("Level : %d",i)->getCString());
}

bool SelectLevelUI::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    _pTitle = GameTitle::create();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    _pTitle->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(_pTitle, 1);
    
    _pBanner = LevelBanner::create();
    _pBanner->setPosition( ccp(size.width / 2, size.height/2) );
    this->addChild(_pBanner, 1);
    
    CCMenuItemLabel* pPlayItem = CCMenuItemLabel::create(CCLabelTTF::create("PLAY", "Georgia-Bold", 34), this, menu_selector(SelectLevelUI::menuPlayCallback));
    pPlayItem->setPosition(ccp(size.width/2, size.height/4));
    CCMenu* pPlayMenu = CCMenu::create(pPlayItem,NULL);
    pPlayMenu->setPosition(CCPointZero);
    this->addChild(pPlayMenu);

    
    CCMenuItemLabel* pBackItem = CCMenuItemLabel::create(CCLabelTTF::create("BACK", "Georgia-Bold", 34), this, menu_selector(SelectLevelUI::menuBackCallback));
    pBackItem->setPosition(ccp(size.width/4, size.height/4));
    CCMenu* pBackMenu = CCMenu::create(pBackItem,NULL);
    pBackMenu->setPosition(CCPointZero);
    this->addChild(pBackMenu);
    
    
    CCMenuItemLabel* pNextItem = CCMenuItemLabel::create(CCLabelTTF::create("NEXT", "Georgia-Bold", 34), this, menu_selector(SelectLevelUI::menuNextCallback));
    pNextItem->setPosition(ccp(size.width*3/4, size.height/4));
    CCMenu* pNextMenu = CCMenu::create(pNextItem,NULL);
    pNextMenu->setPosition(CCPointZero);
    this->addChild(pNextMenu);
    
    return true;
}

void SelectLevelUI::menuPlayCallback(CCObject *pSender)
{
    this->setVisible(false);
    //SectorScene如何设计，和Level
    GameScene::sharedInstance()->startGame();
    GameScene::sharedInstance()->getGameStrategy()->reset();
    GameScene::sharedInstance()->setSectorScene( SectorScene::create() );
}

void SelectLevelUI::menuNextCallback(CCObject *pSender)
{
    if(GameScene::sharedInstance()->getLevel() == 4)
        GameScene::sharedInstance()->setLevel(1);
    else
        GameScene::sharedInstance()->setLevel(GameScene::sharedInstance()->getLevel()+1);
    _pBanner->setLevel(GameScene::sharedInstance()->getLevel());
}

void SelectLevelUI::menuBackCallback(CCObject *pSender)
{
    if(GameScene::sharedInstance()->getLevel() == 1)
        GameScene::sharedInstance()->setLevel(4);
    else
        GameScene::sharedInstance()->setLevel(GameScene::sharedInstance()->getLevel()-1);
    _pBanner->setLevel(GameScene::sharedInstance()->getLevel());
}
