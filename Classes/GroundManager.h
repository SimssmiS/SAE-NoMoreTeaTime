#pragma once
#include "cocos2d.h";

USING_NS_CC;

class GroundManager
{
public:
	GroundManager(Layer*);
	~GroundManager(void);
	std::vector<Rect*> grounds;
	void addTile(Sprite*, float, float);


private:
	Layer* pLayer;
};

