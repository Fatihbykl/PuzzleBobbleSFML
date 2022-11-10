#include "Oyuncu.hpp"
#include "Pencere.hpp"
#include <stdlib.h>

Oyuncu::Oyuncu()
{
	renkListesiOlustur();
	sf::Color renk = rastgeleRenk();
	auto yeniOyuncu = Daire::daireUret(30, renk, false, 0);
	auto yeniCizgi = Cizgi::cizgiUret(90, sf::Color::White, 270);
	yeniCizgi->m_konum = sf::Vector2f(250, 670);
	yeniOyuncu->m_konum = sf::Vector2f(250, 670);
	m_oyuncu = yeniOyuncu;
	m_oyuncuCizgisi = yeniCizgi;
}

DairePtr Oyuncu::oyuncuGetir()
{
	return this->m_oyuncu;
}

void Oyuncu::topYoldaMiAyarla(bool yoldaMi)
{
	m_topYoldaMi = yoldaMi;
}

CizgiPtr Oyuncu::oyuncuCizgisiGetir()
{
	return this->m_oyuncuCizgisi;
}

void Oyuncu::oyuncuyuDondur(YON yon)
{
	int suankiAci = m_oyuncuCizgisi->aciGetir();
	int aci = (std::abs(360 - suankiAci)) % 360;
	if (yon == YON::YON_SAG)
	{
		if (aci <= 20) { return; }
		m_oyuncuCizgisi->aciAyarla(suankiAci + 5);
		
	}
	if (yon == YON::YON_SOL)
	{
		if (aci >= 160) { return; }
		m_oyuncuCizgisi->aciAyarla(suankiAci - 5);
		
	}
}

DairePtr Oyuncu::firlayanTopOlustur()
{
	if (m_topYoldaMi){ return NULL; }
	m_topYoldaMi = true;
	sf::Color renk = rastgeleRenk();
	sf::Color oyuncuRengi = m_oyuncu->renkGetir();

	auto yeniTop = Daire::daireUret(30, oyuncuRengi, true, m_oyuncuCizgisi->sekilGetir().getRotation());
	yeniTop->m_konum = sf::Vector2f(m_oyuncu->m_konum.x, m_oyuncu->m_konum.y);

	m_oyuncu->renkAyarla(renk);
	return yeniTop;
}

void Oyuncu::renkListesiOlustur()
{
	m_renkler.push_back(sf::Color::Red);
	m_renkler.push_back(sf::Color::Green);
	m_renkler.push_back(sf::Color::Yellow);
	m_renkler.push_back(sf::Color::Blue);
}

sf::Color Oyuncu::rastgeleRenk()
{
	srand(time(0));
	int sayi = rand() % 4;
	return m_renkler.at(sayi);
}
