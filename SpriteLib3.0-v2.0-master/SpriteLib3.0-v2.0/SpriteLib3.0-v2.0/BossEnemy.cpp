#include "BossEnemy.h"
#include "Utilities.h"
#include "PhysicsBody.h"
#include"Player.h"
#include <Vector>

BossEnemy::BossEnemy()
{
}
// reload's enemy
void BossEnemy::InitBoss(std::string& fileName, int width, int height, Sprite* sprite, Transform* transform, PhysicsBody* body)
{
	m_sprite = sprite;
	m_transform = transform;
	m_physBody = body;

	m_sprite->LoadSprite(fileName, width, height, false);
}

// Boss idle state
void BossEnemy::idle(float distanceBX, float distanceBY, PhysicsBody* BossPhysicsBody)
{
	if (distanceBX < 0)
	{
		// if player is past than a certain point then chase
		if (distanceBX > (detection * -1))
		{
				LorR = 1;
				chase(distanceBX, distanceBY, BossPhysicsBody);
		}
	}
	// if player is right of enemy then
	else
	{
		// if player is greater than a certain point then chase
		if (distanceBX < detection)
		{
				LorR = 2;
				chase(distanceBX, distanceBY, BossPhysicsBody);
		}
	}
}

// enemy chase state
void BossEnemy::chase(float distanceBX, float distanceBY, PhysicsBody* BossPhysicsBody)
{
	moveB = vec3(distanceBX / 3, 0, 0);
	BossPhysicsBody->SetVelocity(moveB);
	if (distanceBY >= 300)
	{
		moveB = vec3(0, 50, 0);
		BossPhysicsBody->SetVelocity(moveB);
	}
	if (LorR == 1)
	{
		if (distanceBX >= -50)
		{
			//fight(BossPhysicsBody);
		}
		else
		{
			//resetTimer();
		}
	}

	if (LorR == 2)
	{
		if (distanceBX <= 50)
		{
			//fight(BossPhysicsBody);
		}
		else
		{
			//resetTimer();
		}
	}
}

/*void Enemy::fight(PhysicsBody* EnemyPhysicsBody)
{

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
}*/

void BossEnemy::BossUpdate(PhysicsBody* BossPhysicsBody, std::vector <unsigned int>* bEnts, int bentity)
{
	// movement vector
	vec3 moveB = vec3(0, 0, 0);
	vec2 movementB = vec2(0, 0);
	// finding distance between player and enemy physics body
	movementB = vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x - BossPhysicsBody->GetPosition().x,
		ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y - BossPhysicsBody->GetPosition().y);

	float distanceBX = movementB.x;
	float distanceBY = movementB.y;

	//COORD pos;
	//pos.X = movement.x;
	//pos.Y = movement.y;
	//Player temp;

	//Ehealth -= temp.PlayerAttack(pos);
	//internalTime(EnemyPhysicsBody);
	idle(distanceBX, distanceBY, BossPhysicsBody);
	//if (Ehealth <= 0)
	//{
	//	destroyEnemy(eEnts, Eentity);
	//}
}

void BossEnemy::AttachBossBody(PhysicsBody* body)
{
	m_physBody = body;
}