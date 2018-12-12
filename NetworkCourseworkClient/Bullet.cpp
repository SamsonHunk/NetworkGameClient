#include "Bullet.h"

void Bullet::update(float dt)
{
	physicsUpdate();
	if (physicsBody->GetPosition().x < -5 || physicsBody->GetPosition().x > 1000)
	{//if the bullet is out of bounds
		deactivate();
	}
	else
	{
		if (dir)
		{
			physicsBody->SetLinearVelocity(b2Vec2(speed, 0));
		}
		else
		{
			physicsBody->SetLinearVelocity(b2Vec2(-speed, 0));
		}
	}
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
	physicsBody->SetActive(false);
	awake = false;
}

void Bullet::serverAssert(float x, float y)
{//if we get information from the server update it, server takes precedence
	physicsBody->SetTransform(b2Vec2(x, y), 0);
}

ObjectType Bullet::getType()
{
	return ObjectType::BULLET;
}

void Bullet::activate(float x, float y, bool dirIn)
{//grab the bullet and send it on it's way
	awake = true;
	physicsBody->SetTransform(b2Vec2(x, y), 0);
	physicsBody->SetActive(true);
	dir = dirIn;
	newBullet = true;
}

void Bullet::deactivate()
{
	awake = false;
	physicsBody->SetTransform(b2Vec2(0, 0), 0);
	physicsBody->SetActive(false);
}

