#include "scene.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../Castle-Thief.h"
#include <LevelSystem.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <ShlObj_core.h>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
sf::Texture backTexture;
sf::Texture texture2;
sf::Sprite Sprite2;
sf::Texture thief2;
bool standing2;
int activeSprite2;

void Level2Scene::Load() {
	backTexture.loadFromFile("res/background.png", sf::IntRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	backTexture.setRepeated(true);

	Sprite2.setTexture(backTexture);

	cout << " Scene 2 Load" << endl;
	ls::loadLevelFile("res/level_2.txt", 40.0f);

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
		player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
		auto s = player->addComponent<SpriteComponent>();
		s->getSprite().setOrigin(28.5f, 40.f);
		thief2.loadFromFile("res/thief.png", sf::IntRect(0, 0, 57, 57));
		s->getSprite().setTexture(thief2);
		activeSprite2 = 0;
		player->addTag("player");
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

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (activeSprite2 != 1)
		{
			auto s = player->addComponent<SpriteComponent>();
			s->getSprite().setOrigin(28.5f, 40.f);
			thief2.loadFromFile("res/thief.png", sf::IntRect(285, 0, 57, 57));
			s->getSprite().setTexture(thief2);
			activeSprite2 = 1;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (activeSprite2 != 2)
		{
			auto s = player->addComponent<SpriteComponent>();
			s->getSprite().setOrigin(28.5f, 40.f);
			thief2.loadFromFile("res/thief.png", sf::IntRect(342, 0, 57, 57));
			s->getSprite().setTexture(thief2);
			activeSprite2 = 2;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::C))
	{
		if (activeSprite2 != 3)
		{
			auto s = player->addComponent<SpriteComponent>();
			s->getSprite().setOrigin(28.5f, 40.f);
			thief2.loadFromFile("res/thief.png", sf::IntRect(57, 124, 57, 57));
			s->getSprite().setTexture(thief2);
			activeSprite2 = 3;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		if (activeSprite2 != 4)
		{
			auto s = player->addComponent<SpriteComponent>();
			s->getSprite().setOrigin(28.5f, 40.f);
			thief2.loadFromFile("res/thief.png", sf::IntRect(342, 285, 57, 57));
			s->getSprite().setTexture(thief2);
			activeSprite2 = 4;
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
	ls::renderBg(Engine::GetWindow(), Sprite2);
	ls::render(Engine::GetWindow());

	Scene::Render();
}