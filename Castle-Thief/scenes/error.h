#pragma once

#include "engine.h"

class error : public Scene {
public:
	error() = default;
	~error() override = default;

	void Load() override;

	void Update(const double& dt) override;
};