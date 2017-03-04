#pragma once

#include "shared/stdinc.h"

#include "core/Vector3f.h"

#include "sim/UniverseSetupData.h"

#include "sim/System.h"
#include "sim/Universe.h"

class UniverseGenerator {

	UniverseSetupData universeSetupData;

public:
	UniverseGenerator(UniverseSetupData setup_data);
	~UniverseGenerator();

	Universe& GenerateUniverseOrDie();

private:
	std::vector<Vector3f> CalculateSystemPositions();
	std::vector<System> CreateSystems();
};

