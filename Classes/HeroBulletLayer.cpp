/**
*功能 创建子弹并初始化子弹的运动
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.3.14
*/
#include "HeroBulletLayer.h"
HeroBulletLayer::HeroBulletLayer(Node* heroPlane) {
	this->heroPlane = heroPlane;
	mBulletStyle = NULL;
	bulletNumber = 1;
}
/**
*创建子弹的静态方法
*@param heroPlane为英雄飞机
*/
HeroBulletLayer* HeroBulletLayer::create(Node* heroPlane){
	HeroBulletLayer* pRet = new HeroBulletLayer(heroPlane);
	if (pRet&&pRet->init()){
		pRet->autorelease();
		return pRet;
	}
	else{
		delete pRet;
		pRet = NULL;
		return NULL;
	}

}
bool HeroBulletLayer::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!Layer::init());

		
		mBulletStyle = new HeroBulletOne();
		mBulletStyle->autorelease();
		mBulletStyle->createBullet(heroPlane);
		this->addChild(mBulletStyle);
		bRet = true;
	} while (0);
	return bRet;
}
/**
*用缓存的方法创建子弹，并初始化子弹的运动和运动后的事件
*/
//void HeroBulletLayer::shootBullet(float dt) {
	//Size winSize = Director::getInstance()->getWinSize();
	//auto PlanePos = heroPlane->getPosition();
	////从缓存中创建子弹
	//auto spritebullet = Sprite::createWithTexture(bulletBatchNode->getTexture());
	////将创建好的子弹添加到BatchNode中进行批次渲染
	//bulletBatchNode->addChild(spritebullet);
	////将创建好的子弹添加到容器
	//vecBullet.pushBack(spritebullet);

	//Point bulletPos = (Point(PlanePos.x,
	//	PlanePos.y + heroPlane->getContentSize().height / 2 + 20));
	//spritebullet->setPosition(bulletPos);
	//spritebullet->setScale(0.8f);


	//float flyLen = winSize.height - PlanePos.y;
	//float realFlyDuration = flyLen / FlYVElOCITY;//实际飞行的时间

	////子弹运行的距离和时间，从飞机处开始运行到屏幕顶端
	//auto actionMove = MoveTo::create(realFlyDuration,
	//	Point(bulletPos.x, winSize.height));

	////子弹执行完动作后进行函数回调，调用移除子弹函数
	//auto actionDone = CallFuncN::create(
	//	CC_CALLBACK_1(HeroBulletLayer::removeBullet, this));

	////子弹开始跑动
	//Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	//spritebullet->runAction(sequence);

	//两个子弹

	//Size winSize = Director::getInstance()->getWinSize();
	//auto PlanePos = heroPlane->getPosition();


	//从缓存中创建子弹
	//Sprite spritebullet[2];
	//spritebullet[0] = Sprite::createWithTexture(bulletBatchNode->getTexture());
	////将创建好的子弹添加到BatchNode中进行批次渲染
	//bulletBatchNode->addChild(spritebullet);
	////将创建好的子弹添加到容器
	//vecBullet.pushBack(spritebullet);


	//Point bulletPos = (Point(PlanePos.x,
	//	PlanePos.y + heroPlane->getContentSize().height / 2 + 20));
	//spritebullet->setPosition(bulletPos);
	//spritebullet->setScale(0.8f);


	//float flyLen = winSize.height - PlanePos.y;
	//float realFlyDuration = flyLen / FlYVElOCITY;//实际飞行的时间

	////子弹运行的距离和时间，从飞机处开始运行到屏幕顶端
	//auto actionMove = MoveTo::create(realFlyDuration,
	//	Point(bulletPos.x, winSize.height));

	////子弹执行完动作后进行函数回调，调用移除子弹函数
	//auto actionDone = CallFuncN::create(
	//	CC_CALLBACK_1(HeroBulletLayer::removeBullet, this));

	////子弹开始跑动
	//Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	//spritebullet->runAction(sequence);
//}

/**
 * 移除子弹，将子弹从容器中移除，同时也从SpriteBatchNode中移除
 */
//void HeroBulletLayer::removeBullet(Node* pNode) {
//	if (NULL == pNode) {
//		return;
//	}
//	Sprite* bullet = (Sprite*)pNode;
//	this->bulletBatchNode->removeChild(bullet, true);
//	vecBullet.eraseObject(bullet);
//}
/**
*返回子弹列表，用来与敌机做碰撞检测
*/
//Vector <Sprite *>& HeroBulletLayer::GetBullet(){
//	return vecBullet;
//}
bool HeroBulletLayer::changeBullet(int number){


	switch (number)
	{
	case 1:
		if (bulletNumber != 1){
			this->removeChild(mBulletStyle, true);
		mBulletStyle = new HeroBulletOne();
		bulletNumber = 1;
		mBulletStyle->createBullet(heroPlane);
		mBulletStyle->autorelease();
		this->addChild(mBulletStyle);
		}
		break;
	case 2:
		if (bulletNumber != 2){
			this->removeChild(mBulletStyle, true);
			mBulletStyle = new HeroBulletTwo();
			bulletNumber = 2;
			mBulletStyle->createBullet(heroPlane);
			mBulletStyle->autorelease();
			this->addChild(mBulletStyle);
		}
		break;
	case 3:
		if (bulletNumber != 3){
			this->removeChild(mBulletStyle, true);
			mBulletStyle = new HeroBulletThree();
			bulletNumber = 3;
			mBulletStyle->createBullet(heroPlane);
			mBulletStyle->autorelease();
			this->addChild(mBulletStyle);
		}
		break;
	default:
		break;
	}

return false;
}
