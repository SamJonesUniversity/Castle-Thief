#include "scene.h"
#include "../components/cmp_text.h"
#include "../Castle-Thief.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


void tutorial::Load() {
	cout << "Options Load \n";
	{

		auto tuttext = makeEntity();
		auto teehee = tuttext->addComponent<TextComponent>(
			"In this game you play as a thief and you must make it throught the\ncastle killing the scary ghosts trying to stop you.\n\nThe controls are:\nJump:Z\nFire Bow:X\nDash:C\nMove Left: Left arrow key\nMove Right: Right arrow key\n\nBoth you and the ghost have 3 health points,\nthis is displayed on the top left as a heart.\nIf you reach 0 health points you will die,\nthe same applies to each ghost.\nIn order to complete the game you must pass through all the blue doors\nwithout dying.\n\nPress space or return to continue...");
	}
}

void tutorial::Update(const double& dt) {

	if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Return))
	{
		Engine::ChangeScene(&level1);
	}

	Scene::Update(dt);
}