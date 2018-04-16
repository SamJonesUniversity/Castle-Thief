#include "cmp_arrow.h"
#include "LevelSystem.h"
using namespace std;
using namespace sf;

void ArrowComponent::update(double dt) {
  _lifetime -= dt;
  Vector2f leftside = _parent->getPosition();
  leftside.x += 10.f;
  if (_lifetime <= 0.f || ls::getTileAt(_parent->getPosition()) == ls::WALL || ls::getTileAt(leftside) == ls::WALL) {
	_parent->setForDelete();

  }
}

ArrowComponent::ArrowComponent(Entity* p, float lifetime)
    : Component(p), _lifetime(lifetime) {}
