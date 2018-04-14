#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class ArrowComponent : public Component {
protected:
  float _lifetime;

public:
  void update(double dt) override;
  void render() override {}
  explicit ArrowComponent(Entity* p, float lifetime = 3.f);
  ArrowComponent() = delete;
};
