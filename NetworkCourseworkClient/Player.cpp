#include "Player.h"

void Player::update(float dt)
{
	physicsUpdate();

	//player control

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
	
	if (inputManager->getKey(jumpControl))
	{
		currentState = PlayerStates::movingUp;
		inputManager->KeyUp(jumpControl);
	}

	if (inputManager->getKey(shootControl))
	{
		inputManager->KeyUp(shootControl);
		isShooting = true;
	}
	else
	{
		isShooting = false;
	}

	b2Vec2 currentVelocity = physicsBody->GetLinearVelocity();
	switch (currentState)
	{
	case PlayerStates::movingLeft:
		physicsBody->SetLinearVelocity(b2Vec2(-speed, currentVelocity.y));
		left = false;
		break;
	case PlayerStates::movingRight:
		physicsBody->SetLinearVelocity(b2Vec2(speed, currentVelocity.y));
		left = true;
		break;
	case PlayerStates::stationary:
		physicsBody->SetLinearVelocity(b2Vec2(0, currentVelocity.y));
		break;
	case PlayerStates::movingUp:
		if (!inAir)
		{
			physicsBody->SetLinearVelocity(b2Vec2(currentVelocity.x, -14));
			inAir = true;
		}
		break;
	default:
		break;
	}

	collisionHandle();
}

void Player::init(float x, float y)
{
	objectSprite.setColor(sf::Color::Blue);

	//setup player physics body
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
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
	physicsBody->SetFixedRotation(true);
}


PlayerStates Player::getState()
{
	return currentState;
}

void Player::collisionHandle()
{

}
