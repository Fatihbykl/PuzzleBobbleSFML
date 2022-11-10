#pragma once
#include "Hex.hpp"

class Grid
{
public:
	HexPtr m_hexGrid[12][7];
	Grid();
	void ciz(Pencere& pencere);
};
