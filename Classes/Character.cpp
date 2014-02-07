#include "Character.h"
#include "CCAction.h"
USING_NS_CC;

#define getHalfRectHeight g->getMidY() - g->getMinY()

Character::Character()
{
	
}

void Character::init(Layer* parentLayer, std::vector<Rect*>* g)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	
	//Character stats
	speed=500;
	jumpImpulse=20;
	gravitationForce=-50;
	stepUp=50;

	Point pos= Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

	//Character Sprites
	Sp_idle = Sprite::create("Steve_idle2.png");
	Sp_idle->setPosition(pos);
	direction = Point(0,0);
	//Sp_idle->setScale(0.5);
	draw_Sprite=Sp_idle;
	grounds = g;
	//parentLayer->addChild(Sp_idle, 0);
	isGrounded=true;
	collidingWith=nullptr;
	followNode= Node::create();
	nodeOffset=Point(300,20);
	followNode->setPosition(draw_Sprite->getPosition() + nodeOffset);
	parentLayer->addChild(followNode);
	lerpMulti=1.7f;

}

void Character::update(float dt, EKeys keys){
	calcColliders();
	move(dt,keys);
}

void Character::checkCollision()
{
	isGrounded=false;
	for (Rect* g: *grounds)
	{
		if (g->getMidX() - draw_Sprite->getPositionX()<1500 && 
			g->getMidY() - draw_Sprite->getPositionY()<1500 )
		{

			checkGround(g);
			checkTop(g);
			checkSide(true,g);
			checkSide(false,g);
		}
	}

	if (collidingWith==nullptr){
		
	}
	else if (rCollider.intersectsRect(*collidingWith)){

	}
	else if (lCollider.intersectsRect(*collidingWith)){

	}
	else
	{
		collidingWith==nullptr;
	}

}

void Character::checkGround(Rect* g)
{
	if (gCollider.intersectsRect(*g))
			{
				isGrounded=true;
				if (direction.y<0)
				{
					direction.y=0.0f;
					draw_Sprite->setPositionY(g->getMidY()+
										  getHalfRectHeight +
										  draw_Sprite->getContentSize().height/2);
				}
				
			}
}

void Character::checkTop(Rect* g)
{
	if (tCollider.intersectsRect(*g) &&
				direction.y>0.0f)
	{
		direction.y=0.0f;
		draw_Sprite->setPositionY(g->getMidY()-
								  getHalfRectHeight -
								  draw_Sprite->getContentSize().height*0.5f);
	}
}

bool Character::checkSide(bool side, Rect* g) //true=right false=left
{
	bool directionCorrect=false;
	Rect* coll=nullptr;

	if (side == true)
	{
		coll=&rCollider;
		if (direction.x>0)
			directionCorrect=true;
	}
	else
	{
		coll=&lCollider;
		if (direction.x<0)
			directionCorrect=true;
	}

	if (coll->intersectsRect(*g) && directionCorrect)
	{
		if (g->getMidY() + getHalfRectHeight <=
			draw_Sprite->getPositionY()-draw_Sprite->getContentSize().height*0.5f+stepUp &&
			isGrounded)
		{
			Point destination= Point(draw_Sprite->getPositionX(),g->getMidY() + getHalfRectHeight + draw_Sprite->getContentSize().height*0.5f);
			draw_Sprite->setPosition(destination);
		}
		else
		{
			direction.x=0;
		}
		return true;
	}
	return false;
}

void Character::calcColliders(){
	lCollider= Rect(draw_Sprite->getPositionX()+direction.x-(draw_Sprite->getContentSize().width/2),  //left Collider
				   draw_Sprite->getPositionY()+direction.y-(draw_Sprite->getContentSize().height/2-4),
				   draw_Sprite->getContentSize().width/2,
				   draw_Sprite->getContentSize().height-8);
	rCollider= Rect(draw_Sprite->getPositionX()+direction.x,
				   draw_Sprite->getPositionY()+direction.y-(draw_Sprite->getContentSize().height/2-4),  //right Collider
				   draw_Sprite->getContentSize().width/2,
				   draw_Sprite->getContentSize().height-8);
	gCollider= Rect(draw_Sprite->getPositionX()+direction.x-(draw_Sprite->getContentSize().width/2-7),	//Ground Collider
				   draw_Sprite->getPositionY()+direction.y-(draw_Sprite->getContentSize().height/2),
				   draw_Sprite->getContentSize().width-14,
				   20);
	tCollider= Rect(draw_Sprite->getPositionX()+direction.x-(draw_Sprite->getContentSize().width/2-5), //top Collider
				   draw_Sprite->getPositionY()+direction.y+(draw_Sprite->getContentSize().height/2)-20,
				   draw_Sprite->getContentSize().width-10,
				   20);
}

void Character::move(float dt, EKeys keys){
	direction= Point(0,direction.y);
	if ((EKeys::Right & keys) == EKeys::Right){
		direction.x+=1;
	}
	if ((EKeys::Left & keys) == EKeys::Left)
	{
		direction.x-=1;
	}
	
	if (!isGrounded)
	{
		direction.y+=gravitationForce*dt;
		//log("down we go");
	}
	else if((EKeys::Space & keys) == EKeys::Space)
	{
		//log("jmp");
		direction.y=jumpImpulse;
	}

	checkCollision();

	draw_Sprite->setPosition(draw_Sprite->getPosition() + Point(direction.x*speed*dt,direction.y));
	//log("CharPos: x: %f  |  y: %f",draw_Sprite->getPositionX(),draw_Sprite->getPositionY());
	
	if (nodeOffset.x<0 && direction.x>0)
	{
		nodeOffset.x*=-1;
		lerpMulti=3.0f;
	}
	else if (nodeOffset.x>0 && direction.x<0)
	{
		nodeOffset.x*=-1;
		lerpMulti=3.0f;
	}
	lerpMulti-=dt*0.3f;
	if (lerpMulti<2.5f)
		lerpMulti=2.5f;
	followNode->setPosition(lerp(followNode->getPosition(),draw_Sprite->getPosition() + nodeOffset,dt*(lerpMulti)));
}

Point Character::lerp(Point a, Point b, float t)
{
	return a+((b-a)*t);
}

Character::~Character(void)
{

}

//SpriteFrameCache
//AnimationCache