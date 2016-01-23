/**
*功能 创建子弹并初始化子弹的运动
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.3.14
*/

#include "HeroBulletTwo.h"

void HeroBulletTwo::shootBullet(float dt) {
		Size winSize = Director::getInstance()->getWinSize();
		auto PlanePos = plane->getPosition();
		//从缓存中创建子弹
		auto spritebullet1 = Sprite::createWithTexture(bulletBatchNode->getTexture());
		auto spritebullet2 = Sprite::createWithTexture(bulletBatchNode->getTexture());


		//将创建好的子弹添加到BatchNode中进行批次渲染
		bulletBatchNode->addChild(spritebullet1);
		bulletBatchNode->addChild(spritebullet2);
		//将创建好的子弹添加到容器
		vecBullet.pushBack(spritebullet1);
		vecBullet.pushBack(spritebullet2);

		Point bulletPos1 = (Point(PlanePos.x - plane->getContentSize().width / 4,
			PlanePos.y + plane->getContentSize().height / 2+10 ));

		Point bulletPos2 = (Point(PlanePos.x + plane->getContentSize().width / 4,
			PlanePos.y + plane->getContentSize().height / 2+10));

		spritebullet1->setPosition(bulletPos1);
		spritebullet1->setScale(0.8f);

		spritebullet2->setPosition(bulletPos2);
		spritebullet2->setScale(0.8f);

	    float flyVelocity = 500;//运行速度，可以自己控制，每秒所走的像素
		float flyLen = winSize.height - PlanePos.y;
		float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间


		//子弹运行的距离和时间，从飞机处开始运行到屏幕顶端
		auto actionMove1 = MoveTo::create(realFlyDuration,
			Point(bulletPos1.x, winSize.height));

		auto actionMove2 = MoveTo::create(realFlyDuration,
			Point(bulletPos2.x, winSize.height));

		//子弹执行完动作后进行函数回调，调用移除子弹函数
		auto actionDone = CallFuncN::create(
			CC_CALLBACK_1(HeroBulletTwo::removeBullet, this));

		//子弹开始跑动
		Sequence* sequence1 = Sequence::create(actionMove1, actionDone, NULL);
		spritebullet1->runAction(sequence1);

		Sequence* sequence2 = Sequence::create(actionMove2, actionDone, NULL);
		spritebullet2->runAction(sequence2);


	}





