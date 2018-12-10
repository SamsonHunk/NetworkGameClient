#include "Player2.h"

void Player2::update(float dt)
{
	physicsUpdate();
	//first determine if we have updated server info
	if (input.newInfo)
	{//if yes update the object variables with the server info
		physicsBody->SetTransform(b2Vec2(input.pos[0], input.pos[1]), 0);
		currentState = input.newState;
		input.newInfo = false;
	}
	else
	{//else we start some predicting
		b2Vec2 currentVelocity = physicsBody->GetLinearVelocity();

		switch (currentState)
		{
		case PlayerStates::movingLeft: //if they were moving left, they continue
			physicsBody->SetLinearVelocity(b2Vec2(-speed, currentVelocity.y));
			break;
		case PlayerStates::movingRight: //ditto
			physicsBody->SetLinearVelocity(b2Vec2(speed, currentVelocity.y));
			break;
		case PlayerStates::stationary: //if they were standing still and not in the air make them not move
			if (!inAir)
			{
				physicsBody->SetLinearVelocity(b2Vec2(0, currentVelocity.y));
			}
			break;
		case PlayerStates::movingUp:
			break;
		case PlayerStates::movingDown:
			break;
		default:
			currentState = PlayerStates::stationary;
			break;
		}
		
	}
}

void Player2::init(float x, float y)
{
	objectSprite.setColor(sf::Color::Red);

	//setup player physics body
	b2BodyDef playerBodyDef;
	playerBodyDef.type = playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position = b2Vec2(x, y);
	physicsBody = physicsWorld->CreateBody(&playerBodyDef);

	//setup the shape of the player
	b2PolygonShape playerShape;
	playerShape.SetAsBox(objectSprite.getLocalBounds().width / 2, objectSprite.getLocalBounds().height / 2);

	//setup the player fixture
	b2FixtureDef playerFixture;
	playerFixture.shape = &playerShape;
	playerFixture.density = 1.f;

	//attach the shape to the physicsbody
	physicsBody->CreateFixture(&playerFixture);
	physicsBody->SetUserData(this);

	input.dir = false;
	input.newInfo = true;
	input.newState = PlayerStates::stationary;
	input.pos[0] = 100;
	input.pos[1] = 0;
	physicsBody->SetLinearVelocity(b2Vec2(0, 0));
	physicsBody->SetFixedRotation(true);
}

PlayerStates Player2::getState()
{
	return currentState;
}