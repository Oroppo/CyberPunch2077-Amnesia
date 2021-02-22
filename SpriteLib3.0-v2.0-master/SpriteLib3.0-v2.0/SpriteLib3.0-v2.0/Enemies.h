#pragma once
#include "PhysicsBody.h"
#include "Sprite.h"

/*enum class ZombAnimEnums
{
	Standing = 0,
	Moving = 1,
};*/
class Enemy
{
private:
	float health = 10.f; // Enemy Health
	float movementSpeed = -4.f; // Enemy movementspeed
	Sprite* m_sprite = nullptr;
	Transform* m_transform = nullptr;
	PhysicsBody* m_physBody = nullptr;
public:
	Enemy();
	void InitEnemy(std::string& fileName, int width, int height, Sprite* sprite, Transform* transform, PhysicsBody* body = nullptr);
	void AttachBody(PhysicsBody* body);
	float getMovementSpeed();
	float getEnemyHealth();
	void enemyUpdate(PhysicsBody* EnemyPhysicsBody, std::vector <unsigned int>* eEnts, int Eentity);
};
