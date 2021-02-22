#include "PhysicsBody.h"
#include "ECS.h"

bool PhysicsBody::m_drawBodies = false;
std::vector<int> PhysicsBody::m_bodiesToDelete;

PhysicsBody::PhysicsBody(int entity, b2Body * body, float radius, vec2 centerOffset, bool sensor, EntityCategories category, int collidesWith, float friction, float density)
{
	//Bodies don't reference a shape by themselves
	//they need a shape that has been linked to a fixture
	//in order to have a shape
	b2CircleShape tempShape;
	tempShape.m_p = b2Vec2(float32(centerOffset.x), float32(centerOffset.y));
	tempShape.m_radius = radius;

	//Creates the actual fixture (aka, shape, mass, etc);
	b2FixtureDef tempFixture;
	tempFixture.shape = &tempShape;
	tempFixture.density = density;
	tempFixture.friction = friction;
	tempFixture.isSensor = sensor;
	tempFixture.filter.categoryBits = category;
	tempFixture.filter.maskBits = collidesWith;


	m_body = body;
	m_body->CreateFixture(&tempFixture);

	m_body->SetUserData((void*)entity);

	m_body = body;
	m_bodyType = BodyType::CIRCLE;

	//Stores the position;
	m_position = m_body->GetPosition();

	m_width = radius * 2.f;
	m_height = radius * 2.f;

	m_centerOffset = centerOffset;
}

PhysicsBody::PhysicsBody(int entity, b2Body* body, float width, float height, vec2 centerOffset, bool sensor, EntityCategories category, int collidesWith, float friction, float density)
{
	//Bodies don't reference a shape by themselves
	//they need a shape that has been linked to a fixture
	//in order to have a shape
	b2PolygonShape tempShape;
	tempShape.SetAsBox(float32(width / 2.f), float32(height / 2.f),
		b2Vec2(float32(centerOffset.x), float32(centerOffset.y)), float32(0.f));

	//Creates the actual fixture (aka, shape, mass, etc);
	b2FixtureDef tempFixture;
	tempFixture.shape = &tempShape;
	tempFixture.density = density;
	tempFixture.friction = friction;
	tempFixture.isSensor = sensor;
	tempFixture.filter.categoryBits = category;
	tempFixture.filter.maskBits = collidesWith;

	m_body = body;
	m_body->CreateFixture(&tempFixture);

	m_body->SetUserData((void*)entity);

	m_body = body;
	m_bodyType = BodyType::BOX;

	m_width = width;
	m_height = height;

	m_centerOffset = centerOffset;
}

PhysicsBody::PhysicsBody(int entity, BodyType bodyType, b2Body* body, std::vector<b2Vec2> points, vec2 centerOffset, bool sensor, EntityCategories category, int collidesWith, float friction, float density)
{
	//Used to calculate new width and height
	float lX = 999.f;
	float rX = -999.f;
	float bY = 999.f;
	float tY = -999.f;

	//Bodies don't reference a shape by themselves
	//they need a shape that has been linked to a fixture
	//in order to have a shape
	int count = points.size();
	b2Vec2 polyPoints[8];

	if (points.size() <= 8)
	{
		for (int i = 0; i < points.size(); i++)
		{
			polyPoints[i] = points[i];

			//Used to calculate width and height values
			lX = std::min(lX, points[i].x);
			rX = std::max(rX, points[i].x);
			bY = std::min(bY, points[i].y);
			tY = std::max(tY, points[i].y);
		}
	}

	b2PolygonShape tempShape;
	tempShape.Set(polyPoints, count);
	tempShape.m_centroid = b2Vec2(centerOffset.x, centerOffset.y);

	//Creates the actual fixture (aka, shape, mass, etc);
	b2FixtureDef tempFixture;
	tempFixture.shape = &tempShape;
	tempFixture.density = density;
	tempFixture.friction = friction;
	tempFixture.isSensor = sensor;
	tempFixture.filter.categoryBits = category;
	tempFixture.filter.maskBits = collidesWith;

	m_body = body;
	m_body->CreateFixture(&tempFixture);

	m_body->SetUserData((void*)entity);

	m_body = body;
	m_bodyType = bodyType;

	m_width = rX - lX;
	m_height = tY - bY;

	m_centerOffset = centerOffset;
}

void PhysicsBody::DeleteBody()
{
	if (m_body != nullptr)
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}
}

void PhysicsBody::Update(Transform * trans)
{
	//Make sure that movement doesn't happen in contact step
	if (moveLater)
	{
		//set position with saved move value
		SetPosition(moveValue);
		moveLater = false;
	}
	if (rotateLater)
	{
		SetRotationAngleDeg(rotationDeg);
		rotateLater = false;
	}
	if (scaleLater)
	{
 		ScaleBody(scaleVal, scaleFixt);
		scaleLater = false;
	}

	//Stores the position;
	m_position = m_body->GetPosition();

	//Sets the transform position to the position of the physics body
	trans->SetPosition(vec3(m_body->GetPosition().x, m_body->GetPosition().y, trans->GetPosition().z));
	trans->SetRotationAngleZ(Degrees(m_body->GetAngle()));
}

void PhysicsBody::ApplyForce(vec3 force)
{
	m_body->ApplyForce(b2Vec2(float32(force.x), float32(force.y)),
						b2Vec2(float32(m_body->GetPosition().x), float32(m_body->GetPosition().y)),
						 true);
}


b2Body * PhysicsBody::GetBody() const
{
	return m_body;
}

BodyType PhysicsBody::GetBodyType() const
{
	//What kinda physics body is this?
	return m_bodyType;
}


