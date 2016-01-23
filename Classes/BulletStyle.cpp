/**
*功能 创建子弹并初始化子弹的运动
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.3.14
*/

#include "BulletStyle.h"
BulletStyle::~BulletStyle(){
	//removeAllObject();
}
/**
* 移除所有的东西
*/
void BulletStyle::removeAllObject(){
	bulletBatchNode->removeAllChildren();
	vecBullet.clear();
	this->removeAllChildren();
	
}
/**
* 移除子弹，将子弹从容器中移除，同时也从SpriteBatchNode中移除
*/
void BulletStyle::removeBullet(Node* pNode) {
	if (NULL == pNode) {
		return;
	}
	Sprite* bullet = (Sprite*)pNode;
	bulletBatchNode->removeChild(bullet, true);
	vecBullet.eraseObject(bullet);
}
/**
*根据传入的飞机，子弹跟随发射
*@param plane为传入飞机，可为英雄飞机或敌机
*/
void BulletStyle::createBullet(Node* plane){
	this->plane = plane;
	//创建BatchNode节点
	bulletBatchNode = SpriteBatchNode::create("bullet1.png");
	this->addChild(bulletBatchNode);
	//每隔0.2S调用一次发射子弹函数
	schedule(schedule_selector(BulletStyle::shootBullet), 0.2f);//注意，這里調用派生類的！！

}