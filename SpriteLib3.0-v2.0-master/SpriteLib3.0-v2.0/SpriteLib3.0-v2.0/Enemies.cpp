#include "Enemies.h"
#include "Utilities.h"
#include "PhysicsBody.h"
#include"Player.h"
#include <Vector>
// enemy constructor
Enemy::Enemy()
{
}
// reload's enemy
void Enemy::InitEnemy(std::string& fileName, int width, int height, Sprite* sprite, Transform* transform, PhysicsBody* body)
{

	m_sprite = sprite;
	m_transform = transform;
	m_physBody = body;

	m_sprite->LoadSprite(fileName, width, height, false);
}

// return enemy's movement speed
float Enemy::getMovementSpeed()
{
	return movementSpeed;
}
// sets movement speed of enemies (not implemented)
void Enemy::setMovementSpeed(float newSpeed)
{
	movementSpeed = newSpeed;
}
// returns enemy's health
float Enemy::getEnemyHealth()
{
	return Ehealth;
}
// sets health of enemies
void Enemy::setEnemyHealth(float newHealth)
{
	Ehealth = newHealth;
}

void Enemy::resetTimer()
{
		timer = 5;
}

void Enemy::internalTime(PhysicsBody* EnemyPhysicsBody)
{
	// vector 3 for knockback on enemies
	vec3 knockbackRight(800000000, 5000000000, 0);
	vec3 knockbackLeft(-800000000, -500000000, 0);
	//When attacked set internalTime to 1
	//change constant to however much damage the player deals to enemies
	//std::cout << "Ehealth is " << Ehealth << std::endl;
	if (initialEHealth > Ehealth && LorR == 2)
	{

		EnemyPhysicsBody->ApplyForce(knockbackLeft);
		initialEHealth = Ehealth;
		internalTimer = 1;
	}
	else if (initialEHealth > Ehealth && LorR == 1)
	{

		EnemyPhysicsBody->ApplyForce(knockbackRight);
		initialEHealth = Ehealth;
		internalTimer = 1;
	}

	// if the internal timer is great than 0 it will count it down till it reaches 0
	if (internalTimer > 0)
	{
		internalTimer -= Timer::deltaTime;
		if (internalTimer <= 0)
		{
			internalTimer = 0;
		}
	}
}

// Enemy idle state
void Enemy::idle(float distanceX, float distanceY, PhysicsBody* EnemyPhysicsBody)
{
	if (distanceX < 0)
	{
		// if player is past than a certain point then chase
		if (distanceX > (detection * -1))
		{
			LorR = 1;
			chase(distanceX, distanceY, EnemyPhysicsBody);
		}
	}
	// if player is right of enemy then
	else
	{
		// if player is greater than a certain point then chase
		if (distanceX < detection)
		{
			LorR = 2;
			chase(distanceX, distanceY, EnemyPhysicsBody);
		}
	}
}

// enemy chase state
void Enemy::chase(float distanceX, float distanceY, PhysicsBody* EnemyPhysicsBody)
{
	move = vec3(distanceX / 3, 0, 0);
	EnemyPhysicsBody->SetVelocity(move);
	if (LorR == 1)
	{
		if (distanceX >= -50)
		{
			fight(EnemyPhysicsBody);
		}
		else
		{
			resetTimer();
		}
	}

	if (LorR == 2)
	{
		if (distanceX <= 50)
		{
			fight(EnemyPhysicsBody);
		}
		else
		{
			resetTimer();
		}
	}
}
// enemy fight state - not implemented yet
void Enemy::fight(PhysicsBody* EnemyPhysicsBody)
{

	// create something here for enemy taking damage. Maybe a class player and enemy inherit from?

	//std::cout << "Timer is " << timer << std::endl;
	//std::cout << "internal Timer is " << internalTimer << std::endl;
	// will control enemys attacking when not currently being attacked
	if (internalTimer <= 0)
	{
		// controls when enemy will attack when within proximity to player
		if (timer > 0)
		{
			// decreases timer until it reaches 0
			timer -= Timer::deltaTime;
			// when timer reaches 0 enemy will attack player dealing damage to player's health and reseting timer back to 5
			if (timer <= 0)
			{
				// decrease player's health here and play enemy attack animation and player taking damage animation
				std::cout << "Timer hit 0 attack here" << std::endl;
				Phealth = Phealth - Edamage;
				timer = 5;
			}
		}
	}
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

	 EtoPXcord = movement.x;
	 EtoPYcord = movement.y;
	 COORD pos;
	 pos.X = movement.x;
	 pos.Y = movement.y;
	 Player temp;

	 if (Ehealth == 0) {
		 destroyEnemy(eEnts,Eentity);
	 }

	 Ehealth -= temp.PlayerAttack(pos) ;
	internalTime(EnemyPhysicsBody);
	idle(distanceX, distanceY, EnemyPhysicsBody);
}

void Enemy::AttachBody(PhysicsBody* body)
{
	m_physBody = body;
}



	

