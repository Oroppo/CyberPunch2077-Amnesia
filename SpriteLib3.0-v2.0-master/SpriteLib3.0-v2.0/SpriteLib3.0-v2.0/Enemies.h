#pragma once
#include "PhysicsBody.h"
#include "Sprite.h"
#include "Timer.h"
#include "Combat.h"

/*enum class ZombAnimEnums
{
	Standing = 0,
	Moving = 1,
};*/
class Enemy : public Shared
{
private:
	//float health = 10.f; // Enemy Health
	float movementSpeed = -20.f; // Enemy movementspeed
	int detection = 150; // Enemy detection legnth
	vec3 move = vec3(0, 0, 0); // Movement vectors
	vec2 movement = vec2(0, 0);
	int LorR = 0; // checks if player is left or right of enemy
	float timer = 3;// used for fight state
	float internalTimer = 0; // used for fight state

	Sprite* m_sprite = nullptr;
	Transform* m_transform = nullptr;
	PhysicsBody* m_physBody = nullptr;

public:

	Enemy();
	void InitEnemy(std::string& fileName, int width, int height, Sprite* sprite, Transform* transform, PhysicsBody* body = nullptr);
	void AttachBody(PhysicsBody* body);

	float getMovementSpeed();
	float getEnemyHealth();

	void setMovementSpeed(float);
	void setEnemyHealth(float);

	//Enemy State Functions
	void idle(float distanceX, float distanceY, PhysicsBody* EnemyPhysicsBody);
	void chase(float distanceX, float distanceY, PhysicsBody* EnemyPhysicsBody);
	void fight(PhysicsBody* EnemyPhysicsBody);
	void resetTimer();
	void internalTime(PhysicsBody* EnemyPhysicsBody);
	void destroyEnemy(std::vector <unsigned int>* eEnts, int Eentity)
	{
		for (int i = 0; i < eEnts->size(); i++) {
			if (eEnts->at(i) == Eentity) {
				eEnts->erase(eEnts->begin() + i);
			}
		}
		PhysicsBody::m_bodiesToDelete.push_back(Eentity);
	}


	void enemyUpdate(PhysicsBody* EnemyPhysicsBody, std::vector <unsigned int>* eEnts, int Eentity);
};
