#include "Player.h"
#include "Utilities.h"
#include "Combat.h"
#include "PhysicsPlaygroundListener.h"
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
	//m_animController->AddAnimation(animations["LandRight"].get<Animation>());
	//m_animController->AddAnimation(animations["TurnRight"].get<Animation>());


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
	//std::cout << Phealth << std::endl;
	auto& animController = ECS::GetComponent<AnimationController>(3);

	//Jump Logic
	if (m_isJumping && animController.GetAnimation(4).GetAnimationDone()) {
		animController.GetAnimation(4).Reset();
		m_isJumping = false;
	}

	if (m_isJumping && animController.GetAnimation(10).GetAnimationDone()) {
		animController.GetAnimation(10).Reset();
		m_isJumping = false;
	}
	
	/*BossEnemy dmgTemp;
	Phealth = Phealth - dmgTemp.BossAttack();*/

	if (!m_locked)
	{
		MovementUpdate();
	}
	//Attack Logic\\

	//Slice Animation


	else if (animController.GetAnimation(2).GetAnimationDone()) {
		animController.GetAnimation(2).Reset();
		m_locked = false;
			}

	else if (animController.GetAnimation(8).GetAnimationDone()) {
		animController.GetAnimation(8).Reset();
		m_locked = false;
			}


	//Kick Logic
	else if (animController.GetAnimation(3).GetAnimationDone()) {
		animController.GetAnimation(3).Reset();
		m_locked = false;
	}
	else if (animController.GetAnimation(9).GetAnimationDone()) {
		animController.GetAnimation(9).Reset();
		m_locked = false;
			}

	//AnimationUpdate();
}
	

