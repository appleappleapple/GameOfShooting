/**
*功能 创建子弹并初始化子弹的运动
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.3.14
*/
#pragma once
#ifndef __BulletStyle_H__
#define __BulletStyle_H__
#include "cocos2d.h"
USING_NS_CC;

class BulletStyle : public cocos2d::Layer{
public:
	~BulletStyle();
	/**
	* 移除所有的东西
	*/
	void removeAllObject();
	/**
	*移除超出屏幕可视范围的子弹或者碰撞后的子弹清除
	*@param pNode 要删除的子弹
	*/
	void removeBullet(Node* pNode);
	/**
	*根据传入的飞机，子弹跟随发射
	*@param plane为传入飞机，可为英雄飞机或敌机 
	*/
	virtual void createBullet(Node* plane);
	/**
	*发射子弹，在其中进行子弹的渲染和子弹的飞行动作，默认为单子弹 
	*@param dt子弹间隔发时间
	*/
	virtual void shootBullet(float dt){}
	
protected:
	//子弹容器
	  Vector <Sprite *> vecBullet;
	 //批次渲染节点
	  SpriteBatchNode* bulletBatchNode;
	 //传入的飞机
	  Node* plane;
};
#endif 