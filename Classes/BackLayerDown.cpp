#include "BackLayerDown.h"

USING_NS_CC;


bool BackLayerDown::init()
{
  
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite* map1 = Sprite::create("back3_1.png");
	Sprite* map2 = Sprite::create("back3_2.png");
	map1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	map2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y + map2->getContentSize().height / 2));
	this->addChild(map1, 0, MAP_1_Tag);
	this->addChild(map2, 0, MAP_2_Tag);
	this->scheduleUpdate();

    
    return true;
}

//ÒÆ„Ó²¢ÅÐ”à±³¾°
void BackLayerDown::update(float time)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite* temMap1 = (Sprite*)this->getChildByTag(MAP_1_Tag);
	Sprite* temMap2 = (Sprite*)this->getChildByTag(MAP_2_Tag);

	temMap1->setPositionY(temMap1->getPositionY() - 1);
	temMap2->setPositionY(temMap2->getPositionY() - 1);

	if (temMap1->getPositionY() + temMap1->getContentSize().height / 2 <= origin.y)
	{
		float offset = temMap1->getPositionY() + temMap1->getContentSize().height / 2 - origin.y;
		temMap1->setPosition(Vec2(visibleSize.width / 2 + origin.x, temMap1->getContentSize().height / 2 + origin.y + visibleSize.height + offset));
	}

	if (temMap2->getPositionY() + temMap2->getContentSize().height / 2 <= origin.x)
	{
		float offset = temMap2->getPositionY() + temMap2->getContentSize().height / 2 - origin.y;
		temMap2->setPosition(Vec2(visibleSize.width / 2 + origin.x, temMap2->getContentSize().height / 2 + origin.y + visibleSize.height + offset));
	}
}

void BackLayerDown::onExit()
{
	this->unscheduleUpdate();
	Layer::onExit();
}
