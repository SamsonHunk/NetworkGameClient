#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "Input.h"
#include "Global.h"

class GameObj
{
public:
	GameObj(b2World* worldIn, sf::Texture* sprite, Input* in, sf::RenderWindow* windowIn);
	~GameObj();

	void physicsUpdate(); //universal function to update the objects's sprite with it's physics body
	void deleteThis(); //when iterating through a container to delete something, set this to true
	bool getDelete();
	void render() { renderTarget->draw(objectSprite); };
	b2Body* getPhysicsBody();
	//render the object
	//virtual functions for the object
	virtual void update(float dt) = 0;
	virtual void init() = 0;

protected:
	b2World* physicsWorld;
	sf::RenderWindow* renderTarget;
	bool needsDestroyed = false;
	sf::Sprite objectSprite;
	b2Body* physicsBody;
	Input* inputManager;
};
