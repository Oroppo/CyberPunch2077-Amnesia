#pragma once
#include "Enemies.h"
#include "PhysicsBody.h"
#include "Sprite.h"
#include "Timer.h"
#include "Combat.h"

class BossEnemy : public Shared
{
private:
	int detection = 150;
	vec3 moveB = vec3(0, 0, 0);
	vec2 movementB = vec2(0, 0);
	int LorR = 0; // checks if player is left or right of Boss

	Sprite* m_sprite = nullptr;
	Transform* m_transform = nullptr;
	PhysicsBody* m_physBody = nullptr;
public:
	BossEnemy();
	void InitBoss(std::string& fileName, int width, int height, Sprite* sprite, Transform* transform, PhysicsBody* body = nullptr);
	void AttachBossBody(PhysicsBody* body);
	void idle(float distanceX, float distanceY, PhysicsBody* BossPhysicsBody);
	void chase(float distanceX, float distanceY, PhysicsBody* BossPhysicsBody);
	void fight(PhysicsBody* BossPhysicsBody);
	void destroyBoss(std::vector <unsigned int>* BEnts, int Bentity)
	{
		for (int i = 0; i < BEnts->size(); i++) {
			if (BEnts->at(i) == Bentity) {
				BEnts->erase(BEnts->begin() + i);
			}
		}
		PhysicsBody::m_bodiesToDelete.push_back(Bentity);
	}
	void BossUpdate(PhysicsBody* BossPhysicsBody, std::vector <unsigned int>* BEnts, int Bentity);
};

