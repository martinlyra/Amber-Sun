#pragma once

#include "shared/stdinc.h"

#include "core/Vector3f.h"

namespace GalaxyGenerationTools {
	
	void CalculatePositionsElliptic( std::vector<Vector3f>& positions, int size, int diameter );
	void CalculatePositionsSprial( std::vector<Vector3f>& positions, int arms, int size, int diameter );
	void CalculatePositionsDisc( std::vector<Vector3f>& positions, int size, int diameter );
};

