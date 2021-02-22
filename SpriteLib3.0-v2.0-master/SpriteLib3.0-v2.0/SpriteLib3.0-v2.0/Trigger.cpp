#include "Trigger.h"

#include "ECS.h"

void Trigger::OnTrigger()
{
	//make the object linked transparent
	ECS::GetComponent<Sprite>(m_triggerEntity).SetTransparency(0.2f);
}

void Trigger::OnEnter()
{	//Tests the trigger working and displays using T
	ECS::GetComponent<PhysicsBody>(m_triggerEntity).SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
}

void Trigger::OnExit()
{
	//make the object linked opaque
	ECS::GetComponent<PhysicsBody>(m_triggerEntity).SetColor(vec4(1.f, 0.f, 0.f, 0.3f));
}

void Trigger::SetTriggerEntity(int triggerEnt)
{
	m_triggerEntity = triggerEnt;
}

int Trigger::GetTriggerEntity()
{
	return m_triggerEntity;
}

void Trigger::AddTargetEntity(int entity)
{
	m_targetEntities.push_back(entity);
}

void Trigger::SetTargetEntities(std::vector<int> entities)
{
	m_targetEntities = entities;
}

std::vector<int> Trigger::GetTargetEntities()
{
	return m_targetEntities;
}
