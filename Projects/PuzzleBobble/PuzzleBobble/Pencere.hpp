#pragma once
#include <SFML/Graphics.hpp>
#include "TemelTurler.hpp"

class Pencere
{
private:
	sf::RenderWindow		m_pencere;
	KlavyeFonksiyonListesi  m_tusBasmaFonkListesi;
public:
	Pencere();
	void olustur(unsigned int genislik, unsigned int yukseklik, sf::String baslik);
	void cizimeBasla();
	void cizimiBitir();
	void olayKontrol();
	void tusBasmaFonkEkle(KlavyeFonksiyonu fonk);
	void ciz(sf::Drawable& sekil);
	bool acikmi();
	void pencereKapat();
};