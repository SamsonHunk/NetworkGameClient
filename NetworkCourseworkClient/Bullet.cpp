#include "Bullet.h"

void Bullet::update(float dt)
{

}

void Bullet::init(float x, float y)
{
	//initialise physics body
	b2BodyDef bulletBodyDef;
	bulletBodyDef.type = b2_kinematicBody;
	bulletBodyDef.position = b2Vec2(x, y);
	physicsBody = physicsWorld->CreateBody(&bulletBodyDef);

	//create shape
	b2PolygonShape bulletShape;
	bulletShape.SetAsBox(objectSprite.getLocalBounds().width / 2, objectSprite.getLocalBounds().height / 2);

	//setup fixture
	b2FixtureDef bulletFixture;
	bulletFixture.shape = &bulletShape;
	bulletFixture.density = 1.f;

	//attach shape
	physicsBody->CreateFixture(&bulletFixture);
	physicsBody->SetUserData(this);

	if (dir)
	{
		physicsBody->SetLinearVelocity(b2Vec2(-speed, 0));
	}
	else
	{
		physicsBody->SetLinearVelocity(b2Vec2(speed, 0));
	}
}

void Bullet::serverAssert(float x, float y)
{//if we get information from the server update it, server takes precedence
	physicsBody->SetTransform(b2Vec2(x, y), 0);
}

ObjectType Bullet::getType()
{
	return ObjectType::BULLET;
}