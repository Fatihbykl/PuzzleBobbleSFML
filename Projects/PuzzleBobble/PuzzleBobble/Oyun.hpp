#pragma once
#include <SFML/Graphics.hpp>
#include "Pencere.hpp"
#include "Daire.hpp"
#include "Cizgi.hpp"
#include "Oyuncu.hpp"
#include "Grid.hpp"

class Oyun
{
private:
	void saatiYenidenBaslat();
	sf::Time				m_gecenSure;
	sf::Time				m_cerceveSuresi;
	sf::Clock				m_saat;
	Pencere					m_pencere;
	Grid					m_grid;
	Oyuncu					m_oyuncu;
	int						m_fps;
	int						m_atilanTopSayisi = 0;
	std::vector<DairePtr>	m_secilenToplar;

public:
	Oyun();
	~Oyun();
	void setFps(int fps);
	void oyunuBaslat(unsigned int genislik, unsigned int yukseklik);
	void patlayanDaireEkle(float boyut, float konumX, float konumY, sf::Color renk, bool hareket);
	void cizgiEkle(float boyut, float konumX, float konumY, sf::Color renk,int aci);
	void klavyeBasildi(sf::Keyboard::Key tus);
	void firlayanTopListeyeEkle();
	void olaylariBagla();
	void oyunuAyarla();
	void cizimFonksiyonu();
	void carpismaKontrol();
	void daireYerlestir();
	void renkKontrolu(DairePtr daire, sf::Color renk);
	void stateSifirla();
	bool baglantisiVarMi(DairePtr daire);
	void baglantisizlariSil();
	void toplariPatlat();
	int  aktifTopSayisi();
	void oyunKontrol();
	DaireListesi	m_daireler;
	CizgiListesi	m_cizgiler;
};
