#include "cmp_hurt_enemy.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtComponentEnemy::update(double dt) {
  if (auto en = _enemy.lock()) {
	  int damage = en->getHp();
    if (length(en->getPosition() - _parent->getPosition()) < 25.0) {
		en->setHp(damage-1);
		_parent->setForDelete();
		if (damage == 1)
		{
			en->setForDelete();
		}
	}
  }
}

HurtComponentEnemy::HurtComponentEnemy(Entity* e)
    : Component(e), _enemy(_parent->scene->ents.find("enemy")[0]) {}