#pragma once

#include "ECS.h"
#include "PhysicsBody.h"
#include "Timer.h"
#include "MainEntities.h"
#include "Shader.h"

namespace PhysicsSystem
{
	//Initalizes the system
	void Init();
	void InitDebugDrawPlaneVAO();

	//Update the system
	void Update(entt::registry* reg, b2World& world);

	//Draw all entities with physics bodies
	//*only if the static "m_drawBodies" is true
	void Draw(entt::registry* reg);

	//Run our collision detection (will run different collision detection using physics body
	void Run(b2World& world);

	//Cleanup bodies after step
	void CleanupBodies();
}