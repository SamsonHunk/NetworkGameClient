#include "Floor.h"

void Floor::update(float dt)
{
	physicsUpdate();
}

void Floor::init(float x, float y)
{
	objectSprite.setScale(sf::Vector2f(2, 1));
	//setup floor physics body
	b2BodyDef floorBodyDef;
	floorBodyDef.type = b2_staticBody;
	floorBodyDef.position = b2Vec2(200, 400);
	physicsBody = physicsWorld->CreateBody(&floorBodyDef);

	//setup shape
	b2PolygonShape floorShape;
	floorShape.SetAsBox(objectSprite.getLocalBounds().width, objectSprite.getLocalBounds().height / 2);

	b2FixtureDef floorFixture;
	floorFixture.shape = &floorShape;

	//attach fixture
	physicsBody->CreateFixture(&floorFixture);
	physicsBody->SetUserData(this);
}