#include "GameObj.h"

GameObj::GameObj(b2World* worldIn, sf::Texture* sprite, Input* in, sf::RenderWindow* windowIn)
{//setup object's pointers and sprite stuff
	objectSprite.setTexture(*sprite);
	physicsWorld = worldIn;
	inputManager = in;
	renderTarget = windowIn;
}

GameObj::~GameObj()
{
}

void GameObj::physicsUpdate()
{//update sprite with it's physics body position
	objectSprite.setPosition(sf::Vector2f(physicsBody->GetPosition().x, physicsBody->GetPosition().y));
	objectSprite.setRotation(physicsBody->GetTransform().q.GetAngle());
}

void GameObj::deleteThis()
{
	needsDestroyed = true;
}

bool GameObj::getDelete()
{
	return needsDestroyed;
}

b2Body * GameObj::getPhysicsBody()
{
	return physicsBody;
}
