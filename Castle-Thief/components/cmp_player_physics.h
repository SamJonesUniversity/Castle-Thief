#pragma once
#include <ecm.h>
#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  bool _grounded;
  float _groundspeed;
  bool _direction;
  bool _candash;
  bool _canfire;
  float _firetime;
  float _elapsed;
  bool _dampener;
  bool isGrounded() const;

public:
  void update(double dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

  PlayerPhysicsComponent() = delete;
};