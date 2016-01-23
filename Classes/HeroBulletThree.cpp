/**
*功能 创建子弹并初始化子弹的运动
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.3.14
*/

#include "HeroBulletThree.h"

void HeroBulletThree::shootBullet(float dt) {
		Size winSize = Director::getInstance()->getWinSize();
		auto PlanePos = plane->getPosition();
		double angle = M_PI * 80 / 180;//旋轉的角度
		//从缓存中创建子弹
		auto spritebullet = Sprite::createWithTexture(bulletBatchNode->getTexture());
		auto spritebullet1 = Sprite::createWithTexture(bulletBatchNode->getTexture());
		spritebullet1->setRotation(-angle);
		auto spritebullet2 = Sprite::createWithTexture(bulletBatchNode->getTexture());
		spritebullet2->setRotation(angle);
		//将创建好的子弹添加到BatchNode中进行批次渲染
		bulletBatchNode->addChild(spritebullet);
		bulletBatchNode->addChild(spritebullet1);
		bulletBatchNode->addChild(spritebullet2);
		//将创建好的子弹添加到容器
		vecBullet.pushBack(spritebullet);
		vecBullet.pushBack(spritebullet1);
		vecBullet.pushBack(spritebullet2);

		Point bulletPos = (Point(PlanePos.x,
			PlanePos.y + plane->getContentSize().height / 2 + 20));


		Point bulletPos1 = (Point(PlanePos.x - plane->getContentSize().width / 4-10,
			PlanePos.y + plane->getContentSize().height / 2+10 ));

		Point bulletPos2 = (Point(PlanePos.x + plane->getContentSize().width / 4+10,
			PlanePos.y + plane->getContentSize().height / 2+10));

		spritebullet->setPosition(bulletPos);
		spritebullet->setScale(0.8f);

		spritebullet1->setPosition(bulletPos1);
		spritebullet1->setScale(0.8f);

		spritebullet2->setPosition(bulletPos2);
		spritebullet2->setScale(0.8f);


	    float flyVelocity = 500;//运行速度，可以自己控制，每秒所走的像素

		float flyLen = winSize.height - PlanePos.y;
		float flyLen1 = PlanePos.x / cos(angle);//按照度來算
		float flyLen2 = (winSize.width - PlanePos.x) / cos(angle);

		float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间
		float realFlyDuration1 = flyLen1 / flyVelocity;//实际飞行的时间
		float realFlyDuration2 = flyLen2 / flyVelocity;//实际飞行的时间

		//子弹运行的距离和时间，从飞机处开始运行到屏幕顶端
		auto actionMove = MoveTo::create(realFlyDuration,
			Point(bulletPos.x, winSize.height));

		auto actionMove1 = MoveTo::create(realFlyDuration1,
			Point(0, PlanePos.x*tan(angle) + PlanePos.y));

		auto actionMove2 = MoveTo::create(realFlyDuration2,
			Point(winSize.width, (winSize.width - PlanePos.x)*tan(angle) + PlanePos.y));

		//子弹执行完动作后进行函数回调，调用移除子弹函数
		auto actionDone = CallFuncN::create(
			CC_CALLBACK_1(HeroBulletThree::removeBullet, this));

		//子弹开始跑动
		Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
		spritebullet->runAction(sequence);

		Sequence* sequence1 = Sequence::create(actionMove1, actionDone, NULL);
		spritebullet1->runAction(sequence1);

		Sequence* sequence2 = Sequence::create(actionMove2, actionDone, NULL);
		spritebullet2->runAction(sequence2);


	}





