#pragma once
#include "Cizilebilir.hpp"

class Cizgi : public Cizilebilir
{
private:
	float	m_boyut;
	int		m_aci;
	sf::RectangleShape m_sekil;
public:
	Cizgi(float boyut, sf::Color renk, int aci);
	sf::RectangleShape sekilGetir();
	int aciGetir();
	void aciAyarla(int aci);
	static std::shared_ptr<Cizgi> cizgiUret(float boyut, sf::Color renk, int aci);
	virtual void ciz(Pencere& pencere) override;
};
typedef std::shared_ptr<Cizgi>		CizgiPtr;
typedef std::vector<CizgiPtr>		CizgiListesi;