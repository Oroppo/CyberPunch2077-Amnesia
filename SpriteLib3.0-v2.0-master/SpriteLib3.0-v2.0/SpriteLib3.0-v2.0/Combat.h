#pragma once
class Shared {
protected:
	// enemy health and damage values
	float initialEHealth = 50;
	float Ehealth = 50;
	float Edamage = 10;
	float Bhealth = 500;
	float Bdamage = 20;
	// vector drawn between enemy to player
	float EtoPXcord;
	float EtoPYcord;

	// player health and damage values
	float Phealth = 80;
	float Pdamage = 10;

public:
	void setEhealth();
	void setPhealth();
	float getEhealth();
	float getPhealth()
	{
		return Phealth;
	}
	
};