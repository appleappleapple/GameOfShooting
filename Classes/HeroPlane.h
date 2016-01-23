/**
*功能 单例英雄飞机类
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.4.6
*/
#pragma once
#ifndef __HeroPlane_H__
#define __HeroPlane_H__
#include "cocos2d.h"
USING_NS_CC;
class HeroPlane :public cocos2d::Layer{
private:
	HeroPlane();
public:
	/**
	*获得单例英雄飞机的方法
	*@return 英雄飞机类
	*/
	static HeroPlane* getInstance();
	virtual bool init();
	/**
	*取得当前英雄飞机中的精灵
	*@return 飞机中精灵，实际的操作对像
	*/
	Sprite* getPlane();
        /**
	*底下四个分别为触摸按下时的事件
	*/
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEened(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_even);

public:
	unsigned int planeHp;//英雄飞机生命值
	unsigned int planeScore;//英雄飞机分数值
	unsigned int planeBulletNum;//英雄飞机子弹类型
        unsigned int planeAttack;//英雄飞机攻击值
        unsigned int planeDefend;//英雄飞机保护值
private:
	static HeroPlane* sharePlane;//英雄飞机静态变量
	bool isHeroPlaneControl;//飞机是否被控制着
	float mDeltaX;//英雄飞机随手指移动时的X偏移量
	float mDeltaY;//英雄飞机随手指移动时的Y偏移量
	Sprite* plane;//英雄飞机

};
#endif 