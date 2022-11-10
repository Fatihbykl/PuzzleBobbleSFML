#pragma once
#include "Cizilebilir.hpp"
#include <list>

class Daire : public Cizilebilir
{
private:
	float									m_yaricap;
	bool									m_hareketEdiyorMu = false;
	float									m_aci;
	int										m_bounceX = 1;
	std::vector<std::shared_ptr<Daire>>		m_komsular;
public:
	bool									m_ziyaretEdildiMi = false;
	sf::CircleShape							m_sekil;
	bool									m_aktifMi = true;
	Daire(float yaricap, sf::Color renk, bool hareket, float aci);
	bool getirHareketEdiyorMu();
	sf::Color renkGetir();
	void renkAyarla(sf::Color renk);
	void hareketAyarla(bool hareket);
	static std::shared_ptr<Daire> daireUret(float boyut, sf::Color renk, bool hareket, float aci);
	virtual void ciz(Pencere& pencere) override;
	void hareketEttir();
	void bounceAyarla();
	void komsuEkle(std::shared_ptr<Daire> daire);
	std::vector<std::shared_ptr<Daire>> komsuGetir();
};
typedef std::shared_ptr<Daire>		DairePtr;
typedef std::vector<DairePtr>		DaireListesi;
