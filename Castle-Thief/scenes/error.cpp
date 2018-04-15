#include "error.h"
#include "../components/cmp_text.h"
#include "../Castle-Thief.h"

using namespace std;
using namespace sf;

void error::Load()
{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"There is no entry in the save file." 
			"\nPlease start a new game before trying to load.");

	setLoaded(true);	
}

void error::Update(const double& dt) {
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	Engine::ChangeScene(&menu);

	Scene::Update(dt);
}