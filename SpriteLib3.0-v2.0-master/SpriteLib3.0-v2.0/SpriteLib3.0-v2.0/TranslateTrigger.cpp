#include "TranslateTrigger.h"
#include "ECS.h"

void TranslateTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void TranslateTrigger::OnEnter()
{
	Trigger::OnEnter();

	for (int i = 0; i < m_targetEntities.size(); i++)
	{
		
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).SetPosition(b2Vec2(float32(0.f), float32(35.f)),true);
		//ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetPosition() + movement, true
	}
}

void TranslateTrigger::OnExit()
{
	Trigger::OnExit();
}
