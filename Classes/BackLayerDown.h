#ifndef __BackLayerDown_H__
#define __BackLayerDown_H__
/**
*功能 實現無限地圖向下滾動
*作者 林炳文（ling20081005@126.com 博客：http://blog.csdn.net/evankaka）
*時間 2015.2.27
*/
#include "cocos2d.h"
#define MAP_1_Tag   1       // 宏定义两个Map的Tag  
#define MAP_2_Tag   2 
class BackLayerDown : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(BackLayerDown);
private:
	void update(float time);
	virtual void onExit();
};

#endif // __BackLayerDown_H__
