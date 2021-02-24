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
	float movementSpeed = -20.f; // Enemy movementspeed
	int detection = 150; // Enemy detection legnth
	//int state; // 1-3 1 = idle, 2 = chase 3 = fight
	vec3 move = vec3(0, 0, 0); // Movement vectors
	vec2 movement = vec2(0, 0);
	int LorR = 0; // checks if player is left or right of enemy

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
	void idle(float distanceX, float distanceY);
	void chase(float distanceX, float distanceY);
	void fight();


	void enemyUpdate(PhysicsBody* EnemyPhysicsBody, std::vector <unsigned int>* eEnts, int Eentity);
};
