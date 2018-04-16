#include "cmp_steering.h"
#include <cstdlib>

using namespace sf;

void SteeringComponent::update(double dt) {
	//if target play further than 100px seek
	if (length(_parent->getPosition() - _player->getPosition()) > 150.0f) {
		auto output = _seek.getAiMove();
		move(output.direction * (float)dt);
	}
	//if target play closer than 50px seek
	else if (length(_parent->getPosition() - _player->getPosition()) < 100.0f) {
		auto output = _flee.getAiMove();
		move(output.direction * (float)dt);
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
