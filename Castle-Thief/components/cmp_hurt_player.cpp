#include "cmp_hurt_player.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtComponent::update(double dt) {
  if (auto pl = _player.lock()) {
	  int damage = pl->getHp();
    if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
		pl->setHp(damage-1);
		if (damage == 0)
		{
			pl->setForDelete();
			_parent->setForDelete();
		}
      
    }
  }
}

HurtComponent::HurtComponent(Entity* p)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {}
