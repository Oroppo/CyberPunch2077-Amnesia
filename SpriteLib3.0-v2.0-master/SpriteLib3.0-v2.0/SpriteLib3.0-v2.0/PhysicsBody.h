#pragma once

#include <GL/glew.h>
#include <Box2D/Box2D.h>

#include "JSON.h"
#include "Vector.h"
#include "VertexManager.h"
#include "Transform.h"

enum class BodyType
{
	BOX,
	CIRCLE,
	TRIANGLE,
	HEXAGON,

	NUM_TYPES
};

enum EntityCategories
{
	ENVIRONMENT = 0x0001,
	GROUND		= 0x0002,
	OBJECTS		= 0x0004,
	PLAYER		= 0x0008,
	FRIENDLY	= 0x0016,
	ENEMY		= 0x0032,
	PICKUP		= 0x0064,
	TRIGGER		= 0x0128,
	HEXAGON		= 0x0256
};


class PhysicsBody
{
public:
	PhysicsBody() { };
	//Constructs a circle collider
	PhysicsBody(int entity, b2Body* body, float radius, vec2 centerOffset, bool sensor, EntityCategories category, int collidesWith, float friction=1.f, float density=1.f);
	//Constructs a box collider
	PhysicsBody(int entity, b2Body* body, float width, float height, vec2 centerOffset, bool sensor, EntityCategories category, int collidesWith, float friction=1.f, float density=1.f);
	//Constructs a polygon collider
	PhysicsBody(int entity, BodyType bodyType, b2Body* body, std::vector<b2Vec2> points, vec2 centerOffset, bool sensor, EntityCategories category, int collidesWith, float friction=1.f, float density=1.f);

	//Delete the physics body
	void DeleteBody();

	//Update physics stuffs
	void Update(Transform* trans);
	//Apply a force to the physics body
	void ApplyForce(vec3 force);


	//Getters//
	//Get the Box2D physics body
	b2Body* GetBody() const;
	//Get the body type enum
	BodyType GetBodyType() const;


	//Set the mass of the phyics body
	float GetMass() const;
	//Get position of body
	b2Vec2 GetPosition() const;
	//Gets the current velocity
	vec3 GetVelocity() const;
	//Gets the gravity scale of the physics body
	float GetGravityScale() const;
	//Gets the debug color
	vec4 GetColor() const;
	

	//Gets the width of the physics body
	float GetWidth() const;
	//Gets the height of the physics body
	float GetHeight() const;
	//Gets the radius of the physics body
	float GetRadius(int fixture) const;
	//Gets the center offset for the body
	//*if the offset is 0,0, then all corners will be relative to the
	//center of the actual sprite
	vec2 GetCenterOffset() const;

	//Get the rotation angle (radians) of the body
	float GetRotationAngleDeg() const;
	//Get whether the body has a fixed rotation
	bool GetFixedRotation() const;

	//Get whether or not we are currently drawing our physics bodies
	static bool GetDraw();


	//Setters//
	//Sets the pointer to the box2D body
	void SetBody(b2Body* body);
	//If other body types were ever implemented we could set it here 
	//(obviously different types wouldn't use the whole BL, BR, TL, TR
	void SetBodyType(BodyType type);


	//Set position
	void SetPosition(b2Vec2 bodyPos, bool contactStep = false);
	//Sets the velocity of the phyiscs body
	void SetVelocity(vec3 velo);
	//Sets the gravity scale of the physics body
	void SetGravityScale(float gravSc);
	//Set the color of the debug draw
	void SetColor(vec4 col);


	//Set the mass of the physics body
	void SetMass(float mass);

	//Set the scaled width
	void ScaleBody(float scale, int fixture, bool contactStep = false);
	//Sets the center offset for the body
	//*if the offset is 0,0, then all corners will be relative to the
	//center of the actual sprite	void SetCenterOffset(vec2 cent);
	void SetCenterOffset(vec2 cent);

	//Set the rotation angle
	void SetRotationAngleDeg(float degrees, bool contactStep=false);
	//Set whether the body has a fixed rotation
	void SetFixedRotation(bool fixed);

	void SetCategoryBit(EntityCategories category, int fixture=0);
	void SetCollisionBit(EntityCategories collision, int fixture=0);

	//Set whether the bodies are being drawn
	static void SetDraw(bool drawBodies);

	static std::vector<int> m_bodiesToDelete;
private:
	//The actual box2D body
	b2Body* m_body = nullptr;
	//Body type
	BodyType m_bodyType = BodyType::BOX;

	//Stagger the movement
	bool moveLater = false;
	b2Vec2 moveValue = b2Vec2(0.f, 0.f);
	//Stagger the rotation
	bool rotateLater = false;
	float rotationDeg = 0.f;
	//Stagger the scale
	bool scaleLater = false;
	int scaleFixt = 0;
	float scaleVal = 0.f;

	//Box2D position
	b2Vec2 m_position = b2Vec2(0.f, 0.f);
	//Color of the debug draw body
	vec4 m_color = vec4(1.f, 0.f, 0.f, 0.3f);

	bool m_fixedRotation = false;

	//How far from the center of the sprite is it
	vec2 m_centerOffset = vec2();
	//Width and height of the body
	float m_width = 0.f;
	float m_height = 0.f;
	

	//Do you draw the bodies?
	static bool m_drawBodies;
};