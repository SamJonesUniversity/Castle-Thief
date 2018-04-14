#include "Steering.h"

using namespace sf;

AIMoveOut Seek::getAiMove() const noexcept {
	AIMoveOut steering;
	steering.direction = _target->getPosition() - _character->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}

AIMoveOut Flee::getAiMove() const noexcept {
	AIMoveOut steering;
	steering.direction = _character->getPosition() - _target->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}