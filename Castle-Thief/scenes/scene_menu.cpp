#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../Castle-Thief.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <fstream>
#include <ShlObj_core.h>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
	  sf::Music music;
	  music.openFromFile("res/music/BloodyTears.ogg");
	  music.setVolume(50);
	  music.play();
		
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Castle Thief\n1. Continue\n2. New game\n3. Options\n4. Exit");
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		string buffer;

		CHAR my_documents[MAX_PATH];
		HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

		string paths = strcat(my_documents, "\\Castle-Thief\\savefile.txt");

		string line;
		ifstream myfile(paths);
		if (myfile.is_open())
		{
			getline(myfile, line);

			myfile.close();
		}

		const char c = buffer[0];

		if(line == '2') {
			Engine::ChangeScene(&level2);
		}
		else
		{
			Engine::ChangeScene(&error1);
		}
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
