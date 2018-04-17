#include "cmp_steering.h"
#include <cstdlib>

using namespace sf;
float fleeing;

void SteeringComponent::update(double dt) {
	//if target player within 400px seek
	fleeing -= dt;
	if (length(_parent->getPosition() - _player->getPosition()) < 400.0f && fleeing > 0.f) {
		auto output = _seek.getAiMove();
		move(output.direction * (float)dt);
	}
	//if hp == 1 flee for 5 seconds
	else if (_parent->getHp() == 1) {
		auto output = _flee.getAiMove();
		move(output.direction * (float)dt);
	}
	//If none of above wander aimlessly
	else
	{
		AIMoveOut steering;
		steering.direction.x = rand() % 1601 + (-800);
		steering.direction.y = rand() % 1601 + (-800);
		steering.direction = normalize(steering.direction);
		steering.direction *= 25.f;
		steering.rotation = 0.0f;

		move(steering.direction * (float)dt);
		fleeing = 5.f;
	}
}

SteeringComponent::SteeringComponent(Entity* p, Entity* player)
	: _player(player), _seek(Seek(p, player, 100.f)),
	_flee(Flee(p, player, 100.0f)), Component(p) {}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const
{
	if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x || pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y) {
		return false;
	}
	return true;
}

void SteeringComponent::move(const sf::Vector2f &p) {
	auto new_pos = _parent->getPosition() + p;

	if(plusorminus)
	{ 
		new_pos.x += rand() % 2;
		new_pos.y += rand() % 2;
		plusorminus = false;
	}
	else
	{
		new_pos.x -= rand() % 2;
		new_pos.y -= rand() % 2;
		plusorminus = true;
	}

	if (validMove(new_pos)) {
		_parent->setPosition(new_pos);
	}
}