float PhysicsBody::GetMass() const
{
	b2MassData massData;
	m_body->GetMassData(&massData);
	return massData.mass;
}

b2Vec2 PhysicsBody::GetPosition() const
{
	return m_position;
}

vec3 PhysicsBody::GetVelocity() const
{
	//Returns current velocity
	b2Vec2 vel = m_body->GetLinearVelocity();
	vec3 temp = vec3(vel.x, vel.y, 0.f);
	
	return temp;
}

float PhysicsBody::GetGravityScale() const
{
	return m_body->GetGravityScale();
}

vec4 PhysicsBody::GetColor() const
{
	return m_color;
}


vec2 PhysicsBody::GetCenterOffset() const
{
	//return offset from the center of the sprite
	return m_centerOffset;
}



float PhysicsBody::GetWidth() const
{
	//return body width
	return m_width;
}

float PhysicsBody::GetHeight() const
{
	//return body height
	return m_height;
}

float PhysicsBody::GetRadius(int fixture) const
{
	return m_body->GetFixtureList()[fixture].GetShape()->m_radius;
}


float PhysicsBody::GetRotationAngleDeg() const
{
	return Transform::ToDegrees(m_body->GetAngle());
}

bool PhysicsBody::GetFixedRotation() const
{
	return m_fixedRotation;
}


bool PhysicsBody::GetDraw()
{
	return m_drawBodies;
}



void PhysicsBody::SetBody(b2Body * body)
{
	m_body = body;
}

void PhysicsBody::SetBodyType(BodyType type)
{
	//Set the type of body this is
	m_bodyType = type;
}


void PhysicsBody::SetPosition(b2Vec2 bodyPos, bool contactStep)
{
	if (!contactStep)
	{
		//Body transform
		m_body->SetTransform(bodyPos, m_body->GetAngle());
	}
	else
	{
		moveLater = true;
		moveValue = bodyPos;
	}
}

void PhysicsBody::SetVelocity(vec3 velo)
{
	b2Vec2 vel = b2Vec2(velo.x, velo.y);

	m_body->SetLinearVelocity(vel);
}

void PhysicsBody::SetGravityScale(float gravSc)
{
	m_body->SetGravityScale(gravSc);
}

void PhysicsBody::SetColor(vec4 col)
{
	m_color = col;
}

void PhysicsBody::SetMass(float mass)
{
	b2MassData massData;
	m_body->GetMassData(&massData);
	massData.mass = mass;

	m_body->SetMassData(&massData);
}

void PhysicsBody::SetCenterOffset(vec2 cent)
{
	//Set the center offset
	m_centerOffset = cent;
}



void PhysicsBody::ScaleBody(float scale, int fixture, bool contactStep)
{
	if (!contactStep)
	{
		if (m_bodyType == BodyType::CIRCLE)
		{
			float scaledRadius = (m_width / 2.f) * scale;

			m_width += scaledRadius;
			m_height += scaledRadius;
			m_body->GetFixtureList()[fixture].GetShape()->m_radius = m_width / 2.f;
			m_body->SetAwake(true);
		}
		else
		{
			//Used to calculate new width and height
			float lX = 999.f;
			float rX = -999.f;
			float bY = 999.f;
			float tY = -999.f;

			//Gets the shape value and casts as b2PolygonShape so we can access the vertices
			b2PolygonShape* bodyShape = (b2PolygonShape*)m_body->GetFixtureList()[fixture].GetShape();

			//Center of the polygon
			b2Vec2 center = bodyShape->m_centroid;

			//loops through every vertice
			for (int i = 0; i < bodyShape->m_count; i++)
			{
				//Create normalized direction
				b2Vec2 vert = bodyShape->m_vertices[i];
				lX = std::min(lX, vert.x);
				rX = std::max(rX, vert.x);
				bY = std::min(bY, vert.y);
				tY = std::max(tY, vert.y);

				b2Vec2 dir = (vert - center);
				dir.Normalize();

				//Moves the vert out by a scaled direction vector
				bodyShape->m_vertices[i] += scale * dir;
			}

			m_width = rX - lX;
			m_height = tY - bY;
			m_body->SetAwake(true);
		}
		
		int ent = (int)m_body->GetUserData();

		auto tempSpr = ECS::m_reg->try_get<Sprite>(ent);
		if (tempSpr != nullptr)
		{
			tempSpr->SetWidth(m_width);
			tempSpr->SetHeight(m_height);
		}
	}
	else
	{
		scaleLater = true;
		scaleFixt = fixture;
		scaleVal = scale;
	}
}

void PhysicsBody::SetRotationAngleDeg(float degrees, bool contactStep)
{
	if (!contactStep)
	{
		//Set the rotation angle
		m_body->SetTransform(m_body->GetPosition(), Transform::ToRadians(degrees));
	}
	else
	{
		rotateLater = true;
		rotationDeg = degrees;
	}
}

void PhysicsBody::SetFixedRotation(bool fixed)
{
	m_body->SetFixedRotation(fixed);

	m_fixedRotation = fixed;
}

void PhysicsBody::SetCategoryBit(EntityCategories category, int fixture)
{
	b2Filter filter = m_body->GetFixtureList()[fixture].GetFilterData();

	filter.categoryBits = category;

	m_body->GetFixtureList()[fixture].SetFilterData(filter);
}

void PhysicsBody::SetCollisionBit(EntityCategories collision, int fixture)
{
	b2Filter filter = m_body->GetFixtureList()[fixture].GetFilterData();

	filter.maskBits = collision;

	m_body->GetFixtureList()[fixture].SetFilterData(filter);
}

void PhysicsBody::SetDraw(bool drawBodies)
{
	m_drawBodies = drawBodies;
}

