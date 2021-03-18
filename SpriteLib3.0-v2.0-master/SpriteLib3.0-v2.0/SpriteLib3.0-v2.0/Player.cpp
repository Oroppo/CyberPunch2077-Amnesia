#include "Player.h"
#include "Utilities.h"
Player::Player()
{
}

Player::Player(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, 
					AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	InitPlayer(fileName, animationJSON, width, height, sprite, controller, transform, hasPhys, body);
}

void Player::InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, 
							AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	//Store references to the components
	m_sprite = sprite;
	m_animController = controller;
	m_transform = transform;
	m_hasPhysics = hasPhys;
	if (hasPhys)
	{
		m_physBody = body;
	}

	//Initialize UVs
	m_animController->InitUVs(fileName);

	//Loads the texture and sets width and height
	m_sprite->LoadSprite(fileName, width, height, true, m_animController);
	m_animController->SetVAO(m_sprite->GetVAO());
	m_animController->SetTextureSize(m_sprite->GetTextureSize());

	//Loads in the animations json file
	nlohmann::json animations = File::LoadJSON(animationJSON);

	//IDLE ANIMATIONS\\
	
	//Idle Left
	m_animController->AddAnimation(animations["IdleLeft"].get<Animation>());
	//Idle Right
	m_animController->AddAnimation(animations["IdleRight"].get<Animation>());
#ifdef TOPDOWN
	//Idle Up
	m_animController->AddAnimation(animations["IdleUp"].get<Animation>());
	//Idle Down
	m_animController->AddAnimation(animations["IdleDown"].get<Animation>());
#endif

	//Walk Animations\\

	//WalkLeft
	m_animController->AddAnimation(animations["WalkLeft"].get<Animation>());
	//WalkRight
	m_animController->AddAnimation(animations["WalkRight"].get<Animation>());
#ifdef TOPDOWN
	//WalkUP
	m_animController->AddAnimation(animations["WalkUp"].get<Animation>());
	//WalkDown
	m_animController->AddAnimation(animations["WalkDown"].get<Animation>());
#endif

	//Attack Animations\\

	//AttackLeft
	m_animController->AddAnimation(animations["AttackLeft"].get<Animation>());
	//AttackRight
	m_animController->AddAnimation(animations["AttackRight"].get<Animation>());
#ifdef TOPDOWN
	//AttackUp
	m_animController->AddAnimation(animations["AttackUp"].get<Animation>());
	//AttackDown
	m_animController->AddAnimation(animations["AttackDown"].get<Animation>());
#endif

	//Set Default Animation
	m_animController->SetActiveAnim(IDLELEFT);


}

void Player::Update()
{
	if (!m_locked)
	{
		MovementUpdate();
	}

	//AnimationUpdate();
}

static float speed = 0.f;
void Player::MovementUpdate()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());

	b2Vec2 vel = b2Vec2(0.f, 0.f);
	//if (canJump.m_canJump == true) {
		if (Input::GetKey(Key::A))
		{
			if (speed > -4.0) { speed -= 0.5; }
			vel = b2Vec2(100000.f * speed, 1.f);
			//std::cout << vel.x<<std::endl;
			player.GetBody()->ApplyForceToCenter(b2Vec2(vel), true);
			player.GetBody()->GetLinearVelocity();
		}
		if (Input::GetKey(Key::D))
		{
			if (speed < 4.0) { speed += 0.5; }
			vel = b2Vec2(100000.f * speed, 1.f);
			player.GetBody()->ApplyForceToCenter(b2Vec2(vel), true);

		}
//	}
		if (Input::GetKey(Key::O))
		{

		}
		if (Input::GetKey(Key::I))
		{
		}

	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
	if (canJump.m_canJump)
	{
		if (Input::GetKeyDown(Key::Space))
		{
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 700000.f), true);
			canJump.m_canJump = false;
		}
	}
}
float Player::PlayerAttack(COORD Position) {
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
vec2 distance = vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x - Position.X,
	ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y - Position.Y);
AtkDistance = sqrt(pow(distance.y, 2) + pow(distance.y, 2));
if (AtkDistance < 30.0) {
	return 1;
}
else if (AtkDistance > 30.0) {
	return 0;
}
}
void Player::AnimationUpdate()
{
	int activeAnimation = 0;

	if (m_moving)
	{
		//Puts it into the WALK category
		activeAnimation = WALK;
	}
	else if (m_attacking)
	{
		activeAnimation = ATTACK;

		//Check if the attack animation is done
		if (m_animController->GetAnimation(m_animController->GetActiveAnim()).GetAnimationDone())
		{
			//Will auto set to idle
			m_locked = false;
			m_attacking = false;
			//Resets the attack animation
			m_animController->GetAnimation(m_animController->GetActiveAnim()).Reset();

			activeAnimation = IDLE;
		}
	}
	else
	{
		activeAnimation = IDLE;
	}

	SetActiveAnimation(activeAnimation + (int)m_facing);
}

void Player::SetActiveAnimation(int anim)
{
	m_animController->SetActiveAnim(anim);
}
void Player::AttachBody(PhysicsBody* body) {
	m_physBody = body;
}