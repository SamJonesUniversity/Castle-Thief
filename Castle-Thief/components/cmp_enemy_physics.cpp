#include "cmp_enemy_physics.h"
#include <system_physics.h>
#include "cmp_arrow.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <engine.h>
#include <LevelSystem.h>
#include "cmp_hurt_player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

void EnemyPhysicsComponent::update(double dt)
{
}

EnemyPhysicsComponent::EnemyPhysicsComponent(Entity * p, const sf::Vector2f & size)
	: PhysicsComponent(p, true, size) {}
