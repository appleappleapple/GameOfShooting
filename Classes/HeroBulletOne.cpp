/**
*功能 创建子弹并初始化子弹的运动
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.3.14
*/

#include "HeroBulletOne.h"

void HeroBulletOne::shootBullet(float dt) {
		Size winSize = Director::getInstance()->getWinSize();
		auto PlanePos = plane->getPosition();
		//从缓存中创建子弹
		auto spritebullet = Sprite::createWithTexture(bulletBatchNode->getTexture());
		//将创建好的子弹添加到BatchNode中进行批次渲染
		bulletBatchNode->addChild(spritebullet);
		//将创建好的子弹添加到容器
		vecBullet.pushBack(spritebullet);

		Point bulletPos = (Point(PlanePos.x,
			PlanePos.y + plane->getContentSize().height / 2 + 20));
		spritebullet->setPosition(bulletPos);
		spritebullet->setScale(0.8f);

	    float flyVelocity = 500;//运行速度，可以自己控制，每秒所走的像素
		float flyLen = winSize.height - PlanePos.y;
		float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间

		//子弹运行的距离和时间，从飞机处开始运行到屏幕顶端
		auto actionMove = MoveTo::create(realFlyDuration,
			Point(bulletPos.x, winSize.height));

		//子弹执行完动作后进行函数回调，调用移除子弹函数
		auto actionDone = CallFuncN::create(
			CC_CALLBACK_1(HeroBulletOne::removeBullet, this));

		//子弹开始跑动
		Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
		spritebullet->runAction(sequence);


	}

//void HeroBulletOne::createBullet(Node* plane) {
//	    this->plane = plane;
//	  	//创建BatchNode节点
//		bulletBatchNode = SpriteBatchNode::create("bullet1.png");
//		this->addChild(bulletBatchNode);
//		//每隔0.2S调用一次发射子弹函数
//		schedule(schedule_selector(HeroBulletOne::shootBullet), 0.2f);
//	}



