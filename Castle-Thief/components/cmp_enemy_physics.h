#pragma once
#include <ecm.h>
#include "cmp_physics.h"

class EnemyPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;

public:
  void update(double dt) override;

  explicit EnemyPhysicsComponent(Entity* p, const sf::Vector2f& size);

  EnemyPhysicsComponent() = delete;
};
