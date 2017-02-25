#pragma once

#include "shared\stdinc.h"

#include "System.h"
#include "StarObject.h"

class Universe {

	std::vector<System>	systems;
	std::vector<StarObject> stars;

public:
	Universe();
	~Universe();
};

