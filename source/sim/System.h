#pragma once

#include "shared\stdinc.h"

class System {

	string name;

public:
	System();
	~System();

	void ChangeName( string newName );
};

