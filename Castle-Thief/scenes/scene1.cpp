#include "scene.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_steering.h"
#include "../components/cmp_pathfinder.h"
#include "engine.h"
#include "../components/astar.h"
#include "../Castle-Thief.h"
#include <LevelSystem.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <ShlObj_core.h>
#include "../components/cmp_sprite.h"
#include "SFMl/Graphics.hpp"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> enemy1;
shared_ptr<PathfindingComponent> ai;

sf::Texture texture;

void Level1Scene::Load() {
	cout << " Scene 1 Load" << endl;
	ls::loadLevelFile("res/level_1.txt", 40.0f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	string paths = strcat(my_documents, "\\Castle-Thief\\savefile.txt");

	ofstream myfile(paths);
	if (myfile.is_open())
	{
		myfile << "2\n";
		myfile.close();
	}

  // Create player
  {
    player = makeEntity();
	player->setHp(3);
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	auto s = player->addComponent<SpriteComponent>();
	texture.loadFromFile("res/thief.png");
	s->getSprite().setOrigin(28.5f,40.f);
	s->getSprite().setTexture(texture);
	s->getSprite().setTextureRect(sf::IntRect(399,171,57,57));
	s.reset();
	/*
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(10.f, 15.f);
	*/
	player->addTag("player");
    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
  }
  
  // Create Enemy
  {
	for (int i = 0; i < ls::findTiles(ls::ENEMY).size(); i++)
	{
	  enemy1 = makeEntity();
	  enemy1->setHp(3);
	  enemy1->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY).at(i)) +
		  Vector2f(0, 24));
		  
	  // *********************************
	  // Add HurtComponent
	  //enemy1->addComponent<HurtComponent>();
	  // Add ShapeComponent, Red 16.f Circle
	  auto e = enemy1->addComponent<ShapeComponent>();
	  e->setShape<sf::CircleShape>(16.f);
	  e->getShape().setFillColor(Color::Red);
	  e->getShape().setOrigin(16.f, 16.f);
	  enemy1->addComponent<SteeringComponent>(player.get());
	  
	  enemy1->addTag("enemy");
	  //ai = enemy1->addComponent<PathfindingComponent>();
	  //enemy1->addComponent<PhysicsComponent>(true, Vector2f(20.f, 30.f));
	}
	  // Add EnemyAIComponent

	  // *********************************
  }
  
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
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

 void Level1Scene::Update(const double& dt) {
	 Scene::Update(dt);
	 const auto pp = player->getPosition();


  if (ls::getTileAt(player->getPosition()) == ls::END) {
	 Engine::ChangeScene((Scene*)&level2);
  }
  else if (!player->isAlive()) {
	 Engine::ChangeScene((Scene*)&level1);
  }
  /*auto enemy_pos = enemy1->getPosition() - ls::getOffset();
  auto enemy_tile = Vector2i(enemy_pos / ls::getTileSize());
  auto player_pos = player->getPosition() - ls::getOffset();
  auto player_tile = Vector2i(player_pos / ls::getTileSize());
  auto path = pathFind(enemy_tile, player_tile);
  ai->setPath(path);*/

  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
