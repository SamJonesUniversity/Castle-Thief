#pragma once

#include "engine.h"

class tutorial : public Scene {
public:
	void Load() override;

	void Update(const double& dt) override;
};

class Level1Scene : public Scene {
public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;
};

class Level2Scene : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};