void Player::MovementUpdate()
{
	auto& animController = ECS::GetComponent<AnimationController>(3);
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
	b2Vec2 vel = b2Vec2(0.f, 0.f);
	//std::cout << std::boolalpha << canJump.m_canJump << "\n";
	//std::cout << player.GetBody()->GetLinearVelocity().y<<"   ";
	std::cout << spotJumped <<" " << std::boolalpha << dashCorrection<<"\n" ;

	

	// @Ryan i commented out ur true/false cout just uncomment to get them back

	//std::cout << " available: " << std::boolalpha << impactAvailable << " Y: " << impactY << " X: " << impactX << "\n";

	//jump function
	if (canJump.m_canJump == true)
	{
		if (impactAvailable == true) {
			impactX = xdiff;
			impactY = jumpGrav;
			impactAvailable = false;
		}
		
		if (Input::GetKeyDown(Key::Space))
		{
			spotJumped = player.GetPosition().x;
			xdiff = player.GetBody()->GetLinearVelocity().x;
			jumpGrav = 5;
			canJump.m_canJump = false;
			impactAvailable = true;
		}
	}
	else if (canJump.m_canJump == false) {

		jumpGrav -= 0.15f;
		if (Input::GetKey(Key::A))
		{
			m_facingRight = false;
			if (xdiff > -101) {
				xdiff -= 20;
			}
		}
		if (Input::GetKey(Key::D))
		{
			m_facingRight = true;
			if (xdiff < 101) {
				xdiff += 20;
			}
		}
		if (player.GetBody()->GetLinearVelocity().x!=0) {
			player.SetPosition(b2Vec2(player.GetPosition().x + (xdiff / 50), player.GetPosition().y + jumpGrav), true);
		}
		else if (player.GetBody()->GetLinearVelocity().x == 0) {
			player.SetPosition(b2Vec2(player.GetPosition().x  , player.GetPosition().y + jumpGrav), true);
		}
		player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 1.f), true);

	}


	//dash function 
	if (dash == true) {
		if (canJump.m_canJump == true) {

			player.GetBody()->SetLinearVelocity(b2Vec2(XvelDir * XvelDash * 150, 0.f));
		}
		else if (canJump.m_canJump == false) {
			player.SetPosition(b2Vec2(player.GetPosition().x + XvelDir * XvelDash, player.GetPosition().y), true);
			if (dashCorrection == true) {
				std::cout << "detected correction";
				player.SetPosition(b2Vec2(player.GetPosition().x -  XvelDir * XvelDash, player.GetPosition().y), true);
				dashCorrection = false;
			}
		}
		XvelDash--;
		if (XvelDash <= 0) {
			if (canJump.m_canJump == true) {
				player.SetPosition(b2Vec2(player.GetPosition().x + player.GetBody()->GetLinearVelocity().x / 50, player.GetPosition().y + 3), true);
			}
			dash = false;
			canJump.m_canJump = false;
			jumpGrav = 0;
			dashCooldown = 50;
		}
	}
	else if (dash == false) {
		if (dashCooldown > 0) {
			dashCooldown--;
		}
		else if (dashCooldown == 0) {
			if (Input::GetKey(Key::Shift)) {
				dash = true;
				XvelDash = 15;
				if ((spotJumped - (player.GetPosition().x) > -0.1) && (spotJumped - (player.GetPosition().x) <0.1)) {
					dashCorrection = true;
				}
				if (player.GetBody()->GetLinearVelocity().x < -0.2) {
					XvelDir = -1;
				}
				else if (player.GetBody()->GetLinearVelocity().x > 0.2) {
					XvelDir = 1;
				}
				else if ((player.GetBody()->GetLinearVelocity().x <0.199)&& (player.GetBody()->GetLinearVelocity().x > -0.199)) {
					if (m_facingRight == true)
					{
						XvelDir = 1;
					}
					else if (m_facingRight == false) {
						XvelDir = -1;
					}
				}
			}
		}
	}
		//Animation Code\\

		if (!m_isJumping) {
			if (Input::GetKey(Key::Space)) {

				if (m_facingRight) {
					animController.SetActiveAnim(4);
				}
				else {
					animController.SetActiveAnim(10);
				}
				m_isJumping = true;
			}
			/*else if (contact with ground) {
				animController.SetActiveAnim(5);
				m_locked = true;
			}*/
			else if (Input::GetKey(Key::O)) {

				if (m_facingRight) {
					animController.SetActiveAnim(2);
				}
				else {
					animController.SetActiveAnim(8);
				}
				m_locked = true;
			}
			else if (Input::GetKey(Key::I)) {
				if (m_facingRight) {
					animController.SetActiveAnim(3);
				}
				else {
					animController.SetActiveAnim(9);
				}
				m_locked = true;
			}
			else if (Input::GetKey(Key::A)) {
				animController.SetActiveAnim(7);
				m_facingRight = false;
			}
			else if (Input::GetKey(Key::D)) {
				animController.SetActiveAnim(1);
				m_facingRight = true;
			}
			else {
				if (m_facingRight) {
					animController.SetActiveAnim(0);
				}
				else {
					animController.SetActiveAnim(6);
				}
			}
		}
		//

		if (Input::GetKey(Key::A))
		{

			if (player.GetBody()->GetLinearVelocity().x > -100.f) {
				vel = b2Vec2(-1250000.f, 1.f);
			}
			player.GetBody()->ApplyForceToCenter(b2Vec2(vel), true);
		}
		if (Input::GetKey(Key::D))
		{
			m_moving = true;
			if (player.GetBody()->GetLinearVelocity().x < 100.f) {
				vel = b2Vec2(1250000.f, 1.f);
			}
			player.GetBody()->ApplyForceToCenter(b2Vec2(vel), true);

		}

		if (Input::GetKeyDown(Key::T))
		{
			PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
		}
		
	
}

float Player::PlayerAttack(COORD Position)
{
	if (Input::GetKeyDown(Key::O))
	{ 
			if ((Position.X < 70.0) && (Position.X > 0.0)) {
				return Pdamage;
			}
			else if (Position.X > 70.0) {
				return 0;
			}
			if ((Position.X > -70.0) && (Position.X < 0.0)) {
				return Pdamage;
			}
			else if (Position.X < -70.0) {
				return 0;
			}
	}

	if (Input::GetKeyDown(Key::I))
	{	
		if ((Position.X < 70.0) && (Position.X > 0.0)) {
			return Pdamage;
		}
		else if (Position.X > 70.0) {
			return 0;
		}
		if ((Position.X > -70.0) && (Position.X < 0.0)) {
			return Pdamage;
		}
		else if (Position.X < -70.0) {
			return 0;
		}
	}
}


void Player::AnimationUpdate()
{
	/*int activeAnimation = 0;

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

	SetActiveAnimation(activeAnimation + (int)m_facing);*/
}

void Player::SetActiveAnimation(int anim)
{
	m_animController->SetActiveAnim(anim);
}
void Player::AttachBody(PhysicsBody* body) {
	m_physBody = body;
}


