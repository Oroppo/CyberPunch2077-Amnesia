#include "BossEnemy.h"
#include "Utilities.h"
#include "PhysicsBody.h"
#include"Player.h"
#include <Vector>
#include "ECS.h"
#include "Combat.h"

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
	// is the player left of boss
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
	// move down
	if (sheildOn == 0)
	{
		moveB = vec3(0, -10, 0);
		BossPhysicsBody->SetVelocity(moveB);
		if (BossPhysicsBody->GetPosition().y <= 601)
		{
			dodgeCounter = 0;
		}
	}
	// move up
	if (sheildOn == 1)
	{
		moveB = vec3(0, 10, 0);
		BossPhysicsBody->SetVelocity(moveB);
	}
	// reset position and sheild
	if (sheildOn == 1 && BossPhysicsBody->GetPosition().y > 650)
	{
		moveB = vec3(0, 0, 0);
		BossPhysicsBody->SetVelocity(moveB);
		BossPhysicsBody->SetPosition(b2Vec2(8750.f, 650.f));
		ECS::GetComponent<Sprite>(95).SetTransparency(1.f);
		sheildOn = 3;
	}
	if (sheildOn != 0)
	{
		fight(BossPhysicsBody, distanceBX, distanceBY);
	}
}

void BossEnemy::laserBeam()
{
	if (laserBeamTimer > 0)
	{
		laserBeamTimer -= Timer::deltaTime;
		if (laserBeamTimer <= 0)
		{
			ECS::GetComponent<Sprite>(93).SetTransparency(0.f);
			ECS::GetComponent<Sprite>(94).SetTransparency(0.f);
			laserBeamTimer = 0;
			beamOn = 3;
		}
	}
}

void BossEnemy::sheild()
{
	if (sheildOn == 0)
	{
		//std::cout << "Timer3 is " << timer3 << std::endl;
		if (timer3 > 0)
		{
			// decreases timer until it reaches 0
			timer3 -= Timer::deltaTime;
			// when the timer reaches 0 the boss's sheild will be turned back on
			if (timer3 <= 0)
			{
				sheildOn = 1;
				timer3 = 5;
			}
		}
	}
}


/*float BossEnemy::BossAttack()
{
	std::cout << "Can Attack is  " << CanAttack << std::endl;
	if (CanAttack == 1)
	{
		return Bdamage;
		std::cout << "Can Attack =  " << CanAttack << std::endl;
	}
	//CanAttack = 0;
}*/

void BossEnemy::fight(PhysicsBody* BossPhysicsBody, float distanceBX, float distanceBY)
{
	// determinte wether to shoot lazer high or low (1= high 0 = low)
	if (highOrLow == 3)
	{
		srand(time(NULL));
		highOrLow = rand() % 2;
		std::cout << "High or low is " << highOrLow << std::endl;
	}
	// if it decides to shoot low make trench laser pointer appear
	if (highOrLow == 0)
	{
		ECS::GetComponent<Sprite>(91).SetTransparency(1.f);
	}
	// if it decides to shoot high make ground laser pointer appear
	if (highOrLow == 1)
	{
		ECS::GetComponent<Sprite>(92).SetTransparency(1.f);
	}
	//std::cout << "Timer is " << timer2 << std::endl;
		if (timer2 > 0)
		{
			// decreases timer until it reaches 0
			timer2 -= Timer::deltaTime;
			// when timer reaches 0 enemy will attack player dealing damage to player's health and reseting timer back to 5
			if (timer2 <= 0)
			{
					// see if player is in range to get hit by laser in trenches
				if (distanceBX > -933 && distanceBX < -165 && distanceBY < -75)
				{
					ECS::GetComponent<Sprite>(91).SetTransparency(0.f);
					ECS::GetComponent<Sprite>(92).SetTransparency(0.f);
					beamOn = 0;
					if (highOrLow == 0)
					{
						Phealth = Phealth - Bdamage;
						std::cout << "Player got hit by the lazer beam in trenches" << std::endl;
						dodgeCounter = 0;
					}
					else
					{
						dodgeCounter++;
					}
				}

				// see if player is in range to get hit by lazer beam on the ground (Can jump over)
				if (distanceBX > -1040 && distanceBX < -2 && distanceBY > -75 && distanceBY < 3)
				{
					ECS::GetComponent<Sprite>(92).SetTransparency(0.f);
					ECS::GetComponent<Sprite>(91).SetTransparency(0.f);
					beamOn = 1;
					if (highOrLow == 1)
					{
						Phealth = Phealth - Bdamage;
						std::cout << "Player got hit by the lazer beam on ground" << std::endl;
						dodgeCounter = 0;
					}
					else
					{
						dodgeCounter++;
					}
				}

				if (beamOn == 0 || beamOn == 1)
				{
					if (highOrLow == 0)
					{
						// trenches beam
						ECS::GetComponent<Sprite>(93).SetTransparency(1.f);
					}

					if (highOrLow == 1)
					{
						// ground beam
						ECS::GetComponent<Sprite>(94).SetTransparency(1.f);
					}
				}
				laserBeamTimer = 1;
				highOrLow = 3;
				timer2 = 3;

			}
		}
}

void BossEnemy::BossUpdate(PhysicsBody* BossPhysicsBody, std::vector <unsigned int>* bEnts, int bentity)
{
	//std::cout << Phealth << std::endl;
	std::cout << Bhealth << std::endl;
	//std::cout << BossPhysicsBody->GetPosition().y << std::endl;

	// movement vector
	vec3 moveB = vec3(0, 0, 0);
	vec2 movementB = vec2(0, 0);
	// finding distance between player and enemy physics body
	movementB = vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x - BossPhysicsBody->GetPosition().x,
		ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y - BossPhysicsBody->GetPosition().y);
	//std::cout << "X Distance is " << movementB.x << std::endl;
	//std::cout << "Y Distance is " << movementB.y << std::endl;
	float distanceBX = movementB.x;
	float distanceBY = movementB.y;

	if (sheildOn == 0)
	{
		// player attack code
		COORD posB;
		posB.X = movementB.x;
		posB.Y = movementB.y;
		Player tempB;
		Bhealth -= tempB.PlayerAttack(posB);
	}

	// call to boss functions
	if (dodgeCounter >= 3)
	{
		// turn shield off
		sheildOn = 0;
		ECS::GetComponent<Sprite>(95).SetTransparency(0.f);
	}
	idle(distanceBX, distanceBY, BossPhysicsBody);
	laserBeam();
	sheild();

	// decide if player dies or if boss dies
	if (Bhealth <= 0)
	{
		destroyBoss(bEnts, bentity);
	}
	if (Phealth <= 0)
	{
		TeleportPlayer();
	}
}

void BossEnemy::AttachBossBody(PhysicsBody* body)
{
	m_physBody = body;
}

void BossEnemy::TeleportPlayer()
{
	ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(0.f, 30.f));
	Phealth = 100;
}