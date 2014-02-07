#include "GroundManager.h"

USING_NS_CC;

GroundManager::GroundManager(Layer* ParentLayer)
{
	grounds = std::vector<Rect*>();
	pLayer=ParentLayer;
}
GroundManager::~GroundManager(void)
{

}

void GroundManager::addTile(Sprite* s,float pX, float pY)
{
	Rect* g = new Rect(pX - s->getContentSize().width*0.5f,
						  pY-s->getContentSize().height*0.5f,
						  s->getContentSize().width,
						  s->getContentSize().height);
	
	//log ("getX: %f,  getY %f",pX,pY);
	//log ("x: %f  |  y: %f  |  xsize: %f  |  ysize: %f", g->getMinX(), g->getMinY(), g->getMidX()-g->getMinX(), g->getMidY()-g->getMinY()); 
	s->setPosition(pX, pY);
	pLayer->addChild(s,1);
	grounds.push_back(g);
}
