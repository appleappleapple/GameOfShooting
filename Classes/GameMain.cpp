#include "GameMain.h"
#include"HeroPlane.h"
USING_NS_CC;
Scene* GameMain::createScene()
{
    auto scene = Scene::create();
    auto layer = GameMain::create();
    scene->addChild(layer);
    return scene;
}

bool GameMain::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//这是地面图层
	this->addChild(BackLayerUp::create());
	//这是白云图层
	this->addChild(BackLayerDown::create());

	
	HeroPlane *heroPlane = HeroPlane::getInstance();
	this->addChild(heroPlane);



	//加子弹
	mHeroBulletLayer = HeroBulletLayer::create(heroPlane->getPlane());
	this->addChild(mHeroBulletLayer,1);
	//每隔5S改變一次子子彈類型
	number = 1;
	schedule(schedule_selector(GameMain::changeBullet),5.0f);

	scheduleUpdate();
	//每隔0.5S调用一次
	//schedule(schedule_selector(GameMain::enemyBuild1), 0.5f);
	//每隔3S调用一次
//	schedule(schedule_selector(GameMain::enemyBuild2), 3.0f);
	//每隔0.5S调用一次
	schedule(schedule_selector(GameMain::enemyBuild3), 0.5f);

	//每隔0.5调用一次
	schedule(schedule_selector(GameMain::enemyBuild4), 0.5f);
    return true;
}



void GameMain::update(float dt){
	//auto *mEnemyPlane = getChildByTag(200);
	//Vector <Sprite *> mVecHeroBullet = mHeroBulletLayer->GetBullet();
	//for (int i = 0; i<mVecHeroBullet.size();i++){
	//	if (mEnemyPlane->boundingBox().intersectsRect(mVecHeroBullet.at(i)->boundingBox())){
	//		mHeroBulletLayer->removeBullet(mVecHeroBullet.at(i));
	//	}

	//}

}
void GameMain::changeBullet(float dt){
	if (number == 1){
		mHeroBulletLayer->changeBullet(2);
		number = 2;
	}
	else if (number == 2){
		mHeroBulletLayer->changeBullet(3);
		number = 3;
	}
	else if (number == 3)
	{
		mHeroBulletLayer->changeBullet(1);
		number = 1;
	}

}

