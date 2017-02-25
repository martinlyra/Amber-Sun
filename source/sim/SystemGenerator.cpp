
#include <vector>
#include <string>

#include "SystemGenerator.h"

static std::vector<std::string> names = { "Nyx", "Euclide", "Ithara" };

SystemGenerator::SystemGenerator()
{
}


SystemGenerator::~SystemGenerator()
{
}

System SystemGenerator::CreateSystem()
{
	System system = System();

	system.ChangeName(names[rand() % names.size()]);

	return system;
}
