#include "PhysicsSystem.h"

Shader physicsDrawShader;

bool m_debugPlaneInit = false;

GLuint m_debugPlaneVAO = GL_NONE;
GLuint m_debugPlaneUVVBO = GL_NONE;
static GLuint m_debugPlaneVBO;

std::vector<std::string> m_bodyTypeMasks;

void PhysicsSystem::Init()
{
	physicsDrawShader.Load("./assets/shader/StaticGeometry.vert", "./assets/shader/PhysicsColorDraw.frag");
	 
	if (!m_debugPlaneInit)
	{
		m_debugPlaneVBO = VertexManager::GetPlaneVertVBO();
		m_debugPlaneUVVBO = VertexManager::GetPlaneUVVBO();

		InitDebugDrawPlaneVAO();
		m_debugPlaneInit = true;
	}
	
	m_bodyTypeMasks.push_back("SquareMask.png");
	m_bodyTypeMasks.push_back("CircleMask.png");
	m_bodyTypeMasks.push_back("TriangleMask.png");
	m_bodyTypeMasks.push_back("HexagonMask.png");
}

void PhysicsSystem::InitDebugDrawPlaneVAO()
{
	//Creates a new VAO (able to be unloaded upon program termination)
	m_debugPlaneVAO = VertexManager::CreateVAO();
	glBindVertexArray(m_debugPlaneVAO);

	//Enables slot 0 and 1
	glEnableVertexAttribArray(0); //vertices
	glEnableVertexAttribArray(1); //UV coordinates

	//Pushes away the warnings
#pragma warning(push)
#pragma warning(disable : 4312)
	//Bind Vert VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_debugPlaneVBO);
	//Sets the vertex attributes
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
	//Bind UV VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_debugPlaneUVVBO);
	//Sets the uv attributes
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
#pragma warning(pop)

	//Unbinds the buffers
	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
}

void PhysicsSystem::Update(entt::registry * reg, b2World & world)
{
	auto view = reg->view<PhysicsBody, Transform>();

	//Runs the update for the physics bodies
	for (auto entity : view)
	{
		//Grabs references to each component within view
		auto& physBod = view.get<PhysicsBody>(entity);
		auto& trans = view.get<Transform>(entity);

		//Updates physics body
		physBod.Update(&trans);
	}

	//Runs the various things
	//(currently just checking collisions)
	Run(world);
}

void PhysicsSystem::Draw(entt::registry * reg)
{
	auto view = reg->view<PhysicsBody, Transform>();
	auto& cam = reg->get<Camera>(MainEntities::MainCamera());

	if (PhysicsBody::GetDraw())
	{
		for (auto entity : view)
		{
			auto& physBody = view.get<PhysicsBody>(entity);
			auto& trans = view.get<Transform>(entity);

			//Temporary transform so we can actually draw the bodies
			Transform temp = trans;
			temp.SetScale(vec3(physBody.GetWidth(), physBody.GetHeight(), 1.f));
			//Sets the position so the center offset is still relevant
			temp.SetPosition(temp.GetPosition() + vec3(physBody.GetCenterOffset().x, physBody.GetCenterOffset().y, 0.f));
			//Puts the temporary transform for the physics body at the top z-layer
			temp.SetPositionZ(100.f);

			//Updates the transform to create model matrix
			temp.Update();

			std::string fileName = "Masks/";

			for (int i = 0; i < (int)BodyType::NUM_TYPES; i++)
			{
				if (physBody.GetBodyType() == (BodyType)i)
				{
					fileName += m_bodyTypeMasks[i];
				}
			}
			
			Texture* mask = TextureManager::FindTexture(fileName);

			//Binds the draw shader
			physicsDrawShader.Bind();

			//Sends the uniforms we need for drawing the bodies
			physicsDrawShader.SendUniform("uView", cam.GetView());
			physicsDrawShader.SendUniform("uProj", cam.GetProjection());
			physicsDrawShader.SendUniform("uModel", temp.GetLocalToWorldMatrix());
			physicsDrawShader.SendUniform("uColor", physBody.GetColor());

			mask->Bind(0);

			//Draws the body
			 //Bind vertex array
			glBindVertexArray(m_debugPlaneVAO);
			//Draw the array
			glDrawArrays(GL_TRIANGLES, 0, 6);
			//unbind vertex array
			glBindVertexArray(GL_NONE);

			mask->Unbind();

			//Unbinds the shader
			physicsDrawShader.Unbind();
		}
	}
}

void PhysicsSystem::Run(b2World & world)
{
	//Timestep is constant, regardless of deltatime
	float32 timeStep = 1.f / 60.f;

	//Box2D uses an algorithm called an integrator,
	//this simulates the physics algorithms at discrete points in time
	//we need to give it iterations for the velocity and position, along with
	//our timestep
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	//steps through the world
	world.Step(timeStep, velocityIterations, positionIterations);

	CleanupBodies();
}

void PhysicsSystem::CleanupBodies()
{
	for (int i = 0; i < PhysicsBody::m_bodiesToDelete.size(); i++)
	{
		//Bodies to delete
		ECS::GetComponent<PhysicsBody>(PhysicsBody::m_bodiesToDelete[i]).DeleteBody();

		//Destroy the entity
		ECS::DestroyEntity(PhysicsBody::m_bodiesToDelete[i]);
	}

	//Clear bodies to delete
	PhysicsBody::m_bodiesToDelete.clear();
}
