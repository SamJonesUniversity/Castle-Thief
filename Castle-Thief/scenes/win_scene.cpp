#include "win_scene.h"
#include "../components/cmp_text.h"
#include "../Castle-Thief.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;


void WinScene::Load() {
	cout << "Options Load \n";
	{

		auto WinTEXT = makeEntity();
		auto teehee = WinTEXT->addComponent<TextComponent>(
			"YOU WON!");
	}
}

void WinScene::Update(const double& dt) {

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	Engine::ChangeScene(&menu);

	Scene::Update(dt);
}