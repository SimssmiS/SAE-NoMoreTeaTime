#include "HelloWorldScene.h"
#include "CCAction.h";

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	EGLView::getInstance()->setDesignResolutionSize(1600,900,ResolutionPolicy::SHOW_ALL);

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	screenCenter=Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

	//creating GroundManager to keep track of all colliding objects
	GM=new GroundManager(this);

	//creating main character, adding it to layer and set cam focus on player
	steve = new Character();
	steve->init(this, &(GM->grounds)); 
	this->addChild(steve->draw_Sprite);
	this->runAction(Follow::create(steve->followNode));

	//adding static colliding objects to GroundManager and layer
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x, screenCenter.y-400);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x-400, screenCenter.y-400);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+400, screenCenter.y-400);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x-700, screenCenter.y-350);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x-800, screenCenter.y-300);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x-900, screenCenter.y-250);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x-1000, screenCenter.y-200);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x-1100, screenCenter.y-150);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x-1200, screenCenter.y-100);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+700, screenCenter.y-350);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+800, screenCenter.y-300);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+900, screenCenter.y-250);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+1000, screenCenter.y-200);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+1100, screenCenter.y-150);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+1200, screenCenter.y-100);

	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+1200, screenCenter.y-100);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+1600, screenCenter.y-100);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+2000, screenCenter.y-100);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+2400, screenCenter.y-100);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+2800, screenCenter.y-100);
	GM->addTile(Sprite::create("GROUND.png"), screenCenter.x+2800, screenCenter.y+183);
								
	//GM->addTile(Sprite::create("GROUND.png"), screenCenter.x,screenCenter.y);

	//Adding Keyboard input
    auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	m_movement = EKeys::None;

	//creating schedule for update methode
	this->schedule(schedule_selector(HelloWorld::update));

	//init completed
    return true;
	
}
void HelloWorld::update(float dt)
{
//	Sp_idle->setPositionX(Sp_idle->getPositionX() + 1);
	steve->update(dt,m_movement);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event* e)
{
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			m_movement = (EKeys)(m_movement | EKeys::Left);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			m_movement = (EKeys)(m_movement | EKeys::Right);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			m_movement = (EKeys)(m_movement | EKeys::Space);
			break;
		}
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event* e)
{
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			m_movement = (EKeys)(m_movement ^ EKeys::Left);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			m_movement = (EKeys)(m_movement ^ EKeys::Right);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			m_movement = (EKeys)(m_movement ^ EKeys::Space);
			break;
		}
	}
}

//void HelloWorld::draw()
//{
//	//ccDrawRect(screenCenter,screenCenter+Point(500,300));
//	for (Rect* g: GM->grounds)
//	{
//		ccDrawRect(Point(g->getMinX(),
//				         g->getMinY()),
//				   Point(g->getMaxX(),
//				         g->getMaxY()));
//	}
//	log("posx %f  |  posy %f    -     sizeX %f  |  sizeY %f",GM->grounds[2]->getMidX(),
//															 GM->grounds[2]->getMidY(),
//															 GM->grounds[2]->getMaxX()-GM->grounds[2]->getMinX(),
//															 GM->grounds[2]->getMaxY()-GM->grounds[2]->getMinY());
//	//log("vector length %i", GM->grounds.size());
//}