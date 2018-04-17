#pragma once

#include "engine.h"

class WinScene : public Scene {
public:
	WinScene() = default;
	~WinScene() override = default;

	void Load() override;

	void Update(const double& dt) override;


};

