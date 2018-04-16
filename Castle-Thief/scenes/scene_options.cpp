#include "scene_options.h"
#include "../components/cmp_text.h"
#include "../Castle-Thief.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
void OptionsScene::Load() {
	cout << "Options Load \n";
	{

		auto Texto= makeEntity();
		auto tee = Texto->addComponent<TextComponent>(
			"Resolution\n1. Controls\n2.  Go Back");
	}
}

void OptionsScene::Update(const double& dt) {
	// cout << "Menu Update "<<dt<<"\n";

	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		Engine::GetWindow().setSize(sf::Vector2u(1920, 1080));
	}

	else if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
		Engine::ChangeScene(&menu);

	}

	Scene::Update(dt);
}