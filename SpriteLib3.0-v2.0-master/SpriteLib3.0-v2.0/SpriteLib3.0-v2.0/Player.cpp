#include "Player.h"
#include "Utilities.h"
#include "Combat.h"
//#include "Enemies.h"
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


	//NEW ANIMATIONS\\

	m_animController->AddAnimation(animations["RunRight"].get<Animation>());
	m_animController->AddAnimation(animations["JumpRight"].get<Animation>());
	m_animController->AddAnimation(animations["SliceRight"].get<Animation>());
	m_animController->AddAnimation(animations["KickRight"].get<Animation>());
	m_animController->AddAnimation(animations["LandRight"].get<Animation>());
	m_animController->AddAnimation(animations["TurnRight"].get<Animation>());


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
	m_animController->SetActiveAnim(IDLERIGHT);

	
}

void Player::Update()
{
	if (!m_locked)
	{
		MovementUpdate();
	}
	//AnimationUpdate();
}

void Player::MovementUpdate()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
	b2Vec2 vel = b2Vec2(0.f, 0.f);
	//std::cout << player.GetBody()->GetLinearVelocity().y<<"\n";
	//std::cout << player.GetBody()->GetLinearVelocity().x << "\n";
		if (Input::GetKey(Key::A))
		{
			if (player.GetBody()->GetLinearVelocity().x > -100.f) {
			vel = b2Vec2(-1250000.f , 1.f);
			}
			player.GetBody()->ApplyForceToCenter(b2Vec2(vel), true);
		}
		if (Input::GetKey(Key::D))
		{
			if (player.GetBody()->GetLinearVelocity().x < 100.f) {
				vel = b2Vec2(1250000.f, 1.f);
			}
			player.GetBody()->ApplyForceToCenter(b2Vec2(vel), true);
		
		}


		if (Input::GetKey(Key::I))
		{
		
		}

	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}

	

	if (canJump.m_canJump==true)
	{
		if (Input::GetKeyDown(Key::Space))
		{
			xdiff = player.GetBody()->GetLinearVelocity().x;
			jumpGrav = 5;
			canJump.m_canJump = false;
		}
	}
	else if (canJump.m_canJump == false) {
		jumpGrav-=0.15f;
		if (Input::GetKey(Key::A))
		{
			if (xdiff > -101) {
				xdiff -= 20;
			}
		}
		if (Input::GetKey(Key::D))
		{
			if (xdiff <101) {
				xdiff += 20;
			}
		}
		player.SetPosition(b2Vec2(player.GetPosition().x+(xdiff/50), player.GetPosition().y+jumpGrav), true);
		player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 1.f), true);

	}
}

float Player::PlayerAttack(COORD Position)
{
	if (Input::GetKey(Key::O))
	{
		//Animation Controller for Player
		auto& animController = ECS::GetComponent<AnimationController>(3);
		//Could wrap this into a function because god is this a pain in the ass to write but nah
		//std::cout << "player pressed attack key" << std::endl;
		do {
			animController.SetActiveAnim(3);
			if ((Position.X < 50.0) && (Position.X > 0.0)) {
				return 10;
			}
			else if (Position.X > 50.0) {
				return 0;
			}
			if ((Position.X > -50.0) && (Position.X < 0.0)) {
				return 10;
			}
			else if (Position.X < -50.0) {
				return 0;
			}
				animController.SetActiveAnim(0);
		} while (m_animController->GetAnimation(m_animController->GetActiveAnim()).GetAnimationDone());
	}
}
void Player::AnimationUpdate()
{
	int activeAnimation = 0;

	if (m_moving)
	{
		//Puts it into the WALK category
		activeAnimation = RUNRIGHT;
	}
	else if (m_attacking)
	{
		activeAnimation = SLICERIGHT;

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


