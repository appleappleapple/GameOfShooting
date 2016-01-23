/**
*功能 英雄
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*时间 2015.3.14
*/
#pragma once
#ifndef __HeroBulletTwo_H__
#define __HeroBulletTwo_H__
#include "cocos2d.h"
#include "BulletStyle.h"
USING_NS_CC;
class HeroBulletTwo : public BulletStyle {
public:
	virtual  void shootBullet(float dt);
};
#endif 