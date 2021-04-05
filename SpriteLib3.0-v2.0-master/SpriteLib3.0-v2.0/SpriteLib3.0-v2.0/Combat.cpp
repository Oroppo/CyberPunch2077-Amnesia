#include "Combat.h"

void Shared::combatUpdate()
{
}

void Shared::setPhealthFromB()
{
}
void Shared::setPhealthFromE()
{
	Phealth = Phealth - Edamage;
}

void Shared::setEhealth()
{
	Ehealth = Ehealth - Pdamage;
}