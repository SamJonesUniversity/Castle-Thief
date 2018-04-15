#include "engine.h"
#include "Castle-Thief.h"
#include "scenes/scene_menu.h"

using namespace std;
MenuScene menu;
Level1Scene level1;
Level2Scene level2;
error error1;

int main() {
	Engine::Start(1280, 720, "Castle-Thief", &menu);
}