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

void Enemy::enemyUpdate(PhysicsBody* EnemyPhysicsBody, std::vector <unsigned int>* eEnts, int Eentity)
{
	// movement vector
	vec3 move = vec3(0, 0, 0);
	vec2 movement = vec2(0, 0);

	// finding distance between player and enemy physics body
	movement = vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x - EnemyPhysicsBody->GetPosition().x,
		ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y - EnemyPhysicsBody->GetPosition().y);
	std::cout << "X Distance is " << movement.x << std::endl;
	std::cout << "Y Distance is " << movement.y << std::endl;

	float distanceX = movement.x;
	float distanceY = movement.y;

	move = vec3(distanceX / 8, 0, 0);
	m_physBody->SetVelocity(move);
}

void Enemy::AttachBody(PhysicsBody* body)
{
	m_physBody = body;
}