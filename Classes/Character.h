#pragma once
#include "cocos2d.h"

enum EKeys
{
	None = 0,
	Left = 1,
	Right = 2,
	Space = 4,
};

USING_NS_CC;
class Character
{



public:
	//Variables
	Sprite* draw_Sprite;
	Node* followNode;
	std::vector<Rect*>* grounds;
	//Methods
	Character(void);
	~Character(void);
	void update(float, EKeys);
	void init(Layer*, std::vector<Rect*>*);

	
private:
	//Variables
	//Sprites
	Sprite* Sp_running;
	Sprite* Sp_jump;
	Sprite* Sp_hit;
	Sprite* Sp_shoot;
	Sprite* Sp_idle;
	//Player Colliders
	Rect lCollider;
	Rect rCollider;
	Rect gCollider;
	Rect tCollider;
	//
	float speed;
	float gravitationForce;
	float jumpImpulse;
	float stepUp;
	float lerpMulti;
	Point nodeOffset;
	bool isGrounded;

	Layer* parent_Scene;
	Point direction;
	
	
	

	
	Rect* collidingWith;
	//Methods
	void move(float, EKeys);
	void calcColliders();
	void checkCollision();
	void checkGround(Rect* g);
	void checkTop(Rect* g);
	bool checkSide(bool side, Rect* g);
	Point lerp(Point, Point, float);
};

