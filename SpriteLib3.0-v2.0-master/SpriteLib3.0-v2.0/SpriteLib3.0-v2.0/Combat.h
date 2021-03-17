#pragma once
class Shared {
protected:
	float Ehealth = 30;
	float Edamage = 10;
	float Phealth = 80;
	float Pdamage = 10;
public:
	void setEhealth();
	void setPhealth();
	void getEhealth();
	void getPhealth();
};