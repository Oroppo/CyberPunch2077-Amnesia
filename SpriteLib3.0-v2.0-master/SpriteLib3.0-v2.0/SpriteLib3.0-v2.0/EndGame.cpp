#include "EndGame.h"
#include "Utilities.h"
#include "Player.h"
#include <random>

EndGame::EndGame(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(0.f, 0.f);
	m_physicsWorld->SetGravity(m_gravity);
}

int EndGame::GetSceneChange() {
	return m_SceneIndex;
}

void EndGame::SetSceneChange(int a) {
	m_SceneIndex = a;
}

void EndGame::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;
	m_physicsWorld = new b2World(m_gravity);

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;


	//Setup MainCamera Entity
	{
		/*Scene::CreateCamera(m_sceneReg, vec4(-75.f, 75.f, -75.f, 75.f), -100.f, 100.f, windowWidth, windowHeight, true, true);*/

		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = vec4(-120.f, 120.f, -120.f, 120.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attaches the camera to vert and horiz scrolls
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}

	//Main Player entity

	{
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "GameOver.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 450, 250);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 1.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(0.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | OBJECTS | HEXAGON);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempSpr.SetTransparency(1.f);
	}

	/*{
		//loading File... 
		auto animations = File::LoadJSON("Victory!.json");

		auto entity = ECS::CreateEntity();

		//Add components 
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<AnimationController>(entity);


		//Sets up the components 
		std::string fileName = "spritesheets/Defeat.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);

		animController.InitUVs(fileName);
		animController.AddAnimation(animations["Basic"]);	//0 
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 420, 270, true, &animController);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 10.f));


		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;

		tempDef.position.Set(float32(0.f), float32(0.f));
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		// square phys body 
		tempPhsBody = PhysicsBody(entity, tempBody, float(30 - shrinkX), float(50 - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | GROUND | OBJECTS | PICKUP | TRIGGER, 2.f, 3.f);

		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetFixedRotation(true);
		//tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f)); 
		tempPhsBody.SetGravityScale(0.f);
	}*/
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void EndGame::Update()
{
	MenuUpdate();

	if (Input::GetKeyDown(Key::Enter))
	{
		SetSceneChange(0);
	}
	if (Input::GetKeyDown(Key::Escape))
	{
		SetSceneChange(0);
	}



}

void EndGame::MenuUpdate() {




}