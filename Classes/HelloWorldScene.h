#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "GroundManager.h"

USING_NS_CC;

//enum EKeys
//{
//	None = 0,
//	Left = 1,
//	Right = 2,
//	Space = 4,
//};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float dt);

	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* e);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* e);

private:
	EKeys m_movement;
	Character* steve;
	GroundManager* GM;
	Point screenCenter;
	//Character steve;

	//Sprite* Sp_idle;
	//void draw();
};

#endif // __HELLOWORLD_SCENE_H__
