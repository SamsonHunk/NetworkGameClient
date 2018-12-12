#include "Player2.h"

void Player2::update(float dt)
{
	//first determine if we have updated server info
	if (input.newInfo)
	{//if yes update the object variables with the server info
		//physicsBody->SetTransform(b2Vec2(input.pos[0], input.pos[1]), 0);
		serverPos = b2Vec2(input.pos[0], input.pos[1]);
		rubberBandSpeed = b2Distance(physicsBody->GetPosition(), serverPos) / 10;
		physicsBody->SetLinearDamping(1 / rubberBandSpeed);
		physicsBody->SetTransform(b2Vec2(input.pos[0], physicsBody->GetPosition().y), 0);
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
		
			break;
		case PlayerStates::movingUp:
			physicsBody->SetLinearVelocity(b2Vec2(currentVelocity.x, input.yVel));
			break;
		case PlayerStates::movingDown:
			break;
		default:
			currentState = PlayerStates::stationary;
			break;
		}
	
		

		
		

		/*
		if (xDistance != 0)
		{
			//now we know what direction we are going in, interpolate a bit to the latest server position
			physicsBody->ApplyLinearImpulseToCenter(b2Vec2(0, yDistance * rubberBandSpeed), true);
		}
		*/
	}

	b2Vec2 currentPos = physicsBody->GetPosition();
	float yDistance = serverPos.y - currentPos.y;
	float xDistance = serverPos.x - currentPos.y;
	//rubber band movement smoothing on both the x and y axis
	if (yDistance != 0)
	{
		//now we know what direction we are going in, interpolate a bit to the latest server position
		physicsBody->ApplyLinearImpulseToCenter(b2Vec2(0, yDistance * rubberBandSpeed), true);
	}
	if (yDistance > 700)
	{
		physicsBody->SetTransform(b2Vec2(currentPos.x, serverPos.y), 0);
	}

	physicsUpdate();

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