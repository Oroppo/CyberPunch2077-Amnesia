#include "BossEnemy.h"
#include "Utilities.h"
#include "PhysicsBody.h"
#include"Player.h"
#include <Vector>
#include "ECS.h"

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
	bool sheildOn = false;
	// is the player left of boss
	if (distanceBX < 0)
	{
		// if player is past than a certain point then chase
		if (distanceBX > (detection * -1))
		{
				//sheildOn = true;
				LorR = 1;
				chase(distanceBX, distanceBY, BossPhysicsBody, sheildOn);
		}
	}
	// if player is right of enemy then
	else
	{
		//sheildOn == true;
		// if player is greater than a certain point then chase
		if (distanceBX < detection)
		{
				LorR = 2;
				chase(distanceBX, distanceBY, BossPhysicsBody, sheildOn);
		}
	}
}

// enemy chase state
void BossEnemy::chase(float distanceBX, float distanceBY, PhysicsBody* BossPhysicsBody, bool sheildOn)
{
	// move down
	//if (sheildOn == false)
	//{
	//	moveB = vec3(0, -10, 0);
	//	BossPhysicsBody->SetVelocity(moveB);
	//}
	// move/stay up
	if (sheildOn == true && distanceBY <= -124)
	{
		moveB = vec3(0, 10, 0);
		BossPhysicsBody->SetVelocity(moveB);
	}
	// move/stay up
	if (sheildOn == true && distanceBY < -130)
	{
		moveB = vec3(0, -10, 0);
		BossPhysicsBody->SetVelocity(moveB);
	}

	fight(BossPhysicsBody, distanceBX, distanceBY);
}

void BossEnemy::laserBeam()
{

	/*if (beamOn == 0 || beamOn == 1)
	{
		if (highOrLow == 0)
		{
			ECS::GetComponent<Sprite>(92).SetTransparency(1.f);
		}

		if (highOrLow == 1)
		{
			ECS::GetComponent<Sprite>(93).SetTransparency(1.f);
		}
		if (laserBeamTimer > 0)
		{
			laserBeamTimer -= Timer::deltaTime;
			if (laserBeamTimer <= 0)
			{
				ECS::GetComponent<Sprite>(92).SetTransparency(0.f);
				ECS::GetComponent<Sprite>(93).SetTransparency(0.f);
				laserBeamTimer = 0;
				beamOn = 3;
			}
		}
	}*/

	if (laserBeamTimer > 0)
	{
		laserBeamTimer -= Timer::deltaTime;
		if (laserBeamTimer <= 0)
		{
			ECS::GetComponent<Sprite>(92).SetTransparency(0.f);
			ECS::GetComponent<Sprite>(93).SetTransparency(0.f);
			laserBeamTimer = 0;
			beamOn = 3;
		}
	}
}

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
		ECS::GetComponent<Sprite>(90).SetTransparency(1.f);
	}
	// if it decides to shoot high make ground laser pointer appear
	if (highOrLow == 1)
	{
		ECS::GetComponent<Sprite>(91).SetTransparency(1.f);
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
				if (distanceBX > -833 && distanceBX < -65 && distanceBY < -70)
				{
					//Phealth = Phealth - Bdamage;
					std::cout << "Player is in lazer beam in trenches" << std::endl;
					ECS::GetComponent<Sprite>(90).SetTransparency(0.f);
					ECS::GetComponent<Sprite>(91).SetTransparency(0.f);
					beamOn = 0;
					//laserBeamTimer = 1;
				}

				// see if player is in range to get hit by lazer beam on the ground (Can jump over)
				if (distanceBX > -1040 && distanceBX < -2 && distanceBY > -75 && distanceBY < 3)
				{
					//Phealth = Phealth - Bdamage;
					std::cout << "Player is in lazer beam on ground" << std::endl;
					ECS::GetComponent<Sprite>(91).SetTransparency(0.f);
					ECS::GetComponent<Sprite>(90).SetTransparency(0.f);
					beamOn = 1;
					//laserBeamTimer = 1;
				}

				if (beamOn == 0 || beamOn == 1)
				{
					if (highOrLow == 0)
					{
						ECS::GetComponent<Sprite>(92).SetTransparency(1.f);
					}

					if (highOrLow == 1)
					{
						ECS::GetComponent<Sprite>(93).SetTransparency(1.f);
					}
				}
				laserBeamTimer = 1;
				highOrLow = 3;
				timer2 = 5;

			}
		}
}

void BossEnemy::BossUpdate(PhysicsBody* BossPhysicsBody, std::vector <unsigned int>* bEnts, int bentity)
{
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

	//COORD pos;
	//pos.X = movement.x;
	//pos.Y = movement.y;
	//Player temp;

	//Ehealth -= temp.PlayerAttack(pos);
	idle(distanceBX, distanceBY, BossPhysicsBody);
	laserBeam();
	//if (Ehealth <= 0)
	//{
	//	destroyEnemy(eEnts, Eentity);
	//}
	//std::cout << "(BossUpdate) random number is " << highOrLow << std::endl;
}

void BossEnemy::AttachBossBody(PhysicsBody* body)
{
	m_physBody = body;
}