#pragma once
class Shared {
protected:
	// enemy health and damage values
	float initialEHealth = 200;
	float Ehealth = 25;
	float Edamage = 10;
	float Bhealth = 500;
	float Bdamage = 20;
	// vector drawn between enemy to player
	float EtoPXcord;
	float EtoPYcord;

	// player health and damage values
	float Phealth = 80;
	float Pdamage = 5;

public:
	void setEhealth();
	void setPhealth();
	void getEhealth();
	void getPhealth();
	
};