#pragma once
#include "Daire.hpp"
#include "Cizgi.hpp"
#include "TemelTurler.hpp"

class Oyuncu
{
private:
	DairePtr	m_oyuncu;
	CizgiPtr	m_oyuncuCizgisi;
	RenkListesi m_renkler;
	bool		m_topYoldaMi = false;
public:
	Oyuncu();
	DairePtr oyuncuGetir();
	void topYoldaMiAyarla(bool yoldaMi);
	CizgiPtr oyuncuCizgisiGetir();
	void oyuncuyuDondur(YON yon);
	DairePtr firlayanTopOlustur();
	void renkListesiOlustur();
	sf::Color rastgeleRenk();
};
