#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../Castle-Thief.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Castle Thief\n1. Continue\n2. New game\n3. Options\n4. Exit");
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
    
  }	
  else if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
	  Engine::ChangeScene(&level1);
  }
  else if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
	  
  }
  else if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
	  exit(0);
  }

  Scene::Update(dt);
}
