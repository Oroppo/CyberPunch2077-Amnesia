#pragma once
class Shared {
protected:
	// enemy health and damage values
	float initialEHealth = 30;
	float Ehealth = 30;
	float Edamage = 10;

	// vector drawn between enemy to player
	float EtoPXcord;
	float EtoPYcord;

	// player health and damage values
	float Phealth = 80;
	float Pdamage = 10;

public:
	void setEhealth();
	void setPhealth();
	void getEhealth();
	void getPhealth();
	
};