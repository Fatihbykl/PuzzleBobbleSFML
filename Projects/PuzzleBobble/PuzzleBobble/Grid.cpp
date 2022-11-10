#include "Grid.hpp"
#include "Daire.hpp"
Grid::Grid()
{
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			auto hex = Hex::hexUret(30, 0);
			hex->m_konum = sf::Vector2f((y % 2 ? 60 : 30) + x * 60.f, 35 + y * 50.f);
			m_hexGrid[y][x] = hex;
		}
	}
}

void Grid::ciz(Pencere& pencere)
{
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			m_hexGrid[y][x]->ciz(pencere);
		}
	}
}


