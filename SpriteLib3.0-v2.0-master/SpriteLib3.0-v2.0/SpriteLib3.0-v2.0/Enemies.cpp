#include "Enemies.h"
#include "Utilities.h"
Enemy::Enemy()
{
}

void Enemy::InitEnemy(std::string& fileName, int width, int height, Sprite* sprite, Transform* transform, PhysicsBody* body)
{

	m_sprite = sprite;
	m_transform = transform;
	m_physBody = body;

	m_sprite->LoadSprite(fileName, width, height, false);
}


float Enemy::getMovementSpeed()
{
	return movementSpeed;
}

void Enemy::setMovementSpeed(float newSpeed)
{
	movementSpeed = newSpeed;
}

float Enemy::getEnemyHealth()
{
	return health;
}
void Enemy::setEnemyHealth(float newHealth)
{
	health = newHealth;
}

// Enemy idle state
void Enemy::idle(float distanceX, float distanceY)
{
	if (distanceX < 0)
	{
		// if player is past than a certain point then chase
		if (distanceX > (detection * -1))
		{
			LorR = 1;
			chase(distanceX, distanceY);
		}
	}
	// if player is right of enemy then
	else
	{
		// if player is greater than a certain point then chase
		if (distanceX < detection)
		{
			LorR = 2;
			chase(distanceX, distanceY);
		}
	}
}
// enemy chase state
void Enemy::chase(float distanceX, float distanceY)
{
	move = vec3(distanceX / 3, 0, 0);
	m_physBody->SetVelocity(move);

	if (LorR == 1)
	{
		if (distanceX >= -30)
		{
			fight();
		}
	}
	else
	{
		if (distanceX >= 30)
		{
			fight();
		}
	}
}
// enemy fight state - not implemented yet
void Enemy::fight()
{
	//std::cout << "Fight mode activated" << std::endl;
}

void Enemy::enemyUpdate(PhysicsBody* EnemyPhysicsBody, std::vector <unsigned int>* eEnts, int Eentity)
{
	// movement vector
	vec3 move = vec3(0, 0, 0);
	vec2 movement = vec2(0, 0);

	// finding distance between player and enemy physics body
	movement = vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x - EnemyPhysicsBody->GetPosition().x,
		ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y - EnemyPhysicsBody->GetPosition().y);
	//std::cout << "X Distance is " << movement.x << std::endl;
	//std::cout << "Y Distance is " << movement.y << std::endl;

	float distanceX = movement.x;
	float distanceY = movement.y;

	idle(distanceX, distanceY);
}

void Enemy::AttachBody(PhysicsBody* body)
{
	m_physBody = body;
}