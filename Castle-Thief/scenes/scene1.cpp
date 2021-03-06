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
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> enemy1;

sf::Texture ghost;
bool standing;
int activeSprite;
int heartSpriteNum;

sf::Texture texture;
sf::Texture thief;
sf::Texture heart;

sf::Sprite healthSprite;
sf::Sprite Sprite1;

void Level1Scene::Load() {
	cout << " Scene 1 Load" << endl;
	ls::loadLevelFile("res/level_1.txt", 40.0f);
	ghost.loadFromFile("res/ghost.png");

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	string paths = strcat(my_documents, "\\Castle-Thief\\savefile.txt");

	ofstream myfile(paths);
	if (myfile.is_open())
	{
		myfile << "1\n";
		myfile.close();
	}

	texture.loadFromFile("res/background.png", sf::IntRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	texture.setRepeated(true);

	Sprite1.setTexture(texture);

	heart.loadFromFile("res/heart.png", sf::IntRect(0, 0, 50, 50));
	healthSprite.setTexture(heart);

  // Create player
  {
    player = makeEntity();
	player->setHp(3);
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	auto s = player->addComponent<SpriteComponent>();
	s->getSprite().setOrigin(28.5f, 40.f);
	thief.loadFromFile("res/thief.png", sf::IntRect(0, 0, 57, 57));
	s->getSprite().setTexture(thief);
	activeSprite = 0;
	player->addTag("player");
  }
  
  // Create Enemy
  {
	for (int i = 0; i < 2; i++)
	{
	  enemy1 = makeEntity();
	  enemy1->setHp(3);
	  enemy1->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY).at(i)) +
		  Vector2f(0, 24));
	  enemy1->addComponent<HurtComponent>();  
	  auto e = enemy1->addComponent<SpriteComponent>();
	  e->getSprite().setTexture(ghost);
	  e->getSprite().setTextureRect(sf::IntRect(0, 0, 32.5, 56));
	  e->getSprite().setOrigin(15.f, 25.f);
	  enemy1->addComponent<SteeringComponent>(player.get());
	  
	  enemy1->addTag("enemy");
	 }
  }
	//Adds a invisible enemy so that shooting an arrow when all enemie are dead does not crash the game.
	enemy1 = makeEntity();
	enemy1->setHp(3);
	enemy1->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY).at(3)) +
		Vector2f(0, 24));
	enemy1->addTag("enemy");
  
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
	 return;
  }
  else if (!player->isAlive()) {
	 Engine::ChangeScene((Scene*)&level1);
	 return;
  }

  if (Keyboard::isKeyPressed(Keyboard::Left))
  {
	  if (activeSprite != 1)
	  {
		  auto s = player->addComponent<SpriteComponent>();
		  s->getSprite().setOrigin(28.5f, 40.f);
		  thief.loadFromFile("res/thief.png", sf::IntRect(285, 0, 57, 57));
		  s->getSprite().setTexture(thief);
		  activeSprite = 1;
	  }
  }
  else if (Keyboard::isKeyPressed(Keyboard::Right))
  {
	  if (activeSprite != 2)
	  {
		  auto s = player->addComponent<SpriteComponent>();
		  s->getSprite().setOrigin(28.5f, 40.f);
		  thief.loadFromFile("res/thief.png", sf::IntRect(342, 0, 57, 57));
		  s->getSprite().setTexture(thief);
		  activeSprite = 2;
	  }
  }
  else if (Keyboard::isKeyPressed(Keyboard::C))
  {
	  if (activeSprite != 3)
	  {
		  auto s = player->addComponent<SpriteComponent>();
		  s->getSprite().setOrigin(28.5f, 40.f);
		  thief.loadFromFile("res/thief.png", sf::IntRect(57, 124, 57, 57));
		  s->getSprite().setTexture(thief);
		  activeSprite = 3;
	  }
  }
  else if (Keyboard::isKeyPressed(Keyboard::Z))
  {
	 if(activeSprite != 4)
	 {
		  auto s = player->addComponent<SpriteComponent>();
		  s->getSprite().setOrigin(28.5f, 40.f);
		  thief.loadFromFile("res/thief.png", sf::IntRect(228, 285,57, 57));
		  s->getSprite().setTexture(thief);
		  activeSprite = 4;
	 }
  }

  // handle heart sprite
  {
	if(player->isAlive())
	{
	  if (player->getHp() == 2 && heartSpriteNum != 2)
	  {
			heart.loadFromFile("res/heart.png", sf::IntRect(50, 0, 50, 50));
			healthSprite.setTexture(heart);
			heartSpriteNum = 2;
	  }
	  else if (player->getHp() == 1 && heartSpriteNum != 3)
	  {
			heart.loadFromFile("res/heart.png", sf::IntRect(100, 0, 50, 50));
			healthSprite.setTexture(heart);
			heartSpriteNum = 3;
	  }
	}
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::renderBg(Engine::GetWindow(), Sprite1);

  ls::render(Engine::GetWindow());
  
  ls::renderBg(Engine::GetWindow(), healthSprite);

  Scene::Render();
}
