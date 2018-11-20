#include "Player.h"

void Player::update(float dt)
{
	physicsUpdate();

	if (inputManager->getKey(leftControl))
	{
		currentState = PlayerStates::movingLeft;
	}
	else if (inputManager->getKey(rightControl))
	{
		currentState = PlayerStates::movingRight;
	}
	else
	{
		currentState = PlayerStates::stationary;
	}
	
	b2Vec2 currentVelocity = physicsBody->GetLinearVelocity();
	switch (currentState)
	{
	case PlayerStates::movingLeft:
		physicsBody->SetLinearVelocity(b2Vec2(-speed, currentVelocity.y));
		break;
	case PlayerStates::movingRight:
		physicsBody->SetLinearVelocity(b2Vec2(speed, currentVelocity.y));
		break;
	case PlayerStates::stationary:
		physicsBody->SetLinearVelocity(b2Vec2(0, currentVelocity.y));
		break;
	default:
		break;
	}
}

void Player::init()
{
	objectSprite.setColor(sf::Color::Red);

	//setup player physics body
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position = b2Vec2(600, 0);
	physicsBody = physicsWorld->CreateBody(&playerBodyDef);

	//setup the shape of the player
	b2PolygonShape playerShape;
	playerShape.SetAsBox(64, 80);

	//setup the player fixture
	b2FixtureDef playerFixture;
	playerFixture.shape = &playerShape;
	playerFixture.density = 1.f;

	//attach the shape to the physicsbody
	physicsBody->CreateFixture(&playerFixture);
	physicsBody->SetUserData(this);
}

PlayerStates Player::getState()
{
	return currentState;
}