void GameMain::enemyBuild1(float dt){
	Size winSize = Director::getInstance()->getWinSize();
	auto spritePlane = Sprite::create("air3.png");
	spritePlane->setRotation(90);
	spritePlane->setPosition(Vec2(0,400));
	spritePlane->setScale(0.25);
	this->addChild(spritePlane);
	
	//设置贝塞尔曲线参数
	ccBezierConfig tr0;
	tr0.endPosition = Vec2(0, 10);//终点
	tr0.controlPoint_1 = Vec2(250, 300);//控制点1
	tr0.controlPoint_2 = Vec2(180, 150);//控制点2


	ActionInterval* bezierForward = BezierTo::create(3.f, tr0);//创建运行的贝塞尔曲线
	ActionInterval *forwardBy = RotateBy::create(3.f,180);     // 第二个参数：如果是正数则是顺时针，否则逆时针 
	Spawn* spawn = Spawn::create(bezierForward, forwardBy,NULL);//创建合成动作

	//子弹执行完动作后进行函数回调，调用移除子弹函数
	auto actionDone = CallFuncN::create(
		CC_CALLBACK_1(GameMain::enemyRemove, this));

	//连续动作
	Sequence* sequence = Sequence::create(spawn,actionDone, NULL);
	spritePlane->runAction(sequence);

}
void GameMain::enemyBuild2(float dt){
	Size winSize = Director::getInstance()->getWinSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//生成精灵
	auto spritePlane1 = Sprite::create("air4.png");
	auto spritePlane2 = Sprite::create("air4.png");
	auto spritePlane3 = Sprite::create("air4.png");
	//得到精灵宽和高
	float height = spritePlane1->getContentSize().height;
	float width = spritePlane1->getContentSize().width;

	//旋转的角度
	spritePlane1->setRotation(180);
	spritePlane2->setRotation(180);
	spritePlane3->setRotation(180);

	//设置缩放
	//spritePlane1->setScale(0.3);
	//spritePlane2->setScale(0.3);
	//spritePlane3->setScale(0.3);

	//设置位置
	spritePlane1->setPosition(Vec2(width, winSize.height + height));
	spritePlane2->setPosition(Vec2(winSize.width / 2, winSize.height - height));
	spritePlane3->setPosition(Vec2(winSize.width - width, winSize.height + height));


	//层中加入精灵
	this->addChild(spritePlane1);
	this->addChild(spritePlane2);
	this->addChild(spritePlane3);

	//计算飞行时间
	float flyVelocity =200;//运行速度，可以自己控制，每秒所走的像素
	float flyLen = winSize.height;
	float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间

	//子弹运行的距离和时间，从飞机处开始运行到屏幕底部
	auto actionMove1 = MoveBy::create(realFlyDuration, Point(0, -winSize.height - height));
	auto actionMove2 = MoveBy::create(realFlyDuration, Point(0, -winSize.height -height));
	auto actionMove3 = MoveBy::create(realFlyDuration, Point(0, -winSize.height - height));

	//子弹执行完动作后进行函数回调，调用移除子弹函数
	auto actionDone = CallFuncN::create(
		CC_CALLBACK_1(GameMain::enemyRemove, this));

	//连续动作
	Sequence* sequence1 = Sequence::create(actionMove1, actionDone, NULL);
	Sequence* sequence2 = Sequence::create(actionMove2, actionDone, NULL);
	Sequence* sequence3 = Sequence::create(actionMove3, actionDone, NULL);

	//飞机开始跑动
	spritePlane1->runAction(sequence1);
	spritePlane2->runAction(sequence2);
	spritePlane3->runAction(sequence3);

}
void GameMain::enemyBuild3(float dt){
	Size winSize = Director::getInstance()->getWinSize();	
	auto spritePlane = Sprite::create("air2.png");
	//得到精灵宽和高
	float height = spritePlane->getContentSize().height;
	float width = spritePlane->getContentSize().width;
	//设置敌机位于右上角
	
	spritePlane->setPosition(Vec2(winSize.width + width / 2, winSize.height + height/2));
	spritePlane->setScale(0.25);
	this->addChild(spritePlane);
	//计算英雄飞机和对角点连起的线与边界的角度
	float x = HeroPlane::getInstance()->getPlane()->getPosition().x;
	float y = HeroPlane::getInstance()->getPlane()->getPosition().y;
	float a = winSize.width - x;
	float b = winSize.height - y;
	// 弧度转角度
	float radians = atanf(a / b);
	float mDegree = CC_RADIANS_TO_DEGREES(radians);
	spritePlane->setRotation(180+mDegree);
	//计算敌机的最终位置
	float endX = winSize.width-(a / b)*winSize.height;
	float endY = 0;
	//计算飞行时间
	float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素
	float flyLen = sqrt((winSize.width - endX)*(winSize.width - endX)+(winSize.height - endY)*(winSize.height - endY));
	float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间
	//子弹运行的距离和时间，从飞机处开始运行到屏幕底部
	auto actionMove = MoveTo::create(realFlyDuration, Point(endX, endY));
	//子弹执行完动作后进行函数回调，调用移除子弹函数
	auto actionDone = CallFuncN::create(
		CC_CALLBACK_1(GameMain::enemyRemove, this));
	//连续动作
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	//飞机开始跑动
	spritePlane->runAction(sequence);
		
}
void GameMain::enemyBuild4(float dt){
	Size winSize = Director::getInstance()->getWinSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//生成左边敌机
	auto spritePlane1 = Sprite::create("air5.png");
	auto spritePlane2 = Sprite::create("air5.png");
	auto spritePlane3 = Sprite::create("air5.png");
	//生成边敌机
	auto spritePlane4 = Sprite::create("air5.png");
	auto spritePlane5 = Sprite::create("air5.png");
	auto spritePlane6 = Sprite::create("air5.png");

	//旋转的角度
	spritePlane1->setRotation(90);
	spritePlane2->setRotation(90);
	spritePlane3->setRotation(90);

	spritePlane4->setRotation(-90);
	spritePlane5->setRotation(-90);
	spritePlane6->setRotation(-90);

	//设置缩放
	//spritePlane1->setScale(0.3);
	//spritePlane2->setScale(0.3);
 //   spritePlane3->setScale(0.3);


	//得到精灵宽和高
	float height = spritePlane1->getContentSize().height;
	float width = spritePlane1->getContentSize().width;
   
	//放置敌机位置
	spritePlane1->setPosition(Vec2(-width / 2, winSize.height - height / 2-10));
	spritePlane2->setPosition(Vec2(-width / 2, spritePlane1->getPosition().y - 2 * height - 10));
	spritePlane3->setPosition(Vec2(-width / 2, spritePlane2->getPosition().y - 2 * height - 10));

	spritePlane4->setPosition(Vec2(winSize.width + width / 2, spritePlane1->getPosition().y - height - 10));
	spritePlane5->setPosition(Vec2(winSize.width + width / 2, spritePlane4->getPosition().y - 2 * height - 10));
	spritePlane6->setPosition(Vec2(winSize.width + width / 2, spritePlane5->getPosition().y - 2 * height - 10));


	//层中加入精灵
	this->addChild(spritePlane1);
	this->addChild(spritePlane2);
	this->addChild(spritePlane3);
	this->addChild(spritePlane4);
	this->addChild(spritePlane5);


	//计算飞行时间
	float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素
	float flyLen = winSize.width+width;
	float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间


	//子弹运行的距离和时间，从飞机处开始运行到屏幕底部
	auto actionMove1 = MoveBy::create(realFlyDuration, Point(flyLen,0));
	auto actionMove2 = MoveBy::create(realFlyDuration, Point(-flyLen, 0));

	//子弹执行完动作后进行函数回调，调用移除子弹函数
	auto actionDone = CallFuncN::create(
		CC_CALLBACK_1(GameMain::enemyRemove, this));
	//连续动作
	Sequence* sequence1 = Sequence::create(actionMove1, actionDone, NULL);
	Sequence* sequence2 = Sequence::create(actionMove1->clone(), actionDone, NULL);
	Sequence* sequence3 = Sequence::create(actionMove1->clone(), actionDone, NULL);
	Sequence* sequence4 = Sequence::create(actionMove2, actionDone, NULL);
	Sequence* sequence5 = Sequence::create(actionMove2->clone(), actionDone, NULL);
	//飞机开始跑动
	spritePlane1->runAction(sequence1);
	spritePlane2->runAction(sequence2);
	spritePlane3->runAction(sequence3);
	spritePlane4->runAction(sequence4);
	spritePlane5->runAction(sequence5);


}

void GameMain::enemyRemove(Node* pNode){
	if (NULL == pNode) {
		return;
	}
	Sprite* plane = (Sprite*)pNode;
	this->removeChild(plane,true);
}



