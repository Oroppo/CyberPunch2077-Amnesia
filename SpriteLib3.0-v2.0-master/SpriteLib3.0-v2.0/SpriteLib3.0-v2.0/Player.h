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
private:
	float jumpGrav = 10;
	float AtkDistance;
	int HP = 5, attackPower =1; 
	COORD PlayerPosition; 
	void SetActiveAnimation(int anim);
	float AttackTimer=1.f;

	//Basically, any animation OTHER than moving will not have a cancel, and we'll be checking whether or not that animation is done
	bool m_moving = false;
	//Are you currently attacking?????
	bool m_attacking = false;
	//Have we locked the player from moving during this animation?
	bool m_locked = false;

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
	AnimDir m_facing = LEFT;
};

#endif // !__PLAYER_H__