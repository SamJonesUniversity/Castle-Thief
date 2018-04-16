#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class HurtComponentEnemy : public Component {
protected:
  std::weak_ptr<Entity> _enemy;

public:
  void update(double dt) override;
  void render() override {}
  explicit HurtComponentEnemy(Entity* e);
  HurtComponentEnemy() = delete;
};
