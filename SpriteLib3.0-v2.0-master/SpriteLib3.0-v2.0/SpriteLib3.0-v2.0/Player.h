#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BackEnd.h"
#include"Combat.h"
#define TOPDOWN
class jump {


};
enum AnimEnums
{
	IDLELEFT,
	IDLERIGHT,

	//Create an Enumerator of the animations in the JSON to be used in player.cpp
	SLICERIGHT,
	KICKRIGHT,
	JUMPRIGHT,
	LANDRIGHT,
	RUNRIGHT,
	TURNRIGHT,
	FALLRIGHT,

	//Only in Top down
#ifdef TOPDOWN
	IDLEUP,
	IDLEDOWN,
#endif

	WALKLEFT,
	WALKRIGHT,

	//Only in Top down
#ifdef TOPDOWN
	WALKUP,
	WALKDOWN,
#endif
	
	ATTACKLEFT,
	ATTACKRIGHT,

	//Only in Top down
#ifdef TOPDOWN
	ATTACKUP,
	ATTACKDOWN
#endif
};

enum AnimTypes
{
#ifdef TOPDOWN
	IDLE = 0,
	WALK = 4,
	ATTACK = 8
#endif
#ifndef TOPDOWN
	IDLE = 0,
	WALK = 2,
	ATTACK = 4
#endif
};

enum AnimDir
{
	LEFT,
	RIGHT,
	//Only in Top Down
#ifdef TOPDOWN
	UP,
	DOWN
#endif
};

class Player : public Shared
{
public:
	Player();
	Player(std::string& fileName, std::string& animationJSON, int width, int height, 
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = false, PhysicsBody* body = nullptr);

	void InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height, 
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = false, PhysicsBody* body = nullptr);

	void Update();
	void MovementUpdate();
	void AnimationUpdate();
	void AttachBody(PhysicsBody* body);
	float PlayerAttack(COORD);
	float AttackTimer = 1.f;
	static float Phealth;

	float initialPhealth;

private:
	int m_jumpTimer = 0;
	bool dash = false;
	bool dashCorrection = false;
	bool m_facingRight = true;
	bool m_attacking = false;
	bool m_locked = false;
	bool m_isJumping = false;
	float jumpGrav = 10;
	float xdiff = 0;
	float AtkDistance;
	//impactx and y and impact are variables that are used to fix the jump mechanic
	float impactX=0.0, impactY=0.0,spotJumped=0;
	bool impactAvailable = true,walljumpCorrection=false;
	int HP = 5, attackPower = 1, dashCooldown = 0,XvelDash=0,XvelDir=0;
	COORD PlayerPosition; 
	void SetActiveAnimation(int anim);

	//Basically, any animation OTHER than moving will not have a cancel, and we'll be checking whether or not that animation is done
	bool m_moving = false;
	//Are you currently attacking?????
	
	//Have we locked the player from moving during this animation?
	

	//A reference to our sprite
	Sprite* m_sprite = nullptr;
	//A reference to our animation controller
	AnimationController* m_animController = nullptr;
	//A reference to our player transform
	Transform* m_transform = nullptr;

	//Physics importance
	//A reference to our physics body
	PhysicsBody* m_physBody = nullptr;
	//Does this player have physics?
	bool m_hasPhysics = false;

	//Default animation direction (feel free to change this to suit your game. If you're making a side-scroller, left or right would be better
	AnimDir m_facing = RIGHT;
};

#endif // !__PLAYER_H__