#pragma once
#include <engine.h>

struct AIMoveOut
{
	//Direction
	sf::Vector2f direction;
	//Rotation
	float rotation;
};

//Component for basic movement behaviour
class AIMovement{
public:
	virtual ~AIMovement() = default;

	virtual AIMoveOut getAiMove() const noexcept = 0;
};

//Seek
class Seek : public AIMovement {
private:
	Entity* _character;
	Entity* _target;
	float _maxSpeed;
public:
	Seek() = delete;
	Seek(Entity *character, Entity *target, float maxSpeed)
	: _character(character), _target(target), _maxSpeed(maxSpeed) {}
	AIMoveOut getAiMove() const noexcept;
};

//Flee
class Flee : public AIMovement {
private:
	Entity* _character;
	Entity* _target;
	float _maxSpeed;
public:
	Flee() = delete;
	Flee(Entity *character, Entity *target, float maxSpeed)
		: _character(character), _target(target), _maxSpeed(maxSpeed) {}
	AIMoveOut getAiMove() const noexcept;
};