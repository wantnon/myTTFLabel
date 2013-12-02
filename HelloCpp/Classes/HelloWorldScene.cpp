#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
#include "CCControlButton.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

 /*   /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
*/
    /////////////////////////////
    // 3. add your codes below...
    //enable touch
	setTouchEnabled( true );
    //set projection to 2D (default is 3D). if use 3D projection, may cause tiny projection error, in some situation, if the error accumulated across frames, may cause effect wrong.
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    //sinSize
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();//winSize equals to designResolutionSize
    //show frame rate info
    CCDirector::sharedDirector()->setDisplayStats(true);
    
    CCSprite*backGround=CCSprite::create();
    backGround->initWithFile("HelloWorld_iphone5.png");
    backGround->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(backGround);

   
    
    // title
    {
        CmyTTFLabel*label= new CmyTTFLabel();
        label->autorelease();
        label->initWithString("TTF Label with Stroke and Shade", "Arial-BoldMT", 40,2);
        label->setR_shade(3);//3
        label->setShadeColor(Cv4(0, 0, 0, 1));
        label->setStrokeColor(Cv4(0, 0, 0, 1));
        label->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height*(8.0/9) - label->getContentSize().height));
        addChild(label,1);
    }
    // author info
    {
        CmyTTFLabel* label = new CmyTTFLabel();
        label->autorelease();
        label->initWithString("by yang chao (wantnon) 2013-11-22",  "Arial-BoldMT", 30,1);
        label->setR_shade(2);//2
        label->setShadeColor(Cv4(0, 0, 0, 1));
        label->setStrokeColor(Cv4(0, 0, 0, 1));
        label->setPosition(ccp(origin.x + visibleSize.width/2,
                               origin.y + visibleSize.height*(8.0/9) - label->getContentSize().height-60));
        addChild(label,1);
    }
    
    //----myTTFLabel
    myTTFLabel= new CmyTTFLabel();
    myTTFLabel->autorelease();
    myTTFLabel->initWithString("Hellow World !", "Arial-BoldMT", 70,3);
    myTTFLabel->setR_shade(5);
    myTTFLabel->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(myTTFLabel, 1);
    //----ui
    //slider
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(360); // Sets the max value of range
		slider->setValue(calAngleFromCosAndSin(myTTFLabel->getShadeDir().x,myTTFLabel->getShadeDir().y));
		slider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 4.0f));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction), CCControlEventValueChanged);
		m_pSliderCtl=slider;
		addChild(m_pSliderCtl,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("shade angle ", "Arial", 30);
        pLabel->setColor(ccc3(0, 0, 0));
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        addChild(pLabel, 1);
	}
    
    //slider2
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
        slider->setAnchorPoint(ccp(0.5f, 0.5f));
        slider->setMinimumValue(0.0f); // Sets the min value of range
        slider->setMaximumValue(myTTFLabel->getR_shade()*2); // Sets the max value of range
        slider->setValue(myTTFLabel->getR_shade());
        slider->setPosition(m_pSliderCtl->getPosition()+ccp(0,-m_pSliderCtl->getContentSize().height));
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction2), CCControlEventValueChanged);
        m_pSliderCtl2=slider;
        addChild(m_pSliderCtl2,100);
        //title
        CCLabelTTF* pLabel = CCLabelTTF::create("shade width ", "Arial", 30);
        pLabel->setColor(ccc3(0, 0, 0));
        pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        addChild(pLabel, 1);
    }
    
    //slider3
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
        slider->setAnchorPoint(ccp(0.5f, 0.5f));
        slider->setMinimumValue(0.0f); // Sets the min value of range
        slider->setMaximumValue(myTTFLabel->getR_stroke()*2); // Sets the max value of range
        slider->setValue(myTTFLabel->getR_stroke());
        slider->setPosition(m_pSliderCtl2->getPosition()+ccp(0,-m_pSliderCtl->getContentSize().height));
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction3), CCControlEventValueChanged);
        m_pSliderCtl3=slider;
        addChild(m_pSliderCtl3,100);
        //title
        CCLabelTTF* pLabel = CCLabelTTF::create("stroke width ", "Arial", 30);
        pLabel->setColor(ccc3(0, 0, 0));
        pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        addChild(pLabel, 1);
    }
    //slider4
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
        slider->setAnchorPoint(ccp(0.5f, 0.5f));
        slider->setMinimumValue(0); // Sets the min value of range
        slider->setMaximumValue(myTTFLabel->getFontSize()*2); // Sets the max value of range
        slider->setValue(myTTFLabel->getFontSize());
        slider->setPosition(m_pSliderCtl3->getPosition()+ccp(0,-m_pSliderCtl->getContentSize().height));
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction4), CCControlEventValueChanged);
        m_pSliderCtl4=slider;
        addChild(m_pSliderCtl4,100);
        //title
        CCLabelTTF* pLabel = CCLabelTTF::create("font size ", "Arial", 30);
        pLabel->setColor(ccc3(0, 0, 0));
        pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        addChild(pLabel, 1);
    }


    

    return true;
}
void HelloWorld::sliderAction(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    myTTFLabel->setShadeDir(CCPoint(cosf(value*M_PI/180),sinf(value*M_PI/180)));
    
    
}
void HelloWorld::sliderAction2(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    myTTFLabel->setR_shade(value);
    
}

void HelloWorld::sliderAction3(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    myTTFLabel->setR_stroke(value);
    
}

void HelloWorld::sliderAction4(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    myTTFLabel->setFontSize((int)value);
    
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        
    }
}
void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        
		
    }
    
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        //CCLOG("loc_GLSpace:%f,%f",loc_GLSpace.x,loc_GLSpace.y);

        
    }
}

