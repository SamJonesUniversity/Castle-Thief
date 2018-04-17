#include "scene_options.h"
#include "../components/cmp_text.h"
#include "../Castle-Thief.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <fstream>
#include <ShlObj_core.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int viewX, viewY;

void OptionsScene::Load() {
	cout << "Options Load \n";
	{

		auto Texto = makeEntity();
		auto tee = Texto->addComponent<TextComponent>(
			"Resolution\n1. Controls\n2.  Go Back");
	}
}

void OptionsScene::Update(const double& dt) {
	// cout << "Menu Update "<<dt<<"\n";

	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		//Engine::GetWindow().setSize(sf::Vector2u(1920, 1080));
		//Engine::GetWindow().setPosition(sf::Vector2i(0, 0));
		//viewX = Engine::getWindowSize().x, viewY = Engine::getWindowSize().y;
		Engine::GetWindow().close();
		Engine::Start(1920, 1080, "Castle-Thief", &option);
		//sf::Window window(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen);
		/*sf::View view1(sf::Vector2f(1920/2, 1080/2), sf::Vector2f(1920, 1080));
		view1.zoom(0.9f);
		view1.setCenter(1920/2, 1080/2);
		Engine::GetWindow().setView(view1);*/
		//Load();
	
	}

	else if (sf::Keyboard::isKeyPressed(Keyboard::Num5)) {
		Engine::ChangeScene(&menu);

	}

	Scene::Update(dt);
}