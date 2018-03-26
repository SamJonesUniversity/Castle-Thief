#include "cmp_arrow.h"
using namespace std;
using namespace sf;

void ArrowComponent::update(double dt) {
  _lifetime -= dt;
  if (_lifetime <= 0.f) {
    _parent->setForDelete();
  }
}

ArrowComponent::ArrowComponent(Entity* p, float lifetime)
    : Component(p), _lifetime(lifetime) {}
