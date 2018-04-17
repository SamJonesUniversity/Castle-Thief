#include "cmp_hurt_player.h"
#include <engine.h>

using namespace std;
using namespace sf;
float justhurt;

void HurtComponent::update(double dt) {
justhurt -= dt;
  if (auto pl = _player.lock()) {
	  int damage = pl->getHp();
    if (length(pl->getPosition() - _parent->getPosition()) < 25.0 && justhurt < 0) {
		pl->setHp(damage-1);
		justhurt = 2;
		if (damage == 1)
		{
			pl->setForDelete();
		}
	}
  }
}

HurtComponent::HurtComponent(Entity* p)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {}
