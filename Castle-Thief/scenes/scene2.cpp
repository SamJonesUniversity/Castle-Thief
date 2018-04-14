#include "scene.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../Castle-Thief.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void Level2Scene::Load() {
	cout << " Scene 2 Load" << endl;
	ls::loadLevelFile("res/level2.txt", 40.0f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	// Create player
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
		s->getShape().setFillColor(Color::Magenta);
		s->getShape().setOrigin(10.f, 15.f);

		player->addTag("player");
		player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	}

	// Create Enemy
	/*{
		for (int i = 0; i < 9; i++)
		{
			auto enemy = makeEntity();
			enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) +
				Vector2f(0, 24));
			// *********************************
			// Add HurtComponent
			enemy->addComponent<HurtComponent>();
			// Add ShapeComponent, Red 16.f Circle
			auto e = enemy->addComponent<ShapeComponent>();
			e->setShape<sf::CircleShape>(16.f);
			e->getShape().setFillColor(Color::Red);
			e->getShape().setOrigin(16.f, 16.f);
		}
		// Add EnemyAIComponent

		// *********************************
	}*/

	// Add physics colliders to level tiles.
	{
		auto walls = ls::findTiles(ls::WALL);
		for (auto w : walls) {
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(20.f, 20.f); //offset to center
			auto e = makeEntity();
			e->setPosition(pos);
			e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
		}
	}

	//Simulate long loading times
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	cout << " Scene 2 Load Done" << endl;

	setLoaded(true);
}

void Level2Scene::UnLoad() {
	cout << "Scene 2 Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {
	Scene::Update(dt);
	const auto pp = player->getPosition();
	if (ls::getTileAt(player->getPosition()) == ls::END) {
	}
	else if (!player->isAlive()) {
		Engine::ChangeScene((Scene*)&level2);
	}
	
}

void Level2Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}