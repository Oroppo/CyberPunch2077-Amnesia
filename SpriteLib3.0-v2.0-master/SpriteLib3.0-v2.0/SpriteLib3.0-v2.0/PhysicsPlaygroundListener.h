#pragma once

#include <Box2D/Box2D.h>

class PhysicsPlaygroundListener : public b2ContactListener
{
public:
	PhysicsPlaygroundListener();

	bool IsTouchingGround();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
private:
	bool Touch = false;
	void TriggerEnter(b2Fixture* sensor);
	void TriggerExit(b2Fixture* sensor);
};

