#pragma once
#include "PhysicsBody.h"
#include "Sprite.h"
#include "Timer.h"

class Shared
{
protected:
	// enemy health and damage values
	float Ehealth = 150;
	float initialEHealth = 150;
	float Edamage = 20;
	float Bhealth = 350;
	float Bdamage = 20;
	// vector drawn between enemy to player
	float EtoPXcord;
	float EtoPYcord;

	// player health and damage values
	float Phealth = 100;
	float Pdamage = 30;

public:
	void setEhealth();
	void setPhealthFromE();
	void setPhealthFromB();
	float getEhealth();
	float getPhealth()
	{
		return Phealth;
	}
	void combatUpdate();
};