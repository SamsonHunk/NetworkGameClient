#include "Player.h"

void Player::update(float dt)
{
	physicsUpdate();
	if (inputManager->getKey(leftControl))
	{
		physicsBody->SetLinearVelocity(b2Vec2(-speed * dt, 0));
	}

	if (inputManager->getKey(rightControl))
	{
		physicsBody->SetLinearVelocity(b2Vec2(speed * dt, 0));
	}
}

void Player::init()
{
	objectSprite.setColor(sf::Color::Red);

	//setup player physics body
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position = b2Vec2(0, 0);
	physicsBody = physicsWorld->CreateBody(&playerBodyDef);

	//setup the shape of the player
	b2PolygonShape playerShape;
	playerShape.SetAsBox(.5, 1);

	//setup the player fixture
	b2FixtureDef playerFixture;
	playerFixture.shape = &playerShape;
	playerFixture.density = 1.f;

	//attach the shape to the physicsbody
	physicsBody->CreateFixture(&playerFixture);
	physicsBody->SetUserData(this);
}
