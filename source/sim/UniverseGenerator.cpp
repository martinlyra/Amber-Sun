#include "UniverseGenerator.h"

#include "GalaxyGenerationTools.h"


UniverseGenerator::UniverseGenerator( UniverseSetupData setup_data )
{
	universeSetupData = setup_data;
}

UniverseGenerator::~UniverseGenerator()
{
}

Universe & UniverseGenerator::GenerateUniverseOrDie()
{
	auto universe = Universe();

	return universe;
}

std::vector<Vector3f> UniverseGenerator::CalculateSystemPositions()
{
	auto positions = std::vector<Vector3f>();

	GalaxyGenerationTools::CalculatePositionsElliptic( positions, 150, 1000 );

	return std::vector<Vector3f>();
}

