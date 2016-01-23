/**
*功能 单例英雄飞机类
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.4.6
*/
#include"HeroPlane.h"
USING_NS_CC;
HeroPlane* HeroPlane::sharePlane = NULL;//注意，静态变量的写法！
HeroPlane::HeroPlane(){
	plane = NULL;
	planeHp=10000;//英雄飞机生命值
	planeScore=0;//英雄飞机分数值
	planeBulletNum=1;//英雄飞机子弹类型,默认初始化为第一种
	isHeroPlaneControl = false;
    planeAttack=100;//英雄飞机攻击值
    planeDefend=100;//英雄飞机保护值

}
//取得英雄飞机的方法，只能通过这个方法
HeroPlane* HeroPlane::getInstance()
{
	if (NULL == sharePlane){
		sharePlane = new HeroPlane();
		sharePlane->init();
		sharePlane->autorelease();
	}
	return sharePlane;
}
bool HeroPlane::init(){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("heroplane.plist", "heroplane.png");//加载全局资源

	plane = Sprite::createWithSpriteFrameName("plane1.png");//生成飞机
	
	plane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5));
	this->addChild(plane, 0, 1);

	Blink *blink = Blink::create(3,8);//闪烁动画
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(frameCache->getSpriteFrameByName("plane1.png"));
	animation->addSpriteFrame(frameCache->getSpriteFrameByName("plane2.png"));
	Animate* animate = Animate::create(animation);//帧动画

	plane->runAction(blink);//执行闪烁动画
	plane->runAction(RepeatForever::create(animate));// 执行帧动画

	//开启触摸事件，让飞机跟随手指移动
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(HeroPlane::onTouchBegan, this);
	listen->onTouchMoved = CC_CALLBACK_2(HeroPlane::onTouchMoved, this);
	listen->onTouchEnded = CC_CALLBACK_2(HeroPlane::onTouchEened, this);
	listen->onTouchCancelled = CC_CALLBACK_2(HeroPlane::onTouchCancelled, this);
	listen->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);

	return true;
}
Sprite* HeroPlane::getPlane(){
	if (NULL == plane)
		return NULL;
	return plane;
}
bool  HeroPlane::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){

	Point mHeroPos = plane->getPosition();
	Point mBeganPos = touch->getLocationInView();
	mBeganPos = Director::getInstance()->convertToGL(mBeganPos);

	//判断当前手指按下区域是否是英雄飞机的区域,并且计算飞机要移动时的偏移量
	if (mBeganPos.x > mHeroPos.x - plane->getContentSize().width / 2 && mBeganPos.x<mHeroPos.x + plane->getContentSize().width / 2 &&
		mBeganPos.y>mHeroPos.y - plane->getContentSize().height / 2 && mBeganPos.y < mHeroPos.y + plane->getContentSize().height / 2){
		isHeroPlaneControl = true;
		//計算偏移量
		mDeltaX = mBeganPos.x - mHeroPos.x;
		mDeltaY = mBeganPos.y - mHeroPos.y;

	}

	return true;
}
void HeroPlane::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event){
	if (isHeroPlaneControl){
		Point mMovedPos = touch->getLocationInView();
		mMovedPos = Director::getInstance()->convertToGL(mMovedPos);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();
		float x = mMovedPos.x - mDeltaX;//記得減去偏移量
		float y = mMovedPos.y - mDeltaY;

		if (x <= plane->getContentSize().width / 2 + origin.x)//x到达屏幕左边界
			x = plane->getContentSize().width / 2 + origin.x;
		else if (x >= visibleSize.width - plane->getContentSize().width / 2)//x到达屏幕右边界
			x = visibleSize.width - plane->getContentSize().width / 2;

		if (y <= plane->getContentSize().height / 2 + origin.y)//y到达屏幕下边界
			y = plane->getContentSize().height / 2 + origin.y;
		else if (y >= visibleSize.height - plane->getContentSize().height / 2)//x到达屏幕上边界
			y = visibleSize.height - plane->getContentSize().height / 2;

		//飞机跟随手指移动
		plane->setPosition(Vec2(x, y));
	}
}
void HeroPlane::onTouchEened(cocos2d::Touch *touch, cocos2d::Event *unused_event){
	isHeroPlaneControl = false;
}
void  HeroPlane::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_even){
	isHeroPlaneControl = false;
}